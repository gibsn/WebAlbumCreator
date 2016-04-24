#include "WebAlbumCreator.h"


void WebAlbumCreator::CreateWebAlbum(const WebAlbumParams &params)
{
    try
    {
        Extractor extractor;
        extractor.SetPathToFile(params.path_to_archive);
        extractor.SetPathToUnpack(params.path_to_unpack);
        extractor.Extract();

        ThumbnailsCreator thmb_creator;
        thmb_creator.SetPathToOriginals(params.path_to_unpack);
        thmb_creator.SetPathToThumbnails(params.path_to_thumbnails);
        thmb_creator.CreateThumbnails();

        WebPageGenerator web_page_generator;
        web_page_generator.SetPageTitle(params.web_page_title);
        web_page_generator.SetOriginals(thmb_creator.GetOriginals());
        web_page_generator.SetThumbnails(thmb_creator.GetThumbnails());
        web_page_generator.SetPathToWebPage(params.path_to_webpage);
        web_page_generator.GenerateWebPage();

    }
    catch (Exception &ex)
    {
        ex.Print();
    }
}

