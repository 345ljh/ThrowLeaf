#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "graphics.h"
#include "app.h"
#include "leaf.h"
#include "player.h"
#include <math.h>

typedef struct
{
    PIMAGE background;  //背景
    PIMAGE animation;   //动画效果
    PIMAGE leaf;        //叶片
    PIMAGE player;      //人物
    PIMAGE text;        //文字
    PIMAGE msg;         //游戏开始前与结束的信息
}GUI;

void GuiInit(void);
void GuiDraw(void);
void GuiOver(void);

extern GUI gui;
extern MUSIC music_over;
extern MUSIC music_bgm;
#endif // GUI_H_INCLUDED
