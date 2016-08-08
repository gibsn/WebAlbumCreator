#include "ThumbnailsCreator.h"

#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Exceptions.h"
#include "Common.h"


ThumbnailsCreator::ThumbnailsCreator()
    : path_to_originals(0),
    path_to_thumbnails(0)
{}


void ThumbnailsCreator::CheckParams()
{
    if (path_to_originals == 0)
        throw NoPathToOriginals();

    DIR *dir = opendir(path_to_originals);
    if (dir == 0)
        throw WrongPathToOriginals();
    closedir(dir);

    if (path_to_thumbnails)
    {
        dir = opendir(path_to_thumbnails);
        if (dir == 0)
            throw WrongPathToThumbnails();
        closedir(dir);
    } else
    {
        path_to_thumbnails = ".";
    }
}


//This returns a pointer to allocated dynamic memory
//Must free outside this function
char *ThumbnailsCreator::CreatePathForResized(const char *img_path) const
{
    const char *name = strrchr(img_path, '/');
    char *resized_path = strdup(path_to_thumbnails);
    resized_path = StrCatAlloc(resized_path, name);

    char *extension = strrchr(resized_path, '.');
    *extension = '\0';

    resized_path = StrCatAlloc(resized_path, "_resized.png");

    return resized_path;
}


char *ThumbnailsCreator::ResizeAndSave(const char *img_path) const
{
    int in_w, in_h, in_n;

    Img *src = stbi_load(img_path, &in_w, &in_h, &in_n, 4);

    if (src == 0)
        throw CorruptedImage(img_path);

    float k = sqrt(float(60000) / in_h / in_w);
    int out_w = k * in_w;
    int out_h = k * in_h;
    Img *resized = (Img *)malloc(out_w * out_h * 4);

    stbir_resize_uint8(
        src, in_w, in_h, 0,
        resized, out_w, out_h, 0,
        4);

    char *resized_img_path = CreatePathForResized(img_path);

    stbi_write_png(resized_img_path, out_w, out_h, 4, resized, 0);

    free(resized);
    stbi_image_free(src);

    return resized_img_path;
}


bool ThumbnailsCreator::IsDir(const char *dir) const
{
    DIR *n = opendir(dir);
    if (n)
        closedir(n);

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
    DirEnt *curr_file;
    while ((curr_file = readdir(dir)) != 0)
    {
        char *file_path = StrCatAlloc(strdup(path), "/");
        file_path = StrCatAlloc(file_path, curr_file->d_name);

        if (IsImage(file_path) && IsOrdinaryFile(curr_file->d_name))
            ProcessImage(file_path);

        if (IsDir(file_path) &&
            strcmp(curr_file->d_name, ".") &&
            strcmp(curr_file->d_name, ".."))
        {
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
