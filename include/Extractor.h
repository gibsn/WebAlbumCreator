#ifndef EXTRACTOR_H_SENTRY
#define EXTRACTOR_H_SENTRY

#include <string.h>


#define PHOTO_TOKEN_LENGTH 16


struct archive;
struct archive_entry;

class Extractor
{
    char *path_to_unpack;
    char *path_to_file;

    static archive *SetUpRead();
    static void FinishRead(archive *in);

    static archive *SetUpWrite();
    static void FinishWrite(archive *out);

    static void CopyData(archive *in, archive *out);

    void SetUpPathToUnpack(archive_entry *);
    void CheckParams();

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
