#ifndef WAC_EXCEPTIONS_H_SENTRY
#define WAC_EXCEPTIONS_H_SENTRY

#include <string.h>
#include <stdlib.h>


struct archive;
struct archive_entry;

namespace Wac {

class WebAlbumCreatorEx
{

public:
    virtual const char *GetErrMsg() const = 0;
    virtual ~WebAlbumCreatorEx() {};
};


class SystemEx: public WebAlbumCreatorEx
{
    char *text;

public:
    SystemEx(): text(NULL) {}
    virtual ~SystemEx() { if (text) free(text); }

    const char *GetErrMsg() const { return text; }
    void SetText(const char *t) { text = strdup(t); }
};


class LibArchiveEx : public SystemEx
{

public:
    LibArchiveEx(archive *);
    ~LibArchiveEx() {};
};


class StbEx : public SystemEx
{

public:
    StbEx() {};
    ~StbEx() {};
};


class ReadDirEx: public SystemEx
{

public:
    ReadDirEx(const char *);
    ~ReadDirEx() {};
};


class UserEx : public WebAlbumCreatorEx
{

public:
    ~UserEx() {};
};


class WrongPathToArchive : public UserEx
{

public:
    WrongPathToArchive() {};

    const char *GetErrMsg() const;
};


class NoPathToArchive : public UserEx
{

public:
    NoPathToArchive() {};

    const char *GetErrMsg() const;
};


class WrongPathToUnpack : public UserEx
{

public:
    WrongPathToUnpack() {};

    const char *GetErrMsg() const;
};


class WrongPathToOriginals : public UserEx
{

public:
    WrongPathToOriginals() {};

    const char *GetErrMsg() const;
};


class NoPathToOriginals : public UserEx
{

public:
    NoPathToOriginals() {};

    const char *GetErrMsg() const;
};


class WrongPathToThumbnails : public UserEx
{

public:
    WrongPathToThumbnails() {};

    const char *GetErrMsg() const;
};


class NoPathToThumbnails : public UserEx
{

public:
    NoPathToThumbnails() {};

    const char *GetErrMsg() const;
};


class CorruptedImage: public UserEx
{
    char *text;

public:
    CorruptedImage(const char *);
    ~CorruptedImage() { if (text) free(text); }

    const char *GetErrMsg() const { return text; };
};

class WrongPathToWebPage: public UserEx
{

public:
	WrongPathToWebPage() {};

    const char *GetErrMsg() const;
};


class NoPathToWebPage: public UserEx
{

public:
	NoPathToWebPage() {};

    const char *GetErrMsg() const;
};

};
#endif
