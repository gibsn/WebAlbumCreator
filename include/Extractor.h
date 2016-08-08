#ifndef EXTRACTOR_H_SENTRY
#define EXTRACTOR_H_SENTRY

#include "Common.h"


class Extractor
{
    const char *path_to_unpack;
    const char *path_to_file;

    void CopyData(Archive *, Archive *) const;
    Archive *SetUpRead() const;
    Archive *SetUpWrite() const;
    void SetUpPathToUnpack(ArchiveEntry *);
    void CheckParams();
    void Finish(Archive *, Archive *) const;

public:
    Extractor();

    void SetPathToUnpack(const char *p) { path_to_unpack = p; }
    void SetPathToFile(const char *p) { path_to_file = p; }

    const char *GetPathToUnpack() const { return path_to_unpack; }
    const char *GetPathToFile() const { return path_to_file; }

    void Extract();
};

#endif
