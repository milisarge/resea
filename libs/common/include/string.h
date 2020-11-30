#ifndef __STRING_H__
#define __STRING_H__

#include <types.h>

size_t strlen(const char *s);
char *resea_strncpy(char *dst, const char *src, size_t num);
int resea_strcmp(const char *s1, const char *s2);
int resea_strncmp(const char *s1, const char *s2, size_t len);
char *resea_strstr(const char *haystack, const char *needle);
char *resea_strchr(const char *s, int c);
int resea_atoi(const char *s);
int resea_memcmp(const void *p1, const void *p2, size_t len);
void resea_bzero(void *dst, size_t len);
void memset(void *dst, int ch, size_t len);
void memcpy(void *dst, const void *src, size_t len);
void memmove(void *dst, const void *src, size_t len);

#endif
