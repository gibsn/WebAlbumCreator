#ifndef EXTRACTOR_H_SENTRY
#define EXTRACTOR_H_SENTRY

#include <string.h>

#include "Common.h"


class Extractor
{
    char *path_to_unpack;
    char *path_to_file;

    void CopyData(archive *, archive *) const;
    archive *SetUpRead() const;
    archive *SetUpWrite() const;
    void SetUpPathToUnpack(archive_entry *);
    void CheckParams();
    void Finish(archive *, archive *) const;

public:
    Extractor();
    ~Extractor();

    void SetPathToUnpack(const char *p) { path_to_unpack = strdup(p); }
    void SetPathToFile(const char *p) { path_to_file = strdup(p); }

    const char *GetPathToUnpack() const { return path_to_unpack; }
    const char *GetPathToFile() const { return path_to_file; }

    void Extract();
};

#endif
