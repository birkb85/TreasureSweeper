#ifndef HERO_H
#define HERO_H

#include "global.h"
#include "../res/hero_spr.h"
#include <gb/gb.h>

typedef struct Hero
{
    uint8_t sprIds[4u];
    uint8_t localX;
    uint8_t localY;
    uint8_t w;
    uint8_t h;
    int8_t dirY; // -1 = up, 1 = down
    int8_t dirX; // -1 = left, 1 = right
    uint8_t redraw;
};

extern void Hero_Init(struct Hero *hero, uint8_t sprStartIndex);
extern void Hero_MoveX(struct Hero *hero, int8_t x);
extern void Hero_MoveY(struct Hero *hero, int8_t y);
extern void Hero_Draw(struct Hero *hero);

#endif