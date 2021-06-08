#include "kernel.h"
//#include "screen.h"
#include "keycodes.h"
#include "../libc/string.h"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

void keyboard_handler(struct regs *r) {
    unsigned char status;
    char keycode;

    status = inb(KEYBOARD_STATUS_PORT);
    printf("Received keyboard. Status: %x\n", status);
    if (status && 0x01) {
        keycode = inb(KEYBOARD_DATA_PORT);
        printf("Keycode received: %x\n", keycode);
/*         if (keycode == 0x1C) {
            puts("A");
            return;
        }
        if (keycode == 0x01) {
            puts("A");
            return;
        }
        if (keycode < 0 || keycode > 27)
            return;
        // if (keycode == ENTER_KEY) {
        //     kprint('\n');
        //     return;
        // }

 */
         putline(keyboard_map[keycode]);
    }
}

void keyboard_initialize() {
    register_irq_handler(1, keyboard_handler);
}