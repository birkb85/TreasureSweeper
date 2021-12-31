#ifndef LEVEL_H
#define LEVEL_H

#include "global.h"
#include "../res/level_tiles.h"
#include <gb/gb.h>
#include <rand.h>

#define levelMapWidth 32u
#define levelMapHeight 48u
#define levelMapSize (levelMapWidth * levelMapHeight)

#define levelCameraMaxX ((levelMapWidth - 20u) << 3u)
#define levelCameraMaxY ((levelMapHeight - 18u) << 3u)

#define MIN(A,B) ((A)<(B)?(A):(B))

struct Level
{
    // Generated map
    uint8_t map[levelMapSize];

    // Current and old position of the map in tiles    
    uint8_t mapPosX;
    uint8_t mapPosY;
    uint8_t mapPosXOld;
    uint8_t mapPosYOld;

    // Current and old positions of the camera in pixels
    uint16_t cameraX;
    uint16_t cameraY;
    uint16_t cameraXOld;
    uint16_t cameraYOld;

    // Redraw flag, indicates that camera position was changed
    uint8_t redraw;
};

extern void Level_Init(struct Level *level);
extern void Level_SetTile(struct Level *level, uint8_t x, uint8_t y, uint8_t firstTile);
extern uint8_t Level_MoveCameraUp(struct Level *level, uint8_t amount);
extern uint8_t Level_MoveCameraDown(struct Level *level, uint8_t amount);
extern uint8_t Level_MoveCameraLeft(struct Level *level, uint8_t amount);
extern uint8_t Level_MoveCameraRight(struct Level *level, uint8_t amount);
extern void Level_Draw(struct Level *level);

#endif