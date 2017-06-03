#include "Common.h"

#include <ctype.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


char *str_cat_alloc(char *s1, const char *s2)
{
    s1 = (char *)realloc(s1, strlen(s1) + strlen(s2) + 1);
    s1 = strcat(s1, s2);
    return s1;
}


char *str_to_lower(char *str)
{
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }

    return str;
}


bool is_image(const char *name)
{
    bool ret = false;
    char *dup = strdup(name);
    char *extension = extension = (char *)strrchr(dup, '.');
    if (!extension) goto fin;

    ret =
        // extension == name + strlen(name) - 1            ||
        strcmp(str_to_lower(extension), ".jpg") == 0    ||
        strcmp(str_to_lower(extension), ".bmp") == 0    ||
        strcmp(str_to_lower(extension), ".png") == 0;

fin:
    free(dup);
    return ret;
}


bool is_ordinary_file(const char *name)
{
    return name[0] != '.';
}


bool is_dir(const char *dir)
{
    DIR *n = opendir(dir);
    if (n) closedir(n);

    return n != 0;
}


char *gen_random_string(int length) {
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    char *result = (char *)malloc(length + 1);

    for (int i = 0; i < length; i++) {
        result[i] = charset[rand() % (sizeof charset - 1)];
    }

    result[length] = '\0';

    return result;
}
