#include <stdio.h>

#include "WebAlbumCreator.h"


int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        printf("Example takes exactyl 3 arguments\n");
        return 0;
    }

    try
    {
        Extractor extractor;
        extractor.SetPathToFile(argv[1]);
        extractor.SetPathToUnpack(argv[2]);
        extractor.Extract();

        ThumbnailsCreator thmb_creator;
        thmb_creator.SetPathToOriginals(argv[2]);
        thmb_creator.SetPathToThumbnails(argv[3]);
        thmb_creator.CreateThumbnails();
    }
    catch (Exception &ex)
    {
        ex.Print();
    }

    return 0;
}