#ifndef LEVEL_H
#define LEVEL_H

#include "global.h"
#include "../res/hero_spr.h"
#include <gb/gb.h>

#define levelMapWidth 32u
#define levelMapHeight 32u

#define levelCameraMaxX ((levelMapWidth - 20u) * 8u)
#define levelCameraMaxY ((levelMapHeight - 18u) * 8u)

#define MIN(A,B) ((A)<(B)?(A):(B))

struct Level
{
    uint8_t map[1024u];
    uint8_t mapPosX;
    uint8_t mapPosY;
    uint8_t mapPosXOld;
    uint8_t mapPosYOld;
    uint16_t cameraX;
    uint16_t cameraY;
    uint16_t cameraXOld;
    uint16_t cameraYOld;
    uint8_t redraw;
};

extern void Level_Init(struct Level *level);
extern void Level_MoveCameraUp(struct Level *level, uint8_t amount);
extern void Level_MoveCameraDown(struct Level *level, uint8_t amount);
extern void Level_MoveCameraLeft(struct Level *level, uint8_t amount);
extern void Level_MoveCameraRight(struct Level *level, uint8_t amount);
extern void Level_Draw(struct Level *level);

#endif