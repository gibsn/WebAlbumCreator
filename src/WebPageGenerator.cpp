#include "WebPageGenerator.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "Exceptions.h"
#include "Common.h"


WebPageGenerator::WebPageGenerator()
    : page_title(0)
{}


WebPageGenerator::~WebPageGenerator()
{
    if (page_title)
        free(page_title);
}


void WebPageGenerator::InitWebPage() const
{
    const char *css = "../css/blue.css";
    int length = strlen(PAGE_HEAD) + strlen(css) + strlen(page_title);
    char *buf = new char[length];
    sprintf(buf, PAGE_HEAD, page_title, css);
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
    {
        perror("path_to_webpage");
    }

    InitWebPage();

    originals_names.ResetCurr();
    thumbnails_names.ResetCurr();
    char *src_path, *thmb_path;
    char *src_name, *thmb_name;

    while (
        (src_name = originals_names.GetNext()) &&
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
