#include "kernel.h"
#include "../libc/types.h"
#include "../libc/string.h"

void pic_ack(bool both);
void remap_pic(void);

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();



void pic_ack(bool both) {
    if (both)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void remap_pic(void) {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20); // IRQ32-39 - tell master PIC starting IRQ is 0x20
    outb(0xA1, 0x28); // IRQ40-47 - tell slave PIC starting IRQ is 0x28

    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    printf("PIC Remapped\n");
}

void *irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void register_irq_handler(int irq, void (*handler)(struct regs *r)) {
    printf("Registered IRQ %u\n", irq);
    irq_routines[irq] = handler;
}

void unregister_irq_handler(int irq) {
    irq_routines[irq] = 0;
}

void irq_initialize() {
    register_idt_gate(32, (unsigned)irq0, 0x08, 0x8E);
    register_idt_gate(33, (unsigned)irq1, 0x08, 0x8E);
    register_idt_gate(34, (unsigned)irq2, 0x08, 0x8E);
    register_idt_gate(35, (unsigned)irq3, 0x08, 0x8E);
    register_idt_gate(36, (unsigned)irq4, 0x08, 0x8E);
    register_idt_gate(37, (unsigned)irq5, 0x08, 0x8E);
    register_idt_gate(38, (unsigned)irq6, 0x08, 0x8E);
    register_idt_gate(39, (unsigned)irq7, 0x08, 0x8E);
    register_idt_gate(40, (unsigned)irq8, 0x08, 0x8E);
    register_idt_gate(41, (unsigned)irq9, 0x08, 0x8E);
    register_idt_gate(42, (unsigned)irq10, 0x08, 0x8E);
    register_idt_gate(43, (unsigned)irq11, 0x08, 0x8E);
    register_idt_gate(44, (unsigned)irq12, 0x08, 0x8E);
    register_idt_gate(45, (unsigned)irq13, 0x08, 0x8E);
    register_idt_gate(46, (unsigned)irq14, 0x08, 0x8E);
    register_idt_gate(47, (unsigned)irq15, 0x08, 0x8E);

    remap_pic();
}

/* void irq_handler(struct regs *r) {
    putline("IRQ Handler for ");
    putdec(r->int_no);
    putch('\n');
    void (*handler)(struct regs *r);

    handler = irq_routines[r->int_no - 32];
    if (handler)
        handler(r);
        
    pic_ack(r->int_no >= 40 ? true : false);
} */

void irq_handler() {
    putline("IRQ Handler2");
    pic_ack(true);
}
