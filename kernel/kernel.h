#ifndef KERNEL_H
#define KERNEL_H

/* PORTS */
unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char data);
unsigned short inw(unsigned short port);
void outw(unsigned short port, unsigned short data);

/* SCREEN */


/* KEYBOARD */
void keyboard_handler_main(void);

/* TIMER */
void timer_handler();
extern int timer_ticks;

#endif