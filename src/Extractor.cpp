#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "archive.h"
#include "archive_entry.h"
#include "config.h"

#include "Common.h"
#include "Exceptions.h"
#include "Extractor.h"


Extractor::Extractor()
    : path_to_unpack(0),
    path_to_file(0)
{}


Extractor::~Extractor()
{
    if (path_to_unpack) free(path_to_unpack);
    if (path_to_file) free(path_to_file);
}


archive *Extractor::SetUpRead() const
{
    archive *in = archive_read_new();

    archive_read_support_format_gnutar(in);
    archive_read_support_format_rar(in);
    archive_read_support_format_tar(in);
    archive_read_support_format_zip(in);
    archive_read_support_format_zip_streamable(in);
    archive_read_support_format_zip_seekable(in);

    archive_read_support_filter_gzip(in);

    return in;
}


archive *Extractor::SetUpWrite() const
{
    archive *out = archive_write_disk_new();
    int flags = ARCHIVE_EXTRACT_TIME;
    flags |= ARCHIVE_EXTRACT_PERM;
    flags |= ARCHIVE_EXTRACT_ACL;
    flags |= ARCHIVE_EXTRACT_FFLAGS;

    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    return out;
}


void Extractor::SetUpPathToUnpack(archive_entry *entry)
{
    char *filename = strdup(archive_entry_pathname(entry));
    char *extension = strrchr(filename, '.');
    if (!extension) throw Wac::LibArchiveEx(NULL);

    char *photo_token = gen_random_string(PHOTO_TOKEN_LENGTH);

    int len = strlen(path_to_unpack) + 1 + PHOTO_TOKEN_LENGTH + strlen(extension) + 1;
    char *output_path =  (char *)malloc(len);

    output_path[0] = '\0';
    output_path = strcat(output_path, path_to_unpack);
    output_path = strcat(output_path, "/");
    output_path = strcat(output_path, photo_token);
    output_path = strcat(output_path, extension);
    archive_entry_set_pathname(entry, output_path);

    free(filename);
    free(photo_token);
    free(output_path);
}


void Extractor::CheckParams()
{
    if (path_to_file == 0) throw Wac::NoPathToArchive();

    struct stat buf;
    if (stat(path_to_file, &buf) == -1) throw Wac::WrongPathToArchive();

    if (path_to_unpack) {
        DIR *dir = opendir(path_to_unpack);
        if (dir == 0) throw Wac::WrongPathToUnpack();
        closedir(dir);
    } else {
        path_to_unpack = strdup(".");
    }
}


void Extractor::Finish(archive *in, archive *out) const
{
    archive_read_close(in);
    archive_read_free(in);
    archive_write_close(out);
    archive_write_free(out);
}


void Extractor::Extract()
{
    archive_entry *entry;
    int r;

    CheckParams();

    archive *in = SetUpRead();
    archive *out = SetUpWrite();

    if (archive_read_open_filename(in, path_to_file, 10240)) {
        throw Wac::LibArchiveEx(in);
    }

    while (true) {
        r = archive_read_next_header(in, &entry);
        if (r == ARCHIVE_EOF) break;
        if (r == ARCHIVE_FATAL) throw Wac::LibArchiveEx(in);

        if (!is_image(archive_entry_pathname(entry))) continue;

        SetUpPathToUnpack(entry);

        r = archive_write_header(out, entry);
        if (r == ARCHIVE_FATAL) throw Wac::LibArchiveEx(out);

        if (archive_entry_size(entry) > 0) CopyData(in, out);

        r = archive_write_finish_entry(out);
        if (r == ARCHIVE_FATAL) throw Wac::LibArchiveEx(out);
    }

    Finish(in, out);
}


void Extractor::CopyData(archive *ar, archive *aw) const
{
    int r;
    const void *buff;
    size_t size;
    off_t offset;

    while (true) {
        r = archive_read_data_block(ar, &buff, &size, &offset);
        if (r == ARCHIVE_EOF) return;
        if (r == ARCHIVE_FATAL) throw Wac::LibArchiveEx(ar);

        r = archive_write_data_block(aw, buff, size, offset);
        if (r == ARCHIVE_FATAL) throw Wac::LibArchiveEx(aw);
    }
}
