/*
**  TODO
**      Decrease size of thumbnails
**      Add ability to manually choose resolution
**      Make path exceptions more informative
**      Make exceptions for WebPageGenerator
**      Make exceptions for WebAlbumCreator
**      Make css variable
**      Move paths creation to static method of main class
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
    const char *relative_path_to_originals;
    const char *relative_path_to_thumbnails;
};


class WebAlbumCreator
{

public:
    WebAlbumCreator() {};
    ~WebAlbumCreator() {};

    static void CreateWebAlbum(const WebAlbumParams &);
};


#endif
