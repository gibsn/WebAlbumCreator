#include <stdio.h>

#include "WebAlbumCreator.h"


int main(int argc, const char **argv)
{
    if (argc < 5)
    {
        printf("Example takes exactly 4 arguments\n");
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

        WebPageGenerator web_page_generator;
        web_page_generator.SetPageTitle("Hello, world");
		web_page_generator.SetOriginals(thmb_creator.GetOriginals());
		web_page_generator.SetThumbnails(thmb_creator.GetThumbnails());
        web_page_generator.SetPathToWebPage(argv[4]);
        web_page_generator.GenerateWebPage();

    }
    catch (Exception &ex)
    {
        ex.Print();
    }

    return 0;
}
