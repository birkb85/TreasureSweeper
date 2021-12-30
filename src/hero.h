#ifndef HERO_H
#define HERO_H

#include "global.h"
#include "../res/hero_spr.h"
#include <gb/gb.h>

enum Hero_Dir
{
    Hero_Dir_Up,
    Hero_Dir_Down,
    Hero_Dir_Left,
    Hero_Dir_Right
};

typedef struct Hero
{
    uint8_t sprIds[6u];
    uint8_t localX;
    uint8_t localY;
    uint8_t w;
    uint8_t h;
    uint8_t localMaxX;
    uint8_t localMaxY;
    enum Hero_Dir dir;
    uint8_t redraw;
};

extern void Hero_Init(struct Hero *hero, uint8_t sprStartIndex);
extern void Hero_SetDir(struct Hero *hero, enum Hero_Dir dir);
extern void Hero_MoveUp(struct Hero *hero, uint8_t amount);
extern void Hero_MoveDown(struct Hero *hero, uint8_t amount);
extern void Hero_MoveLeft(struct Hero *hero, uint8_t amount);
extern void Hero_MoveRight(struct Hero *hero, uint8_t amount);
extern void Hero_Draw(struct Hero *hero);

#endif