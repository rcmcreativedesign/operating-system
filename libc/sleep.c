#include "../kernel/kernel.h"

unsigned int sleep(unsigned int seconds) {
    unsigned int ticks = 18 * seconds;
    unsigned int eticks;
    eticks = timer_ticks + ticks;
    while (timer_ticks < eticks)
        __asm__ __volatile__ ("sti//hlt//cli");
    return 0;
};