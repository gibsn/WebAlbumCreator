#include "WebPageGenerator.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "Exceptions.h"
#include "Common.h"

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


WebPageGenerator::WebPageGenerator()
    : page_title(0)
{}


WebPageGenerator::~WebPageGenerator()
{
    // if (page_title)
    //     free(page_title);
}


void WebPageGenerator::CheckParams()
{
    if (!page_title)
        page_title = "Photoalbum";
    if (!path_to_css)
        path_to_css = "";
}


void WebPageGenerator::InitWebPage() const
{
    int length = strlen(PAGE_HEAD) + strlen(path_to_css) + strlen(page_title);
    char *buf = new char[length];
    sprintf(buf, PAGE_HEAD, page_title, path_to_css);
    write(fd, buf, strlen(buf));
    delete [] buf;
}


void WebPageGenerator::FinishWebPage() const
{
    write(fd, PAGE_BOTTOM, strlen(PAGE_BOTTOM));
}


void WebPageGenerator::GenerateWebPage()
{
    if ((fd = open(path_to_web_page, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
        throw WrongPathToWebPage();

    CheckParams();
    InitWebPage();

    originals_names.ResetCurr();
    thumbnails_names.ResetCurr();
    char *src_path, *thmb_path;
    char *src_name, *thmb_name;

    while ((src_name = originals_names.GetNext()) &&
           (thmb_name = thumbnails_names.GetNext()))
    {
        char *src_path = strdup(path_to_originals);
        src_path = StrCatAlloc(src_path, "/");
        src_path = StrCatAlloc(src_path, src_name);

        char *thmb_path = strdup(path_to_thumbnails);
        thmb_path = StrCatAlloc(thmb_path, "/");
        thmb_path = StrCatAlloc(thmb_path, thmb_name);

        int length = strlen(PAGE_IMAGE) + strlen(src_path) + 2 * strlen(thmb_path);
        char *buf = new char[length];
        sprintf(buf, PAGE_IMAGE, src_path, thmb_path, thmb_path);
        write(fd, buf, strlen(buf));

        delete [] buf;
        free(src_path);
        free(thmb_path);
    }

    FinishWebPage();

    close(fd);
}
