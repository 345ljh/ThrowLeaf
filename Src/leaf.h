#ifndef LEAF_H_INCLUDED
#define LEAF_H_INCLUDED

#include "cvector.h"
#include <stdlib.h>
#include "player.h"

#define STYLE_AMOUNT 7

typedef struct
{
    int width;
    int height;
    int stem_len;
}PROPERTY;

void LeafInit(void);
void LeafSummon(void);
void LeafLoop(void);
void LeafInsert(int x, int y);

extern const PROPERTY leaf_property[STYLE_AMOUNT];
extern ARRAY* leaf_array;

#endif // LEAF_H_INCLUDED
