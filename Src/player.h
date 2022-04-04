#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "graphics.h"
#include "gui.h"
#include "windows.h"

#include <math.h>
#include <malloc.h>

typedef enum {RUN, JUMP, FALL, GRAB, HANG, FLY} STATE_E;

typedef struct
{
    double x;        //x坐标
    double y;        //y坐标
    int direct;      //朝向,向右=0,向左=1
    double speed_y;  //竖直方向上速度,取向下为正
    STATE_E state;   //当前状态
    int support;     //空中=0,踩在叶片上=1,抓住茎=2
    int grab_timer;  //抓取状态与冷却计时
    int fly_timer;   //飞行状态计时
    int run_timer;   //游戏进行计时,每秒增加40次,当值到达40时归零并使seconds+1
    int seconds;     //游戏进行时间
}PLAYER;

void PlayerInit(void);
void PlayerLoop(void);

extern PLAYER* player;
#endif // PLAYER_H_INCLUDED
