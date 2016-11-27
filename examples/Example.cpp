#include <stdio.h>

#include "WebAlbumCreator.h"


int main(int argc, const char **argv)
{
    if (argc < 7) {
        printf("Usage: path_to_archive path_to_store_photos "
               "path_to_store_thumbs path_to_webpage "
               "relative_path_to_originals relative_path_to_thumbs\n");
        return 0;
    }

    WebAlbumParams params;

    params.path_to_archive = argv[1];
    params.path_to_unpack = argv[2];
    params.path_to_thumbnails = argv[3];
    params.path_to_webpage = argv[4];
    params.relative_path_to_originals = argv[5];
    params.relative_path_to_thumbnails = argv[6];
    params.web_page_title = "Photoalbum";
    params.path_to_css = "../css/blue.css";
    params.quality = 90;

    CreateWebAlbum(params);

    return 0;
}
