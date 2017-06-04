#include "WebPageGenerator.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

using WebAlbumCreator::List;


WebPageGenerator::WebPageGenerator()
    : page_title(0),
    path_to_web_page(0),
    path_to_css(0),
    path_to_originals(0),
    path_to_thumbnails(0)
{}


WebPageGenerator::~WebPageGenerator()
{
    free(page_title);
    free(path_to_web_page);
    free(path_to_css);
    free(path_to_originals);
    free(path_to_thumbnails);
}


void WebPageGenerator::CheckParams()
{
    if (!page_title) page_title = strdup("Photoalbum");
    if (!path_to_web_page) throw Wac::NoPathToWebPage();
    if (!path_to_originals) throw Wac::NoPathToOriginals();
    if (!path_to_thumbnails) throw Wac::NoPathToThumbnails();
    if (!path_to_css) path_to_css = strdup("");
}


void WebPageGenerator::InitWebPage(int fd) const
{
    int length = strlen(PAGE_HEAD) + strlen(path_to_css) + strlen(page_title);
    char *buf = (char *)malloc(length);

    sprintf(buf, PAGE_HEAD, page_title, path_to_css);

    int ret = write(fd, buf, strlen(buf));
    free(buf);

    if (ret == -1) {
        if (errno == ENOSPC) {
            throw Wac::NoSpace(strerror(errno));
        }

        throw Wac::SystemEx(strerror(errno));
    }
}


void WebPageGenerator::FinishWebPage(int fd) const
{
    if (write(fd, PAGE_BOTTOM, sizeof PAGE_BOTTOM) == -1) {
        if (errno == ENOSPC) {
            throw Wac::NoSpace(strerror(errno));
        }

        throw Wac::SystemEx(strerror(errno));
    }
}


void WebPageGenerator::GeneratePhotoEntry(int fd, const char *src_name, const char *thmb_name)
{
    char *src_path = strdup(path_to_originals);
    src_path = str_cat_alloc(src_path, "/");
    src_path = str_cat_alloc(src_path, src_name);

    char *thmb_path = strdup(path_to_thumbnails);
    thmb_path = str_cat_alloc(thmb_path, "/");
    thmb_path = str_cat_alloc(thmb_path, thmb_name);

    int length = strlen(PAGE_IMAGE) + strlen(src_path) + 2 * strlen(thmb_path);
    char *buf = (char *)malloc(length);
    sprintf(buf, PAGE_IMAGE, src_path, thmb_path, thmb_path);
    free(src_path);
    free(thmb_path);

    int ret = write(fd, buf, strlen(buf));
    free(buf);

    if (ret == -1) {
        if (errno == ENOSPC) {
            throw Wac::NoSpace(strerror(errno));
        }

        throw Wac::SystemEx(strerror(errno));
    }
}


void WebPageGenerator::GenerateWebPage()
{
    CheckParams();

    int fd;
    if ((fd = open(path_to_web_page, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
        if (errno == ENOSPC) {
            throw Wac::NoSpace(strerror(errno));
        } else if (errno == ENOENT) {
            throw Wac::WrongPathToWebPage(strerror(errno));
        }

        throw Wac::SystemEx(strerror(errno));
    }

    InitWebPage(fd);

    originals_names.ResetCurr();
    thumbnails_names.ResetCurr();

    char *src_name, *thmb_name;
    try {
        while ((src_name = originals_names.GetNext()) &&
               (thmb_name = thumbnails_names.GetNext())
        ) {
            GeneratePhotoEntry(fd, src_name, thmb_name);
        }

        FinishWebPage(fd);
        close(fd);
    } catch (Wac::Exception &) {
        close(fd);
        throw;
    }

}
