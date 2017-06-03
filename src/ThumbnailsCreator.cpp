#include "ThumbnailsCreator.h"

#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#include "jpeglib.h"

#include "Exceptions.h"


Img::~Img()
{
    stbi_image_free(data);
}


ThumbnailsCreator::ThumbnailsCreator()
    : path_to_originals(0),
    path_to_thumbnails(0),
    quality(0)
{}


ThumbnailsCreator::~ThumbnailsCreator()
{
    free(path_to_originals);
    free(path_to_thumbnails);
}


void ThumbnailsCreator::CheckParams()
{
    if (quality == 0) quality = 75;
    if (!path_to_originals) throw Wac::NoPathToOriginals();

    DIR *dir = opendir(path_to_originals);
    if (!dir) throw Wac::WrongPathToOriginals();
    closedir(dir);

    dir = opendir(path_to_thumbnails);
    if (!dir) throw Wac::WrongPathToThumbnails();
    closedir(dir);
}


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


void ThumbnailsCreator::WriteJpeg(const char *path, Img *img, int quality) const
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    // TODO: throw an exception here
    FILE *out = fopen(path, "wb");
    if (!out) {
        perror("path");
        exit(EXIT_FAILURE);
    }

    jpeg_stdio_dest(&cinfo, out);

    cinfo.image_width = img->width;
    cinfo.image_height = img->height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer[1];
    int row_stride = cinfo.image_width * cinfo.input_components;
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &(img->data)[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    fclose(out);
}


Img *ThumbnailsCreator::Resize(const char *img_path) const
{
    Img src;

    src.data = stbi_load(img_path, &src.width, &src.height, &src.comp, 3);

    if (!src.data) throw Wac::CorruptedImage(img_path);

    float k = sqrt(float(60000) / src.height / src.width);
    Img *resized = new Img;
    resized->width = k * src.width;
    resized->height = k * src.height;
    resized->data = (unsigned char *)malloc(resized->width * resized->height * 3);

    stbir_resize_uint8(
        src.data, src.width, src.height, 0,
        resized->data, resized->width, resized->height, 0,
        3);

    return resized;
}


void ThumbnailsCreator::ProcessImage(const char *img_path)
{
    char *relative_path = (char *)strstr(img_path, path_to_originals) + strlen(path_to_originals);
    originals_names.Append(strdup(relative_path + 1));

    Img *resized = Resize(img_path);

    char *thmb_name = CreatePathForResized(img_path);
    WriteJpeg(thmb_name, resized, quality);

    thumbnails_names.Append(strdup(strrchr(thmb_name, '/') + 1));

    delete resized;
    free(thmb_name);
}


void ThumbnailsCreator::ProcessDirectory(const char *path)
{
    DIR *dir = opendir(path);

    dirent *curr_file;
    while ((curr_file = readdir(dir)) != 0) {
        char *file_path = str_cat_alloc(strdup(path), "/");
        file_path = str_cat_alloc(file_path, curr_file->d_name);

        if (is_ordinary_file(curr_file->d_name)) {
            ProcessImage(file_path);
        }

        if (is_dir(file_path)              &&
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
