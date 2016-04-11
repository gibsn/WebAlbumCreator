#ifndef WEB_PAGE_GENERATOR_H_SENTRY
#define WEB_PAGE_GENERATOR_H_SENTRY

#include <string.h>
#include <list>

#define PAGE_HEAD "\
<!DOCTYPE html>\n\
\n\
<html>\n\
<head>\n\
    <title>\n\
        %s\n\
    </title>\n\
<link href=\"%s\" rel=\"stylesheet\" type=\"text/css\" />\n\
</head>\n\
<body>\n\
<div class=\"album\">\n\
"

#define PAGE_IMAGE "\
<a href=\"%s\">\n\
    <div class=\"photo_box\">\n\
        <img src=\"%s\" />\n\
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
    std::list<char *> originals;
    std::list<char *> thumbnails;

    void InitWebPage() const;
    void FinishWebPage() const;

public:
    WebPageGenerator();
    ~WebPageGenerator();

    void SetPageTitle(const char *t) { page_title = strdup(t); }
    void SetPathToWebPage(const char *p) { path_to_web_page = p; }
    void SetOriginals(std::list<char *> l) { originals = l; }
    void SetThumbnails(std::list<char *> l) { thumbnails = l; }

    const char *GetPageTitle() const { return page_title; }
    const char *GetPathToWebPage() const { return path_to_web_page; }

    void GenerateWebPage();
};


#endif