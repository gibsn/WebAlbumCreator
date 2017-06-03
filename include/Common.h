#ifndef COMMON_H_SENTRY
#define COMMON_H_SENTRY


char *str_cat_alloc(char *s1, const char *s2);

bool is_image(const char *name);
bool is_ordinary_file(const char *name);
bool is_dir(const char *dir);

char *gen_random_string(int length);


#endif
