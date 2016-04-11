#ifndef THUMBNAILS_CREATOR_H_SENTRY
#define THUMBNAILS_CREATOR_H_SENTRY

#include <list>


class ThumbnailsCreator
{
    const char *path_to_originals;
    const char *path_to_thumbnails;
    std::list<char *> originals;
    std::list<char *> thumbnails;

    void CheckPaths() const;
    char *ProcessPhoto(char *) const;
    char *CreateFullPath(const char *) const;
    char *CreateNameForResized(const char *) const;

public:
    ThumbnailsCreator();

    void SetPathToOriginals(const char *p) {path_to_originals = p; }
    void SetPathToThumbnails(const char *p) {path_to_thumbnails = p; }

    const char *GetPathToOriginals() const { return path_to_originals; }
    const char *GetPathToThumbnails() const { return path_to_thumbnails; }
    std::list<char *> GetOriginals() const { return originals; }
    std::list<char *> GetThumbnails() const { return thumbnails; }

    void CreateThumbnails();
};

#endif
