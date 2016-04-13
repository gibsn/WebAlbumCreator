#ifndef THUMBNAILS_CREATOR_H_SENTRY
#define THUMBNAILS_CREATOR_H_SENTRY

#include <stdlib.h>

#include "List.h"


class ThumbnailsCreator
{
    char *path_to_originals;
    char *path_to_thumbnails;
    List originals;
    List thumbnails;

    void CheckPaths() const;
    char *ResizeAndSave(const char *) const;
    void ProcessImage(const char *);
    void ProcessDirectory(const char *);
    int IsDir(const char *) const;
	int IsOrdinaryFile (const char *) const;
    char *CreatePathForResized(const char *) const;

public:
    ThumbnailsCreator();
    ~ThumbnailsCreator();

    void SetPathToOriginals(const char *p)
        {path_to_originals = realpath(p, 0); }
    void SetPathToThumbnails(const char *p)
        {path_to_thumbnails = realpath(p, 0); }

    const char *GetPathToOriginals() const { return path_to_originals; }
    const char *GetPathToThumbnails() const { return path_to_thumbnails; }
    const List &GetOriginals() const { return originals; }
    const List &GetThumbnails() const { return thumbnails; }

    void CreateThumbnails();
};

#endif
