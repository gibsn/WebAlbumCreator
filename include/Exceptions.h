#ifndef WAC_EXCEPTIONS_H_SENTRY
#define WAC_EXCEPTIONS_H_SENTRY

#include <string.h>
#include <stdlib.h>


struct archive;
struct archive_entry;

namespace Wac {

class Exception
{
    char *err_msg;

public:
    Exception(): err_msg(NULL) {}
    Exception(const char *t) { err_msg = strdup(t); }
    virtual ~Exception() { free(err_msg); }

    virtual const char *GetErrMsg() const { return err_msg; }
    virtual void SetErrMsg(const char *t) { if (t) err_msg = strdup(t); }
};


class SystemEx: public Exception
{

public:
    SystemEx() {}
    SystemEx(const char *t): Exception(t) {}
};


class LibArchiveEx : public Exception
{

public:
    LibArchiveEx(archive *);
    ~LibArchiveEx() {};
};


class StbEx : public Exception
{

public:
    ~StbEx() {};
};


class UserEx : public Exception
{

public:
    ~UserEx() {};
};


class WrongPathToArchive : public UserEx
{

public:
    const char *GetErrMsg() const;
};


class NoPathToArchive : public UserEx
{

public:
    const char *GetErrMsg() const;
};


class WrongPathToUnpack : public UserEx
{

public:
    const char *GetErrMsg() const;
};


class WrongPathToOriginals : public UserEx
{

public:
    const char *GetErrMsg() const;
};


class NoPathToOriginals : public UserEx
{

public:
    const char *GetErrMsg() const;
};


class WrongPathToThumbnails : public UserEx
{

public:
    const char *GetErrMsg() const;
};


class NoPathToThumbnails : public UserEx
{

public:
    const char *GetErrMsg() const;
};


class CorruptedImage: public UserEx
{

public:
    CorruptedImage(const char *t);
};

class WrongPathToWebPage: public UserEx
{

public:
    const char *GetErrMsg() const;
};


class NoPathToWebPage: public UserEx
{

public:
    const char *GetErrMsg() const;
};

};

#endif
