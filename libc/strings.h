#ifndef STRINGS_H
#define STRINGS_H

int strlen(char s[]);
int strcmp(char s1[], char s2[]);

int memcmp (const void *str1, const void *str2, size_t count);
void *memcpy(void *dest, const void *src, size_t len);
void *memmove(void *dest, const void *src, size_t len);
void *memset(void *dest, int val, size_t len);

#endif