#include "Common.h"

#include <stdlib.h>
#include <string.h>


char *StrCatAlloc(char *s1, const char *s2)
{
    s1 = (char *)realloc(s1, strlen(s1) + strlen(s2) + 1);
    s1 = strcat(s1, s2);
    return s1;
}


bool IsImage(const char *name)
{
    char *c;
    if (!(c = (char *)strrchr(name, '.'))) return false;

    if (c == name + strlen(name) - 1 ||
        strcmp(c + 1, "jpg") == 0    ||
        strcmp(c + 1, "JPG") == 0    ||
        strcmp(c + 1, "bmp") == 0    ||
        strcmp(c + 1, "BMP") == 0    ||
        strcmp(c + 1, "png") == 0    ||
        strcmp(c + 1, "PNG") == 0
    ) {
        return true;
    } else {
        return false;
    }
}
