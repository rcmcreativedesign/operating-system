#include "types.h"

void *memset(void *dest, int val, size_t len) {
    unsigned char *ptr = dest;
    while(len-- > 0)
        *ptr++ = val;
    return dest;
}

void *memsetw(void *dest, int val, size_t len) {
    unsigned short *ptr = dest;
    while(len-- > 0)
        *ptr++ = val;
    return dest;
}