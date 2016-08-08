/*
**  TODO
**      Decrease size of thumbnails
**      Add ability to manually choose resolution
**      Make exceptions for WebAlbumCreator
**      Move paths creation to static method of main class
**      Refactor main class
**      List.h
*/

#ifndef WEB_ALBUM_CREATOR_H_SENTRY
#define WEB_ALBUM_CREATOR_H_SENTRY

#include "Extractor.h"
#include "ThumbnailsCreator.h"
#include "WebPageGenerator.h"
#include "Exceptions.h"


struct WebAlbumParams
{
    const char *path_to_archive;
    const char *path_to_unpack;
    const char *path_to_thumbnails;
    const char *web_page_title;
    const char *path_to_webpage;
    const char *path_to_css;
    const char *relative_path_to_originals;
    const char *relative_path_to_thumbnails;

    WebAlbumParams();
};


class WebAlbumCreator
{

public:
    WebAlbumCreator() {};
    ~WebAlbumCreator() {};

    static void CreateWebAlbum(const WebAlbumParams &);
};


#endif
