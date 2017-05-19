#include "ThumbnailsCreator.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#include "jpeglib.h"

#include "Exceptions.h"
#include "Common.h"


ThumbnailsCreator::ThumbnailsCreator()
    : path_to_originals(0),
    path_to_thumbnails(0),
    quality(0)
{}


ThumbnailsCreator::~ThumbnailsCreator()
{
    if (path_to_originals) free(path_to_originals);
    if (path_to_thumbnails) free(path_to_thumbnails);
}


void ThumbnailsCreator::CheckParams()
{
    if (quality == 0) quality = 75;

    if (path_to_originals == 0) throw Wac::NoPathToOriginals();

    DIR *dir = opendir(path_to_originals);
    if (dir == 0) throw Wac::WrongPathToOriginals();
    closedir(dir);

    if (path_to_thumbnails) {
        dir = opendir(path_to_thumbnails);
        if (dir == 0) throw Wac::WrongPathToThumbnails();
        closedir(dir);
    } else {
        path_to_thumbnails = strdup(".");
    }
}


//This returns a pointer to allocated dynamic memory
//Must free outside this function
char *ThumbnailsCreator::CreatePathForResized(const char *img_path) const
{
    const char *name = strrchr(img_path, '/');
    char *resized_path = strdup(path_to_thumbnails);
    resized_path = str_cat_alloc(resized_path, name);

    char *extension = strrchr(resized_path, '.');
    *extension = '\0';

    resized_path = str_cat_alloc(resized_path, ".jpg");

    return resized_path;
}


void ThumbnailsCreator::WriteJpeg(
        const char *path,
        Img *img,
        int width,
        int height,
        int q) const
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    FILE *out = fopen(path, "wb");
    if (!out) {
        exit(-1);
        perror("path");
    }

    jpeg_stdio_dest(&cinfo, out);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, q, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer[1];
    int row_stride = cinfo.image_width * cinfo.input_components;
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &img[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    fclose(out);
}


char *ThumbnailsCreator::ResizeAndSave(const char *img_path) const
{
    int in_w, in_h, in_n;

    Img *src = stbi_load(img_path, &in_w, &in_h, &in_n, 3);

    if (src == 0) throw Wac::CorruptedImage(img_path);

    float k = sqrt(float(60000) / in_h / in_w);
    int out_w = k * in_w;
    int out_h = k * in_h;
    Img *resized = (Img *)malloc(out_w * out_h * 3);

    stbir_resize_uint8(
        src, in_w, in_h, 0,
        resized, out_w, out_h, 0,
        3);
    stbi_image_free(src);

    char *resized_img_path = CreatePathForResized(img_path);

    WriteJpeg(resized_img_path, resized, out_w, out_h, quality);

    free(resized);

    return resized_img_path;
}


bool ThumbnailsCreator::IsDir(const char *dir) const
{
    DIR *n = opendir(dir);
    if (n) closedir(n);

    return n != 0;
}


bool ThumbnailsCreator::IsOrdinaryFile(const char *name) const
{
    return name[0] != '.';
}


void ThumbnailsCreator::ProcessImage(const char *path)
{
    char *relative_path =
        (char *)strstr(path, path_to_originals) + strlen(path_to_originals);
    originals_names.Append(strdup(relative_path + 1));

    char *thmb_name = ResizeAndSave(path);

    thumbnails_names.Append(strdup(strrchr(thmb_name, '/') + 1));
    free(thmb_name);
}


void ThumbnailsCreator::ProcessDirectory(const char *path)
{
    DIR *dir = opendir(path);
    dirent *curr_file;
    while ((curr_file = readdir(dir)) != 0) {
        char *file_path = str_cat_alloc(strdup(path), "/");
        file_path = str_cat_alloc(file_path, curr_file->d_name);

        if (IsOrdinaryFile(curr_file->d_name)) ProcessImage(file_path);

        if (IsDir(file_path)               &&
            strcmp(curr_file->d_name, ".") &&
            strcmp(curr_file->d_name, "..")
        ) {
            ProcessDirectory(file_path);
        }

        free (file_path);
    }

    closedir(dir);
}


void ThumbnailsCreator::CreateThumbnails()
{
    CheckParams();
    ProcessDirectory(path_to_originals);
}
