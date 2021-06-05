#include "string.h"
#include "../kernel/kernel.h"

void printf(const char* format, ...) {
    const char** arg = &format;
    int c;

    arg++;
    while ((c = *format++) != 0) {
        if (c == '\\') {
            c = *format++;
            switch (c) {
                case 'n':
                    putch('\n');
                    break;
                case 't':
                    putch('\t');
                    break;
            }
        }
        else if (c == '%') {
            c = *format++;
            switch (c) {
                case 'u':
                    putdec(*(unsigned int *)arg);
                    break;
                case 'x':
                    puthex(*(unsigned int *)arg);
                    break;
                case 's':
                    puts(*arg);
                    break;
                case 'p':
                    puthex(*(unsigned int *)arg);
                    break;
            }
            arg++;
        }
        else {
            putch(c);
        }
    }
}