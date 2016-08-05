#ifndef THUMBNAILS_CREATOR_H_SENTRY
#define THUMBNAILS_CREATOR_H_SENTRY

#include <stdlib.h>

#include "List.h"


class ThumbnailsCreator
{
    char *path_to_originals;
    char *path_to_thumbnails;
    List originals_names;
    List thumbnails_names;

    void CheckPaths() const;
    char *ResizeAndSave(const char *) const;
    void ProcessImage(const char *);
    void ProcessDirectory(const char *);
    bool IsDir(const char *) const;
    bool IsOrdinaryFile (const char *) const;
    char *CreatePathForResized(const char *) const;

public:
    ThumbnailsCreator();
    ~ThumbnailsCreator();

    void SetPathToOriginals(const char *p)
        { path_to_originals = realpath(p, 0); }
    void SetPathToThumbnails(const char *p)
        { path_to_thumbnails = realpath(p, 0); }

    const char *GetPathToOriginals() const { return path_to_originals; }
    const char *GetPathToThumbnails() const { return path_to_thumbnails; }
    const List &GetOriginalsNames() const { return originals_names; }
    const List &GetThumbnailsNames() const { return thumbnails_names; }

    void CreateThumbnails();
};

#endif
