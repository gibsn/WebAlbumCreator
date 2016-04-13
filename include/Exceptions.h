#ifndef EXCEPTIONS_H_SENTRY
#define EXCEPTIONS_H_SENTRY

typedef struct archive Archive;
typedef struct archive_entry ArchiveEntry;


class Exception
{

public:
    virtual void Print() = 0;
    virtual ~Exception() {};
};


class SystemEx: public Exception
{
    const char *text;

public:
    virtual void Print() = 0;
    const char *GetText() const { return text; }
    void SetText(const char *t) { text = t; }
    virtual ~SystemEx() {};
};


class LibArchiveEx : public SystemEx
{

public:
    LibArchiveEx(Archive *);
    void Print();
    ~LibArchiveEx() {};
};


class StbEx : public SystemEx
{

public:
    StbEx();
    void Print();
    ~StbEx() {};
};


class ReadDirEx: public SystemEx
{

public:
    ReadDirEx(const char *);
    void Print();
    ~ReadDirEx() {};
};


class UserEx : public Exception
{

public:
    ~UserEx() {};
};


class WrongPathToArchive : public UserEx
{

public:
    WrongPathToArchive() {};
    void Print();
};


class NoPathToArchive : public UserEx
{

public:
    NoPathToArchive() {};
    void Print();
};


class WrongPathToUnpack : public UserEx
{

public:
    WrongPathToUnpack() {};
    void Print();
};


class WrongPathToOriginals : public UserEx
{

public:
    WrongPathToOriginals() {};
    void Print();
};


class NoPathToOriginals : public UserEx
{

public:
    NoPathToOriginals() {};
    void Print();
};


class WrongPathToThumbnails : public UserEx
{

public:
    WrongPathToThumbnails() {};
    void Print();
};


class NoPathToThumbnails : public UserEx
{

public:
	NoPathToThumbnails() {};
	void Print();
};


class CorruptedImage: public UserEx
{
    const char *text;

public:
    CorruptedImage(const char *);
    void Print();
};


#endif
