#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "archive.h"
#include "archive_entry.h"
#include "config.h"

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


Archive *Extractor::SetUpRead() const
{
    Archive *in = archive_read_new();

    archive_read_support_format_all(in);
    archive_read_support_compression_all(in);

    return in;
}


Archive *Extractor::SetUpWrite() const
{
    Archive *out = archive_write_disk_new();
    int flags = ARCHIVE_EXTRACT_TIME;
    flags |= ARCHIVE_EXTRACT_PERM;
    flags |= ARCHIVE_EXTRACT_ACL;
    flags |= ARCHIVE_EXTRACT_FFLAGS;

    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    return out;
}


void Extractor::SetUpPathToUnpack(ArchiveEntry *entry)
{
    char *filename = strdup(archive_entry_pathname(entry));
    int len = strlen(path_to_unpack) + 1 + strlen(filename) + 1;
    char *output_path = new char[len];
    output_path[0] = '\0';
    output_path = strcat(output_path, path_to_unpack);
    output_path = strcat(output_path, "/");
    output_path = strcat(output_path, filename);
    archive_entry_set_pathname(entry, output_path);

    free(filename);
    delete[] output_path;
}


void Extractor::CheckParams()
{
    if (path_to_file == 0) throw NoPathToArchive();

    struct stat buf;
    if (stat(path_to_file, &buf) == -1) throw WrongPathToArchive();

    if (path_to_unpack) {
        DIR *dir = opendir(path_to_unpack);
        if (dir == 0) throw WrongPathToUnpack();
        closedir(dir);
    } else {
        path_to_unpack = strdup(".");
    }
}


void Extractor::Finish(Archive *in, Archive *out) const
{
    archive_read_close(in);
    archive_read_finish(in);
    archive_write_close(out);
    archive_write_finish(out);
}


void Extractor::Extract()
{
    ArchiveEntry *entry;
    int r;

    CheckParams();

    Archive *in = SetUpRead();
    Archive *out = SetUpWrite();

    if (archive_read_open_filename(in, path_to_file, 10240))
        throw LibArchiveEx(in);

    while (true) {
        r = archive_read_next_header(in, &entry);
        if (r == ARCHIVE_EOF) break;
        if (r == ARCHIVE_FATAL) throw LibArchiveEx(in);

        SetUpPathToUnpack(entry);

        r = archive_write_header(out, entry);
        if (r == ARCHIVE_FATAL) throw LibArchiveEx(in);

        if (archive_entry_size(entry) > 0) CopyData(in, out);

        r = archive_write_finish_entry(out);
        if (r == ARCHIVE_FATAL) throw LibArchiveEx(out);
    }

    Finish(in, out);
}


void Extractor::CopyData(Archive *ar, Archive *aw) const
{
    int r;
    const void *buff;
    size_t size;
    off_t offset;

    while (true) {
        r = archive_read_data_block(ar, &buff, &size, &offset);
        if (r == ARCHIVE_EOF) return;
        if (r == ARCHIVE_FATAL) throw LibArchiveEx(ar);

        r = archive_write_data_block(aw, buff, size, offset);
        if (r == ARCHIVE_FATAL) throw LibArchiveEx(aw);
    }
}
