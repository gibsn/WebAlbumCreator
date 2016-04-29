#ifndef WEB_PAGE_GENERATOR_H_SENTRY
#define WEB_PAGE_GENERATOR_H_SENTRY

#include <string.h>

#include "List.h"

#define PAGE_HEAD "\
<!DOCTYPE html>\n\
\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\">\n\
    <title>\n\
        %s\n\
    </title>\n\
<link href=\"%s\" rel=\"stylesheet\" type=\"text/css\">\n\
</head>\n\
<body>\n\
<div class=\"album\">\n\
"

#define PAGE_IMAGE "\
<a href=\"%s\">\n\
    <div class=\"photo_box\">\n\
        <img src=\"%s\" alt=\"%s\">\n\
    </div>\n\
</a>\n\
"

#define PAGE_BOTTOM "\
</div>\n\
</body>\n\
</html>"


class WebPageGenerator
{
    char *page_title;
    const char *path_to_web_page;
    int fd;
    List originals_names;
    List thumbnails_names;
    const char *path_to_originals;
    const char *path_to_thumbnails;

    void InitWebPage() const;
    void FinishWebPage() const;

public:
    WebPageGenerator();
    ~WebPageGenerator();

    void SetPageTitle(const char *t) { page_title = strdup(t); }
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
