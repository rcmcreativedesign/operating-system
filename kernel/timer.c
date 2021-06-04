#include "kernel.h"

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
}

void timer_init() {
    timer_ticks = 0;
}