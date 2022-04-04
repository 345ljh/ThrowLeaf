/** @file  : leaf.cpp
 *  @brief : 叶片相关函数,包括对cvector的简单封装
 */

#include "leaf.h"

const PROPERTY leaf_property[STYLE_AMOUNT] =
{
    {114, 120, 66},
    {90, 114, 58},
    {90, 120, 83},
    {96, 120, 71},
    {90, 120, 83},
    {90, 114, 59},
    {90, 114, 59},
};

ARRAY* leaf_array;

void LeafInit(void)
{
    leaf_array = array_create(1);
    leaf_array->buf[0].style = rand() % 4;
    leaf_array->buf[0].x = 600;
    leaf_array->buf[0].y = 310 - leaf_property[leaf_array->buf[0].style].height;
    leaf_array->buf[0].destroy_time = 0;
    while(leaf_array->buf[leaf_array->len - 1].x < 1200) LeafSummon();
}

void LeafSummon(void)
{
    LEAF temp;

    int isgold = 0;
    for(int i = 0; i <= leaf_array->len - 1; i++) if(leaf_array->buf[i].style == 5) isgold = 1;
    temp.style = rand() % ((player->seconds > 10 && !isgold && player->state != FLY) ? 6 : 5);  //金色叶仅在10s后刷出
    if(temp.style == 5) temp.style = (rand() % 3) ? 5 : rand() % 4;  //下调33%金色叶刷新率
    //根据游戏时间修正深绿叶刷新率
    int rate;
    if(player->seconds < 4) rate = 49;
    else if(player->seconds < 8) rate = 59;
    else if(player->seconds < 13) rate = 69;
    else if(player->seconds < 26) rate = 79;
    else if(player->seconds < 40) rate = 89;
    else rate = 99;
    if(temp.style == 4) temp.style = (rand() % 100 <= rate) ? 4 : rand() % 4;

    temp.x = leaf_array->buf[leaf_array->len - 1].x + rand() % 90 + 60;
    temp.y = rand() % 200 + 150;
    temp.destroy_time = 0;
    array_add(leaf_array, temp);
}

void LeafLoop(void)
{
    for(int i = 0; i <= leaf_array->len - 1; i++)
    {
        if(leaf_array->buf[i].style == 4 && leaf_array->buf[i].destroy_time)
        {
            leaf_array->buf[i].destroy_time++;
            if(leaf_array->buf[i].destroy_time >= 10) array_delete(leaf_array, i);
        }
    }
    while(leaf_array->buf[0].x < -100) array_delete(leaf_array, 0);
    while(leaf_array->buf[leaf_array->len - 1].x < 1200) LeafSummon();
}

//在指定位置添加叶片,用于飞行状态结束
void LeafInsert(int x, int y)
{
    //寻找适宜位置,保证leaf_array仍按x坐标排序
    int index = 0;
    for(; x <= leaf_array->buf[index].x; index++);
    LEAF temp = {x, y, 6, 0};
    array_add(leaf_array, temp);
    //将index后所有元素向后1位
    for(int i = leaf_array->len - 1; i >= index + 1; i--) leaf_array->buf[i] = leaf_array->buf[i - 1];
    leaf_array->buf[index] = temp;
}
