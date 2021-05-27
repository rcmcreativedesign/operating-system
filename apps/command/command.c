//#include "kernel.h"
#include "stdio.h"

#define SHUTDOWN 4232446817
#define RESTART 1059716234

const unsigned long hash(const char *str);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Invalid command.");
    }

    switch (hash(argv[1])) {
    case SHUTDOWN:
        printf("Shutting down...");
        break;
    case RESTART:
        printf("Restarting...");
        break;
    default:
        printf("Unknown Command");
        break;
    }   
}

const unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) 
        hash = ((hash << 5) + hash) + c;
    return hash;
}