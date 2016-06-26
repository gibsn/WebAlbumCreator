#ifndef WEB_PAGE_GENERATOR_H_SENTRY
#define WEB_PAGE_GENERATOR_H_SENTRY

#include <string.h>

#include "List.h"


class WebPageGenerator
{
    const char *page_title;
    const char *path_to_web_page;
    const char *path_to_css;
    int fd;
    List originals_names;
    List thumbnails_names;
    const char *path_to_originals;
    const char *path_to_thumbnails;

    void CheckParams();
    void InitWebPage() const;
    void FinishWebPage() const;

public:
    WebPageGenerator();
    ~WebPageGenerator();

    void SetPageTitle(const char *t) { page_title = strdup(t); }
    void SetPathToCss(const char *t) { path_to_css = t; }
    void SetPathToWebPage(const char *p) { path_to_web_page = p; }
    void SetOriginalsNames(const List &l) { originals_names = l; }
    void SetThumbnailsNames(const List &l) { thumbnails_names = l; }
    void SetPathToOriginals(const char *p) { path_to_originals = p; }
    void SetPathToThumbnails(const char *p) { path_to_thumbnails = p; }

    const char *GetPageTitle() const { return page_title; }
    const char *GetPathToWebPage() const { return path_to_web_page; }

    void GenerateWebPage();
};


#endif
