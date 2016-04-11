#include "WebPageGenerator.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "Exceptions.h"


WebPageGenerator::WebPageGenerator()
    : page_title(0)
{}


WebPageGenerator::~WebPageGenerator()
{
    if (page_title)
        free(page_title);
}


char *WebPageGenerator::StrCatAlloc(char *s1, const char *s2) const
{
    s1 = (char *)realloc(s1, strlen(s1) + strlen(s2) + 1);
    s1 = strcat(s1, s2);
    return s1;
}


void WebPageGenerator::InitWebPage() const
{
    char *buf = strdup("<html>\n\t<head>\n\t\t<title>");
    buf = StrCatAlloc(buf, page_title);
    buf = StrCatAlloc(buf, "</title>\n\t</head>\n\t<body>\n");
    write(fd, buf, strlen(buf));
    free(buf);
}


void WebPageGenerator::FinishWebPage() const
{
    char *buf = strdup("\t</body>\n</html>");
    write(fd, buf, strlen(buf));
    free(buf);
}


void WebPageGenerator::GenerateWebPage()
{
    if ((fd = open(path_to_web_page, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    {
        perror("path_to_webpage");
    }

    InitWebPage();
    FinishWebPage();

    close(fd);
}