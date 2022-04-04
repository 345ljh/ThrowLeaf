#include "cvector.h"

//创建一个动态数组,所有元素为0
ARRAY* array_create(int len)
{
    ARRAY* pointer = NULL;
    pointer = (ARRAY*)malloc(sizeof(ARRAY));
    pointer->len = len;
    pointer->buf = (TYPE*)calloc(len, sizeof(TYPE));
    memset(pointer->buf, 0, len * sizeof(TYPE));
    return pointer;
}

//释放动态数组
void array_destroy(ARRAY* array)
{
    free(array);
}

//删除特定下标元素,此后的元素填补空缺(当且仅当数组长度大于1)
void array_delete(ARRAY* array, int index)
{
    if(array->len > 1 && index < array->len)
    {
        for(int i = index; i <= array->len - 2; i++)  array->buf[i] = array->buf[i + 1];
        TYPE* temp = array->buf;
        array->buf = (TYPE*)realloc(temp, --array->len * sizeof(TYPE));
    }
}

//在末尾添加一个元素
void array_add(ARRAY* array, TYPE value)
{
    TYPE* temp = array->buf;
    array->buf = (TYPE*)realloc(temp, ++array->len * sizeof(TYPE));
    array->buf[array->len - 1] = value;
}
