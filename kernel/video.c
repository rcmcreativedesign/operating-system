#include "kernel.h"
#include "../libc/string.h"

unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

void scroll(void) {
    unsigned blank, temp;

    blank = 0x20 | (attrib << 8);

    if (csr_y >= 25) {
        temp = csr_y - 25 + 1;
        memcpy(textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);
        memsetw(textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}

void move_csr(void) {
    unsigned temp;

    temp = csr_y * 80 + csr_x;
    outb(0x3D4, 14);
    outb(0x3D5, temp >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, temp);
}

void cls() {
    unsigned blank;
    int i;

    blank = 0x20 | (attrib << 8);

    for(i = 0; i < 25; i++)
        memsetw(textmemptr + i * 80, blank, 80);
    
    csr_x = 0;
    csr_y = 0;
    move_csr();
}

void putch(unsigned char c) {
    unsigned short *where;
    unsigned att = attrib << 8;

    if(c == 0x08) {
        if (csr_x !=0) 
            csr_x--;
    }
    else if (c == 0x09) {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    else if (c == '\r') {
        csr_x = 0;
    }
    else if (c == '\n') {
        csr_x = 0;
        csr_y++;
    }
    else if (c >= ' ') {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;
        csr_x++;
    }

    if (csr_x >= 80) {
        csr_x = 0;
        csr_y++;
    }

    scroll();
    move_csr();
}

void puts(unsigned char *text) {
    int i;

    for (i = 0; i < strlen(text); i++)
        putch(text[i]);
}

void putline(unsigned char *text) {
    puts(text);
    putch('\n');
}

void puthex(unsigned int hex) {
    char hexarr[9] = {0};
    int index = 7;

    for (index = 7; index >= 0; index--) {
        unsigned int tmp = hex % 16;
        switch(tmp) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                hexarr[index] = tmp + '0';
                break;
            case 10:
                hexarr[index] = 'A';
                break;
            case 11:
                hexarr[index] = 'B';
                break;
            case 12:
                hexarr[index] = 'C';
                break;
            case 13:
                hexarr[index] = 'D';
                break;
            case 14:
                hexarr[index] = 'E';
                break;
            case 15:
                hexarr[index] = 'F';
                break;
        }
        if (hex < 16) {
            break;
        }
        hex = hex / 16;
    }
    index = index == -1 ? index + 1 : index;
    puts("0x");
    puts(&hexarr[index]);
}

void putdec(unsigned int dec) {
    char decarr[33] = {0};
    int index = 31;

    for (index = 31; index >= 0; index--) {
        unsigned int tmp = dec % 10;

        decarr[index] = tmp + '0';
        if (dec < 10)
            break;
        dec /= 10;
    }
    index = index == -1 ? index + 1 : index;
    puts(&decarr[index]);
}

void settextcolor(unsigned char forecolor, unsigned char backcolor) {
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

void init_video(void) {
    textmemptr = (unsigned short *)0xB8000;
    settextcolor(0xF, 0x0);
    cls();
    if (DEBUG)
        putline("Video initialized");
}