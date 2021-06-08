#include "string.h"

void strlwr(int *str) {
    int c;
    while ((c = *str++) != 0) {
        if (c >= 'A' && c <= 'Z')
            str += 32;
    }
}