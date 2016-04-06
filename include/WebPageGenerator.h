#ifndef WEB_PAGE_GENERATOR_H_SENTRY
#define WEB_PAGE_GENERATOR_H_SENTRY

#include <string.h>


class WebPageGenerator
{
    char *page_title;
    int fd;
    const char *path_to_originals;
    const char *path_to_thumbnails;
    const char *path_to_web_page;

    void InitWebPage() const;
    void FinishWebPage() const;
    char *StrCatAlloc(char *, const char *) const;

public:
    WebPageGenerator();
    ~WebPageGenerator();

    void SetPageTitle(const char *t) { page_title = strdup(t); }
    void SetPathToOriginals(const char *p) { path_to_originals = p; }
    void SetPathToThumbnails(const char *p) {path_to_thumbnails = p; }
    void SetPathToWebPage(const char *p) { path_to_web_page = p; }

    const char *GetPageTitle() const { return page_title; }
    const char *GetPathToOriginals() const { return path_to_originals; }
    const char *GetPathToThumbnails() const { return path_to_thumbnails; }
    const char *GetPathToWebPage() const { return path_to_web_page; }

    void GenerateWebPage();
};


#endif