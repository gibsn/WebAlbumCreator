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
    char *css = "../css/blue.css";
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

    while (originals.size())
    {
        char *src_name = originals.front();
        originals.pop_front();
        char *thmb_name = thumbnails.front();
        thumbnails.pop_front();

        int length = strlen(PAGE_IMAGE) + strlen(src_name) + strlen(thmb_name);
        char *buf = new char[length];
        sprintf(buf, PAGE_IMAGE, src_name, thmb_name);
        write(fd, buf, strlen(buf));

        delete [] buf;
        free(src_name);
        free(thmb_name);
    }

    FinishWebPage();

    close(fd);
}