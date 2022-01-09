#ifndef LEVEL_H
#define LEVEL_H

#include "global.h"
#include "../res/level_tiles.h"
#include <gb/gb.h>
#include <rand.h>

#define levelMapWidth 16u
#define levelMapHeight 24u
#define levelMapSize 384u //(levelMapWidth * levelMapHeight)

#define levelMapDrawWidth 32u //(levelMapWidth << 1u)
#define levelMapDrawHeight 48u //(levelMapHeight << 1u)
#define levelMapDrawSize 1536u //(levelMapDrawWidth * levelMapDrawHeight)

#define levelCameraMaxX 96u //((levelMapDrawWidth - 20u) << 3u)
#define levelCameraMaxY 240u //((levelMapDrawHeight - 18u) << 3u)

#define MIN(A,B) ((A)<(B)?(A):(B))

enum Level_Tile
{
    // No collision
    Level_Tile_Earth1 = 0u,
    Level_Tile_Earth2 = 4u,
    Level_Tile_Earth3 = 8u,
    Level_Tile_Empty0 = 12u,

    Level_Tile_Free = 16u,
    Level_Tile_Enter = 20u,
    Level_Tile_Exit = 24u,
    Level_Tile_Mine = 28u,

    // Collision
    Level_Tile_Block = 32u,
    Level_Tile_Empty1 = 36u,
    Level_Tile_Empty2 = 40u,
    Level_Tile_Empty3 = 44u,

    Level_Tile_Block1 = 48u,
    Level_Tile_Block2 = 52u,
    Level_Tile_Block3 = 56u,
    Level_Tile_Block4 = 60u,

    Level_Tile_Block5 = 64u,
    Level_Tile_Block6 = 68u,
    Level_Tile_Block7 = 72u,
    Level_Tile_Block8 = 76u
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

    uint16_t entranceX;
    uint16_t entranceY;
};

extern void Level_Init(struct Level *level);
extern enum Level_Tile Level_GetMapTile(struct Level *level, uint8_t tileX, uint8_t tileY);
extern void Level_SetMapTile(struct Level *level, uint8_t tileX, uint8_t tileY, enum Level_Tile tile);
extern void Level_SetMapDrawTile(struct Level *level, uint8_t tileX, uint8_t tileY, enum Level_Tile tile);
extern uint8_t Level_MoveCameraUp(struct Level *level, uint8_t amount);
extern uint8_t Level_MoveCameraDown(struct Level *level, uint8_t amount);
extern uint8_t Level_MoveCameraLeft(struct Level *level, uint8_t amount);
extern uint8_t Level_MoveCameraRight(struct Level *level, uint8_t amount);
extern void Level_Draw(struct Level *level);

extern uint8_t Level_CheckMapCollision(struct Level *level, uint8_t tileX, uint8_t tileY);

#endif