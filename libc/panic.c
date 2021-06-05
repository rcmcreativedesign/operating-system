#include "../kernel/kernel.h"
#include "string.h"

void panic(const char* msg, const char* file, unsigned int line) {
    printf("PANIC! \"%s\" in %s line %u\n", msg, file, line);
    while(1);
}