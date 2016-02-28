#ifndef WEB_PAGE_GENERATOR_H_SENTRY
#define WEB_PAGE_GENERATOR_H_SENTRY


class WebPageGenerator
{
    const char *path_to_originals;
    const char *path_to_thumbnails;
    const char *path_to_web_page;

public:
    WebPageGenerator();

    void SetPathToOriginals(const char *p) { path_to_originals = p; }
    void SetPathToThumbnails(const char *p) {path_to_thumbnails = p; }
    void SetPathToWebPage(const char *p) { path_to_web_page = p; }

    const char *GetPathToOriginals() const { return path_to_originals; }
    const char *GetPathToThumbnails() const { return path_to_thumbnails; }
    const char *GetPathToWebPage() const { return path_to_web_page; }

    void GenerateWebPage();
};


#endif