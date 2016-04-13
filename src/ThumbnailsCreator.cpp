#include "ThumbnailsCreator.h"

#include <dirent.h>
#include <string.h>

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


void ThumbnailsCreator::CheckPaths() const
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
    }
}


//This returns a pointer to allocated dynamic memory
//Must free outside this function
char *ThumbnailsCreator::CreateNameForResized(const char *name) const
{
    const char *i = strrchr(name, '.');
	int length = (int)(i - name) + strlen("_resized") + strlen(path_to_thumbnails) + strlen(".png") + 2;
    char *new_name = (char *)malloc(length);

    new_name[0] = '\0';
    if (path_to_thumbnails)
    {
        strcat(new_name, path_to_thumbnails);
        strcat(new_name, "/");
    }
    strncat(new_name, name, (int)(i - name));
    strcat(new_name, "_resized");
    strcat(new_name, ".png");

    return new_name;
}


//This returns a pointer to allocated dynamic memory
//Must free outside this function
char *ThumbnailsCreator::CreateFullPath(const char *name) const
{
    int length = strlen(path_to_originals) + strlen(name) + 2;
    char *full_path = (char *)malloc(length);
    full_path[0] = '\0';
    strcat(full_path, path_to_originals);
    strcat(full_path, "/");
    strcat(full_path, name);

    return full_path;
}


char *ThumbnailsCreator::ProcessPhoto(char *name) const
{
    int in_w, in_h, in_n;

    char *full_path = CreateFullPath(name);
    Img *src = stbi_load(full_path, &in_w, &in_h, &in_n, 4);
    free(full_path);
    if (src == 0)
        throw CorruptedImage(name);

    float k = sqrt(float(60000) / in_h / in_w);
    int out_w = k * in_w;
    int out_h = k * in_h;
    Img *resized = (Img *)malloc(out_w * out_h * 4);

    stbir_resize_uint8(
        src, in_w, in_h, 0,
        resized, out_w, out_h, 0,
        4);

    char *new_name = CreateNameForResized(name);

    stbi_write_png(new_name, out_w, out_h, 4, resized, 0);

    free(resized);
    stbi_image_free(src);

    return new_name;
}


void ThumbnailsCreator::CreateThumbnails()
{
    CheckPaths();
    DIR *dir = opendir(path_to_originals);
    DirEnt *curr_file;
    while ((curr_file = readdir(dir)) != 0)
    {
        char *src_name = curr_file->d_name;
        if (IsImage(src_name))
        {
            char *thmb_name = ProcessPhoto(src_name);
            char *src_full_path = strdup(path_to_originals);

            src_full_path = StrCatAlloc(src_full_path, "/");
            src_full_path = StrCatAlloc(src_full_path, src_name);
            thumbnails.Append(realpath(thmb_name, 0));
            originals.Append(realpath(src_full_path, 0));

            free(thmb_name);
            free(src_full_path);
        }
    }
    closedir(dir);
}


ThumbnailsCreator::~ThumbnailsCreator()
{}
