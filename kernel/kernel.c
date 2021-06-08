//#include "screen.h"
#include "idt.h"
#include "timer.h"
#include "kernel.h"
#include "../libc/sleep.h"
#include "../libc/types.h"

void main() {

	init_video();
/*
	kprint_char('H', 0, 5, WHITE_ON_BLACK);
	kprint_char('E', 1, 5, WHITE_ON_BLACK);
	kprint_char('L', 2, 5, WHITE_ON_BLACK);
	kprint_char('L', 3, 5, WHITE_ON_BLACK);
	kprint_char('O', 4, 5, WHITE_ON_BLACK);
	
	kprint_char('M', 18, 5, WHITE_ON_BLACK);
	kprint_char('Y', 19, 5, WHITE_ON_BLACK);
	kprint_char('L', 21, 5, WHITE_ON_BLACK);
	kprint_char('O', 22, 5, WHITE_ON_BLACK);
	kprint_char('V', 23, 5, WHITE_ON_BLACK);
	kprint_char('E', 24, 5, WHITE_ON_BLACK);
	
	kprint_char('X', 11, 3, WHITE_ON_RED);
	kprint_char('X', 10, 2, WHITE_ON_RED);
	kprint_char('X', 9, 2, WHITE_ON_RED);
	kprint_char('X', 8, 3, WHITE_ON_RED);
	kprint_char('X', 7, 4, WHITE_ON_RED);
	kprint_char('X', 7, 5, WHITE_ON_RED);
	kprint_char('X', 7, 6, WHITE_ON_RED);
	kprint_char('X', 8, 7, WHITE_ON_RED);
	kprint_char('X', 9, 8, WHITE_ON_RED);
	kprint_char('X', 10, 9, WHITE_ON_RED);
	kprint_char('X', 11, 10, WHITE_ON_RED);
	kprint_char('X', 12, 9, WHITE_ON_RED);
	kprint_char('X', 13, 8, WHITE_ON_RED);
	kprint_char('X', 14, 7, WHITE_ON_RED);
	kprint_char('X', 15, 6, WHITE_ON_RED);
	kprint_char('X', 15, 5, WHITE_ON_RED);
	kprint_char('X', 15, 4, WHITE_ON_RED);
	kprint_char('X', 14, 3, WHITE_ON_RED);
	kprint_char('X', 13, 2, WHITE_ON_RED);
	kprint_char('X', 12, 2, WHITE_ON_RED);
*/
	puts("256 in hex = ");
	puthex(256);
	putch('\n');
	puts("256 in dec = ");
	putdec(256);
	putch('\n');

	idt_init();
	timer_init();

	sleep(1);
	puts("\n\nR:>");



}