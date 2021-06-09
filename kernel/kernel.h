#ifndef KERNEL_H
#define KERNEL_H

/* PORTS */
unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char data);
unsigned short inw(unsigned short port);
void outw(unsigned short port, unsigned short data);

/* SCREEN */
extern void cls();
extern void putch(unsigned char c);
extern void putch_at(unsigned char c, unsigned char loc);
extern void puthex(unsigned int hex);
extern void putdec(unsigned int dec);
extern void puts(unsigned char *str);
extern void puts_at(unsigned char *text, unsigned char loc);
extern void putline(unsigned char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();
extern void *convert_to_dec(unsigned int dec, char *arrdec);

/* KEYBOARD */
void keyboard_handler_main(void);

/* TIMER */
void timer_handler();
extern int timer_ticks;

/* KERNEL */
void panic(const char* msg, const char* file, unsigned int line);

#define DEBUG 1

#endif