#include "kernel.h"
#include "screen.h"
#include "keycodes.h"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

void keyboard_handler_main(void) {
    unsigned char status;
    char keycode;

    status = inb(KEYBOARD_STATUS_PORT);
    if (status && 0x01) {
        keycode = inb(KEYBOARD_DATA_PORT);
        if (keycode == 0x1C) {
            kprint("A");
            return;
        }
        if (keycode == 0x01) {
            kprint("A");
            return;
        }
        if (keycode < 0 || keycode > 27)
            return;
        // if (keycode == ENTER_KEY) {
        //     kprint('\n');
        //     return;
        // }

        kprint(keyboard_map[keycode]);
    }
}