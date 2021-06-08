#include "kernel.h"
#include "../libc/string.h"

#define IDT_SIZE 256

extern void idt_load();

struct IDT_entry {
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

struct IDT_ptr {
    unsigned short limit;
    unsigned int base;
};

struct IDT_entry IDT[IDT_SIZE];
struct IDT_ptr idtp;

void register_idt_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    IDT[num].offset_lowerbits = base & 0xffff;
    IDT[num].selector = sel;
    IDT[num].zero = 0;
    IDT[num].type_attr = flags;
    IDT[num].offset_higherbits = (base >> 16) & 0xFFFF;
}

void unregister_idt_gate(unsigned char num) {
    //IDT[num] = 0;
}

void idt_initialize() {
    idtp.limit = (sizeof(struct IDT_entry) * 256) - 1;
    idtp.base = &IDT;

    memset(&IDT, 0, sizeof(struct IDT_entry) * 256);

    idt_load();
}


