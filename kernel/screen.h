#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define WHITE_ON_RED 0x4f
#define BLACK_ON_WHITE 0xf0

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void kprint_at(char *message, int col, int row);
void kprint (char *message);
void kclear_screen();
void kreset_prompt();
int kprint_char(char character, int col, int row, char attribute_byte);
#endif