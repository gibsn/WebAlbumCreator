#include <stdio.h>

#include "WebAlbumCreator.h"


int main(int argc, const char **argv)
{
    if (argc < 7)
    {
        printf("Example takes exactly 6 arguments\n");
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

    WebAlbumCreator::CreateWebAlbum(params);

    return 0;
}
