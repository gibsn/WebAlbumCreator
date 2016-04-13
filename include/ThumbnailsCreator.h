#ifndef THUMBNAILS_CREATOR_H_SENTRY
#define THUMBNAILS_CREATOR_H_SENTRY

#include "List.h"


class ThumbnailsCreator
{
    const char *path_to_originals;
    const char *path_to_thumbnails;
    List originals;
    List thumbnails;

    void CheckPaths() const;
    char *ProcessPhoto(char *) const;
    char *CreateFullPath(const char *) const;
    char *CreateNameForResized(const char *) const;

public:
    ThumbnailsCreator();
    ~ThumbnailsCreator();

    void SetPathToOriginals(const char *p) {path_to_originals = p; }
    void SetPathToThumbnails(const char *p) {path_to_thumbnails = p; }

    const char *GetPathToOriginals() const { return path_to_originals; }
    const char *GetPathToThumbnails() const { return path_to_thumbnails; }
    const List &GetOriginals() const { return originals; }
    const List &GetThumbnails() const { return thumbnails; }

    void CreateThumbnails();
};

#endif
