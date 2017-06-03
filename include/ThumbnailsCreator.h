#ifndef THUMBNAILS_CREATOR_H_SENTRY
#define THUMBNAILS_CREATOR_H_SENTRY

#include <stdlib.h>
#include <string.h>

#include "Common.h"
#include "List.h"

using WebAlbumCreator::List;


// do not copy objects of this class
struct Img
{
    unsigned char *data;
    int width;
    int height;
    int comp;

    Img(): data(NULL), width(0), height(0), comp(0) {};
    ~Img();
};


class ThumbnailsCreator
{
    char *path_to_originals;
    char *path_to_thumbnails;

    List originals_names;
    List thumbnails_names;

    int quality;

    void CheckParams();

    Img *Resize(const char *img_path) const;
    char *CreatePathForResized(const char *) const;
    void WriteJpeg(const char *img_path, Img *img, int quality) const;

    void ProcessImage(const char *img_path);
    void ProcessDirectory(const char *dir);


public:
    ThumbnailsCreator();
    ~ThumbnailsCreator();

    void SetPathToOriginals(const char *p) { path_to_originals = strdup(p); }
    void SetPathToThumbnails(const char *p) { path_to_thumbnails = strdup(p); }
    void SetQuality(int q) { quality = q; }

    const char *GetPathToOriginals() const { return path_to_originals; }
    const char *GetPathToThumbnails() const { return path_to_thumbnails; }
    const List &GetOriginalsNames() const { return originals_names; }
    const List &GetThumbnailsNames() const { return thumbnails_names; }

    void CreateThumbnails();
};

#endif
