#ifndef LEVEL_H
#define LEVEL_H

#include "global.h"
#include "../res/level_tiles.h"
#include <gb/gb.h>
#include <rand.h>

#define levelMapWidth 16u
#define levelMapHeight 24u
#define levelMapSize (levelMapWidth * levelMapHeight)

#define levelMapDrawWidth (levelMapWidth << 1u)
#define levelMapDrawHeight (levelMapHeight << 1u)
#define levelMapDrawSize (levelMapDrawWidth * levelMapDrawHeight)

#define levelCameraMaxX ((levelMapDrawWidth - 20u) << 3u)
#define levelCameraMaxY ((levelMapDrawHeight - 18u) << 3u)

#define MIN(A,B) ((A)<(B)?(A):(B))

enum Level_Tile
{
    // No collision
    Level_Tile_None,
    Level_Tile_Earth1,
    Level_Tile_Earth2,

    // Collision
    Level_Tile_Block,
    Level_Tile_Block1,
    Level_Tile_Block2,
    Level_Tile_Block3,
    Level_Tile_Block4,
    Level_Tile_Block5,
    Level_Tile_Block6,
    Level_Tile_Block7,
    Level_Tile_Block8
};

struct Level
{
    // Generated map
    uint8_t map[levelMapSize];

    // Map to draw on screen
    uint8_t mapDraw[levelMapDrawSize];

    // Current and old position of the map in tiles    
    uint8_t mapDrawPosX;
    uint8_t mapDrawPosY;
    uint8_t mapDrawPosXOld;
    uint8_t mapDrawPosYOld;

    // Current and old positions of the camera in pixels
    uint16_t cameraX;
    uint16_t cameraY;
    uint16_t cameraXOld;
    uint16_t cameraYOld;

    // Redraw flag, indicates that camera position was changed
    uint8_t redraw;
};

extern void Level_Init(struct Level *level);
extern enum Level_Tile Level_GetMapTile(struct Level *level, uint8_t x, uint8_t y);
extern void Level_SetMapTile(struct Level *level, uint8_t x, uint8_t y, enum Level_Tile tile);
extern void Level_SetMapDrawTile(struct Level *level, uint8_t x, uint8_t y, enum Level_Tile tile);
extern uint8_t Level_MoveCameraUp(struct Level *level, uint8_t amount);
extern uint8_t Level_MoveCameraDown(struct Level *level, uint8_t amount);
extern uint8_t Level_MoveCameraLeft(struct Level *level, uint8_t amount);
extern uint8_t Level_MoveCameraRight(struct Level *level, uint8_t amount);
extern void Level_Draw(struct Level *level);

#endif