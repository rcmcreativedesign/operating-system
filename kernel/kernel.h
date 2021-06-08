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
extern void putdec(unsigned int dec);
extern void puthex(unsigned int hex);
extern void puts(unsigned char *str);
extern void putline(unsigned char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();

/* KEYBOARD */
void keyboard_initialize();

/* TIMER */
void timer_handler();
extern int timer_ticks;

/* KERNEL */
void panic(const char* msg, const char* file, unsigned int line);

#define DEBUG 1

struct regs {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

/* ISR */
void idt_initialize();
void register_idt_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void isr_initialize();

/* IRQ */
void irq_initialize();
void register_irq_handler(int irq, void (*handler)(struct regs *r));
void unregister_irq_handler(int irq);

#endif