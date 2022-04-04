/**
 * @file    app.cpp
 * @brief   绘图、文字等常用的功能性函数
 */

#include "app.h"

//将数值转换为字符串,字符串即返回值
///同一语句内不能多次调用,如 i = strcat(Myitoa(12), Myitoa(34) );会导致结果错误,故使用2个相同功能的函数
char* Myitoa(int num)
{
    static char p[11];
    memset(p, 0, sizeof(p));
    itoa(num, p, 10);
    return p;
}

char* MyitoaII(int num)
{
    static char p[11];
    memset(p, 0, sizeof(p));
    itoa(num, p, 10);
    return p;
}

//文字拼接,返回值为拼接后的字符串
///同一语句内多次调用Link须使用嵌套而非并列,如 Link(Link(Link(str1, str2), str3), str4)
///不能写作 Link( Link(str1, str2), Link(str3, str4) )
char* Link(char* str1, char* str2)
{
    static char p[101];
    memset(p, 0, sizeof(p));
    strcpy(p, str1);
    strcat(p, str2);

    static char pcopy[101];
    memset(pcopy, 0, sizeof(p));
    strcpy(pcopy, p);
    return pcopy;
}

//图像粘贴函数
///调用时将路径转为char*,否则报warning
///此函数调用时向mode传递的TRANSPARENT已被定义为1
void PasteImage(char* path, int x, int y, PIMAGE img, int mode, color_t color)
{
    PIMAGE temp = newimage();
    getimage(temp, path);
    switch(mode)
    {
    case 0:
    {
        putimage_alphablend(img, temp, x, y, 255);
        break;
    }
    case 1:
    {
        putimage_transparent(img, temp, x, y, color);
        break;
    }
    }
    delimage(temp);
}
