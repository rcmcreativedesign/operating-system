#include "screen.h"
#include "kernel.h"
#include "../libc/string.h"

int get_cursor_offset();
void set_cursor_offset(int offset);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);


void kprint_at(char *message, int col, int row) {
	int offset;
	if (col >= 0 && row >= 0)
		offset = get_offset(col, row);
	else {
		offset = get_cursor_offset();
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}

	int i = 0;
	while (message[i] != 0) {
		offset = kprint_char(message[i++], col, row, WHITE_ON_BLACK);
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
}

void kprint (char *message) {
	kprint_at(message, -1, -1);
}

void kclear_screen() {
	int screen_size = MAX_COLS * MAX_ROWS;
	int i;
	unsigned char *screen = (unsigned char*) VIDEO_ADDRESS;
	
	for (i = 0; i < screen_size; i++) {
		screen[i * 2] = ' ';
		screen[i * 2 + 1] = WHITE_ON_BLACK;
	}
	set_cursor_offset(get_offset(0, 0));
}

void kreset_prompt() {
	kclear_screen();
	set_cursor_offset(get_offset(1, MAX_ROWS));
	kprint("R:>\0");
}

int kprint_char(char character, int col, int row, char attribute_byte) {
	unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
	
	if (!attribute_byte) {
		attribute_byte = WHITE_ON_BLACK;
	}
	
	int offset;
	if (col >= 0 && row >= 0) {
		offset = get_offset(col, row);
	} else {
		offset = get_cursor_offset();
	}
	
	if (character == '\n') {
		row = get_offset_row(offset);
		offset = get_offset(0, row + 1);
	} else {
		vidmem[offset] = character;
		vidmem[offset + 1] = attribute_byte;
		offset += 2;
	}
	
	if (offset >= MAX_ROWS * MAX_COLS * 2) {
		int i;
		for (i = 1; i < MAX_ROWS; i++) 
			memcpy(get_offset(0, i) + VIDEO_ADDRESS,
						get_offset(0,  i - 1) + VIDEO_ADDRESS,
						MAX_COLS * 2);
		
		char *last_line = get_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
		for (i = 0; i < MAX_COLS * 2; i++)
			last_line[i] = 0;

			offset -= 2 * MAX_COLS;
	}
	set_cursor_offset(offset);
	return offset;
}

int handle_scrolling(int cursor_offset) {
	if (cursor_offset < MAX_ROWS * MAX_COLS * 2) {
		return cursor_offset;
	}
	
	int i;
	for (i = 1; i < MAX_ROWS; i++) {
		memcpy((char)get_offset(0, i) + VIDEO_ADDRESS,
					(char)get_offset(0, i - 1) + VIDEO_ADDRESS,
					MAX_COLS * 2);
	}
	
	char* last_line = (char)get_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
	for (i = 0; i < MAX_COLS * 2; i++) {
		last_line[i] = 0;
	}
	
	cursor_offset -= 2 * MAX_COLS;
	
	return cursor_offset;
}

int get_cursor_offset() {
	outb(REG_SCREEN_CTRL, 14);
	int offset = (int)inb(REG_SCREEN_DATA) << 8;
	outb(REG_SCREEN_CTRL, 15);
	offset += (int)inb(REG_SCREEN_DATA);
	return offset * 2;
}

void set_cursor_offset(int offset) {
	offset /= 2;
	outb(REG_SCREEN_CTRL, 14);
	outb(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	outb(REG_SCREEN_CTRL, 15);
	outb(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
	
}

int get_offset(int col, int row) {
	return (row * MAX_COLS + col) * 2;
}
int get_offset_row(int offset) {
	return offset / (2 * MAX_COLS);
}
int get_offset_col(int offset) {
	return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}
