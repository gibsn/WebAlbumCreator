#include "Common.h"

#include <stdlib.h>
#include <string.h>


char *StrCatAlloc(char *s1, const char *s2)
{
    s1 = (char *)realloc(s1, strlen(s1) + strlen(s2) + 1);
    s1 = strcat(s1, s2);
    return s1;
}


int IsImage(const char *name)
{
    int i = strlen(name);
    while (name[i] != '.' && i >= 0)
        --i;
    if (i < 0)
        return 0;

    if (strcmp(name + i + 1, "jpg") == 0 ||
        strcmp(name + i + 1, "JPG") == 0 ||
        strcmp(name + i + 1, "bmp") == 0 ||
        strcmp(name + i + 1, "BMP") == 0 ||
        strcmp(name + i + 1, "png") == 0 ||
        strcmp(name + i + 1, "PNG") == 0)
        return 1;
    else
        return 0;
}