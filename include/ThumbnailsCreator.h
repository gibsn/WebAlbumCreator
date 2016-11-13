#ifndef THUMBNAILS_CREATOR_H_SENTRY
#define THUMBNAILS_CREATOR_H_SENTRY

#include <stdlib.h>
#include <string.h>

#include "Common.h"
#include "List.h"

using WebAlbumCreator::List;

class ThumbnailsCreator
{
    char *path_to_originals;
    char *path_to_thumbnails;
    List originals_names;
    List thumbnails_names;
    int quality;

    void CheckParams();
    char *ResizeAndSave(const char *) const;
    void ProcessImage(const char *);
    void ProcessDirectory(const char *);
    bool IsDir(const char *) const;
    bool IsOrdinaryFile (const char *) const;
    char *CreatePathForResized(const char *) const;
    void WriteJpeg(const char *, Img *, int, int, int) const;

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
