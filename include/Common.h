#ifndef COMMON_H_SENTRY
#define COMMON_H_SENTRY

typedef struct dirent DirEnt;
typedef struct archive Archive;
typedef struct archive_entry ArchiveEntry;
typedef unsigned char Img;


char *StrCatAlloc(char *, const char *);
int IsImage(const char *);


#endif