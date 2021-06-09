#include "kernel.h"

int number_of_digits(int num);
void timer_phase(int hz);
int timer_ticks;

void timer_phase(int hz) {
    int divisor = 1193180 / hz;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xff);
    outb(0x40, divisor >> 8);
}

void timer_handler() {
    timer_ticks++;
/*     if (DEBUG && timer_ticks % (18 * 3) == 0) {
        puts("Tick: ");
        puthex(timer_ticks);
        putch('\n');
    } */

    int loc = 80;
    char decarr[33] = {0};
    char decarr2[33] = {0};

    puts_at(convert_to_dec(timer_ticks, decarr), loc - number_of_digits(timer_ticks));
    if (timer_ticks % 18 == 0)
        puts_at(convert_to_dec(timer_ticks / 18, decarr2), loc * 2 - number_of_digits(timer_ticks / 18));
}

void timer_init() {
    timer_ticks = 0;
    if (DEBUG)
        putline("Timer Initialized");
}

int number_of_digits(int num) {
    int count = 0;
    do
    {
        count++;
        num /= 10;
    } while (num != 0);
    return count;
}