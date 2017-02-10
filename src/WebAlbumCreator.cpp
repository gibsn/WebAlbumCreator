#include "WebAlbumCreator.h"

#include <stdio.h>

#include "Extractor.h"
#include "ThumbnailsCreator.h"
#include "WebPageGenerator.h"
#include "Exceptions.h"


WebAlbumParams::WebAlbumParams()
    : path_to_archive(0),
    path_to_unpack(0),
    path_to_thumbnails(0),
    web_page_title(0),
    path_to_webpage(0),
    path_to_css(0),
    relative_path_to_originals(0),
    relative_path_to_thumbnails(0),
    quality(0)
{
}


static void CheckParams(const WebAlbumParams &params)
{
    if (!params.path_to_archive) throw NoPathToArchive();
    if (!params.path_to_webpage) throw NoPathToWebPage();
    if (!params.relative_path_to_originals) throw NoPathToOriginals();
    if (!params.relative_path_to_thumbnails) throw NoPathToThumbnails();
}


void CreateWebAlbum(const WebAlbumParams &params)
{
    CheckParams(params);

    Extractor extractor;
    extractor.SetPathToFile(params.path_to_archive);
    extractor.SetPathToUnpack(params.path_to_unpack);
    extractor.Extract();

    ThumbnailsCreator thmb_creator;
    thmb_creator.SetPathToOriginals(extractor.GetPathToUnpack());
    thmb_creator.SetPathToThumbnails(params.path_to_thumbnails);
    thmb_creator.SetQuality(params.quality);
    thmb_creator.CreateThumbnails();

    WebPageGenerator web_page_generator;
    web_page_generator.SetPageTitle(params.web_page_title);
    web_page_generator.SetOriginalsNames(thmb_creator.GetOriginalsNames());
    web_page_generator.SetThumbnailsNames(thmb_creator.GetThumbnailsNames());
    web_page_generator.SetPathToOriginals(params.relative_path_to_originals);
    web_page_generator.SetPathToThumbnails(params.relative_path_to_thumbnails);
    web_page_generator.SetPathToWebPage(params.path_to_webpage);
    web_page_generator.SetPathToCss(params.path_to_css);
    web_page_generator.GenerateWebPage();
}

