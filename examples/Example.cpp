#include <stdio.h>

#include "WebAlbumCreator.h"


int main(int argc, const char **argv)
{
    if (argc < 5)
    {
        printf("Example takes exactly 4 arguments\n");
        return 0;
    }

    WebAlbumParams params;

    params.path_to_archive = argv[1];
    params.path_to_unpack = argv[2];
    params.path_to_thumbnails = argv[3];
    params.web_page_title = "Hello, world!";
    params.path_to_webpage = argv[4];

    WebAlbumCreator::CreateWebAlbum(params);

    return 0;
}
