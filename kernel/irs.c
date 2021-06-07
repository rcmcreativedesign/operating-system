#include "kernel.h"
#include "../libc/types.h"

void ack(bool both);

void ack(bool both) {
    if (both)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void irq0_handler(void) {
    timer_handler();
    ack(false);
}

void irq1_handler(void) {
    keyboard_handler_main();
    ack(false);
}

void irq2_handler(void) {
    ack(false);
}

void irq3_handler(void) {
    ack(false);
}

void irq4_handler(void) {
    ack(false);
}

void irq5_handler(void) {
    ack(false);
}

void irq6_handler(void) {
    ack(false);
}

void irq7_handler(void) {
    ack(false);
}

void irq8_handler(void) {
    ack(true);
}

void irq9_handler(void) {
    ack(true);
}

void irq10_handler(void) {
    ack(true);
}

void irq11_handler(void) {
    ack(true);
}

void irq12_handler(void) {
    ack(true);
}

void irq13_handler(void) {
    ack(true);
}

void irq14_handler(void) {
    ack(true);
}

void irq15_handler(void) {
    ack(true);
}

