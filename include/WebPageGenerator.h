#ifndef WEB_PAGE_GENERATOR_H_SENTRY
#define WEB_PAGE_GENERATOR_H_SENTRY

#include <string.h>

#include "List.h"

using WebAlbumCreator::List;


class WebPageGenerator
{
    char *page_title;
    char *path_to_web_page;
    char *path_to_css;

    List originals_names;
    List thumbnails_names;

    char *path_to_originals;
    char *path_to_thumbnails;

    void CheckParams();
    void InitWebPage(int fd) const;
    void FinishWebPage(int fd) const;

public:
    WebPageGenerator();
    ~WebPageGenerator();

    void SetPageTitle(const char *t) { page_title = strdup(t); }
    void SetPathToCss(const char *t) { path_to_css = strdup(t); }
    void SetPathToWebPage(const char *p) { path_to_web_page = strdup(p); }
    void SetOriginalsNames(const List &l) { originals_names = l; }
    void SetThumbnailsNames(const List &l) { thumbnails_names = l; }
    void SetPathToOriginals(const char *p) { path_to_originals = strdup(p); }
    void SetPathToThumbnails(const char *p) { path_to_thumbnails = strdup(p); }

    const char *GetPageTitle() const { return page_title; }
    const char *GetPathToWebPage() const { return path_to_web_page; }

    void GenerateWebPage();
};


#endif
