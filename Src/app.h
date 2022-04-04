#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

char* Myitoa(int num);
char* MyitoaII(int num);
char* Link(char* str1, char* str2);

void PasteImage(char* path, int x, int y, PIMAGE img = NULL, int mode = 0, color_t color = BLACK);

#endif // APP_H_INCLUDED
