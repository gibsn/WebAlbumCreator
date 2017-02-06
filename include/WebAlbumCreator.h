/*
**  TODO
**      Add ability to manually choose resolution
*/

#ifndef WEB_ALBUM_CREATOR_H_SENTRY
#define WEB_ALBUM_CREATOR_H_SENTRY

struct WebAlbumParams
{
    const char *path_to_archive;             //requried
    const char *path_to_unpack;
    const char *path_to_thumbnails;
    const char *web_page_title;
    const char *path_to_webpage;             //required
    const char *path_to_css;
    const char *relative_path_to_originals;  //required
    const char *relative_path_to_thumbnails; //required
    int quality;

    WebAlbumParams();
};


void CreateWebAlbum(const WebAlbumParams &);


#endif
