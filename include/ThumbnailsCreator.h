#ifndef THUMBNAILS_CREATOR_H_SENTRY
#define THUMBNAILS_CREATOR_H_SENTRY

typedef struct dirent DirEnt;
typedef unsigned char Img;


class ThumbnailsCreator
{
    const char *path_to_originals;
    const char *path_to_thumbnails;

    void CheckPaths() const;
    void ProcessPhoto(char *) const;
    int IsImage(const char *) const;
    char *CreateFullPath(const char *) const;
    char *CreateNameForResized(const char *) const;

public:
    ThumbnailsCreator();

    void SetPathToOriginals(const char *p) {path_to_originals = p; }
    void SetPathToThumbnails(const char *p) {path_to_thumbnails = p; }

    const char *GetPathToOriginals() const { return path_to_originals; }
    const char *GetPathToThumbnails() const { return path_to_thumbnails; }

    void CreateThumbnails() const;
};


#endif