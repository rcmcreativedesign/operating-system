#include "kernel.h"
#include "../libc/string.h"

void timer_phase(int hz);
int timer_ticks = 0;

void timer_phase(int hz) {
    int divisor = 1193180 / hz;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xff);
    outb(0x40, divisor >> 8);
}

void timer_handler(struct regs *r) {
    timer_ticks++;
    printf("Timer Ticks: %u\n", timer_ticks);
/*     if (DEBUG && timer_ticks % (18 * 3) == 0) {
        puts("Tick: ");
        puthex(timer_ticks);
        putch('\n');
    } */
}

void timer_init() {
    register_irq_handler(0, timer_handler);
/* 
    if (DEBUG)
        putline("Timer Initialized"); */
}