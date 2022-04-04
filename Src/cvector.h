#ifndef CVECTOR_H_INCLUDED
#define CVECTOR_H_INCLUDED

#include <malloc.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    int x;             //x坐标
    int y;             //y坐标
    int style;         //叶片形态,影响判定
    int destroy_time;  //深色叶踩上后开始计时,0.2s(10,踩上后第一次loop结束为2)时消失
}LEAF;

typedef LEAF TYPE;  //定义ARRAY储存的数据类型,程序中所有ARRAY储存类型应相同

typedef struct
{
    int len;
    TYPE* buf;
}ARRAY;

ARRAY* array_create(int len);
void array_destroy(ARRAY* array);
void array_delete(ARRAY* array, int index);
void array_add(ARRAY* array, TYPE value);

#endif // CVECTOR_H_INCLUDED
