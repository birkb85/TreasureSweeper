#include "level.h"

void Level_Init(struct Level *level)
{
    DISPLAY_OFF;
    set_bkg_data(0u, 48u, levelTiles);

    // TODO BB! 2021-12-31. Test at udfylde "level->map" med tiles, og så generere "level->mapDraw" som bliver vist ud fra det.
    for (uint8_t x = 0u; x < levelMapWidth; x++)
    {
        for (uint8_t y = 0u; y < levelMapHeight; y++)
        {
            int8_t r = rand();
            if (r > 100)
                Level_SetMapTile(level, x, y, Level_Tile_Block);
            else if (r > 50)
                Level_SetMapTile(level, x, y, Level_Tile_Earth1);
            else
                Level_SetMapTile(level, x, y, Level_Tile_Earth2);
        }
    }
    Level_SetMapTile(level, 0u, 0u, Level_Tile_Block1);
    Level_SetMapTile(level, levelMapWidth - 1u, 0u, Level_Tile_Block2);
    Level_SetMapTile(level, 0u, levelMapHeight - 1u, Level_Tile_Block3);
    Level_SetMapTile(level, levelMapWidth - 1u, levelMapHeight - 1u, Level_Tile_Block4);

    for (uint8_t x = 0u; x < levelMapWidth; x++)
    {
        for (uint8_t y = 0u; y < levelMapHeight; y++)
        {
            enum Level_Tile tile = Level_GetMapTile(level, x, y);
            Level_SetMapDrawTile(level, x, y, tile);
        }
    }

    level->mapDrawPosY = 0u;
    level->mapDrawPosX = 0u;
    level->mapDrawPosYOld = 0u;
    level->mapDrawPosXOld = 255u;
    set_bkg_submap(level->mapDrawPosX, level->mapDrawPosY, 20u, 18u, level->mapDraw, levelMapDrawWidth);
    DISPLAY_ON;

    level->cameraX = 0u;
    level->cameraY = 0u;
    level->cameraXOld = level->cameraX;
    level->cameraYOld = level->cameraY;

    level->redraw = FALSE;

    SCX_REG = level->cameraX;
    SCY_REG = level->cameraY;
}

enum Level_Tile Level_GetMapTile(struct Level *level, uint8_t x, uint8_t y)
{
    return level->map[y * levelMapWidth + x];
}

void Level_SetMapTile(struct Level *level, uint8_t x, uint8_t y, enum Level_Tile tile)
{
    level->map[y * levelMapWidth + x] = tile;
}

void Level_SetMapDrawTile(struct Level *level, uint8_t x, uint8_t y, enum Level_Tile tile)
{
    uint8_t firstTile = 0u;
    switch (tile)
    {
    case Level_Tile_None:
        firstTile = 0u;
        break;

    case Level_Tile_Earth1:
        firstTile = 4u;
        break;

    case Level_Tile_Earth2:
        firstTile = 8u;
        break;

    case Level_Tile_Block:
        firstTile = 12u;
        break;

    case Level_Tile_Block1:
        firstTile = 16u;
        break;

    case Level_Tile_Block2:
        firstTile = 20u;
        break;

    case Level_Tile_Block3:
        firstTile = 24u;
        break;

    case Level_Tile_Block4:
        firstTile = 28u;
        break;

    case Level_Tile_Block5:
        firstTile = 32u;
        break;

    case Level_Tile_Block6:
        firstTile = 36u;
        break;

    case Level_Tile_Block7:
        firstTile = 40u;
        break;

    case Level_Tile_Block8:
        firstTile = 44u;
        break;

    default:
        break;
    }

    uint8_t xTemp = x << 1u;
    uint8_t yTemp = y << 1u;
    level->mapDraw[yTemp * levelMapDrawWidth + xTemp] = firstTile;
    level->mapDraw[yTemp * levelMapDrawWidth + (xTemp + 1u)] = firstTile + 1u;
    level->mapDraw[(yTemp + 1u) * levelMapDrawWidth + xTemp] = firstTile + 2u;
    level->mapDraw[(yTemp + 1u) * levelMapDrawWidth + (xTemp + 1u)] = firstTile + 3u;
}

uint8_t Level_MoveCameraUp(struct Level *level, uint8_t amount)
{
    if (level->cameraY)
    {
        level->cameraY -= amount;
        level->redraw = TRUE;
        return TRUE;
    }
    return FALSE;
}

uint8_t Level_MoveCameraDown(struct Level *level, uint8_t amount)
{
    if (level->cameraY < levelCameraMaxY)
    {
        level->cameraY += amount;
        level->redraw = TRUE;
        return TRUE;
    }
    return FALSE;
}

uint8_t Level_MoveCameraLeft(struct Level *level, uint8_t amount)
{
    if (level->cameraX)
    {
        level->cameraX -= amount;
        level->redraw = TRUE;
        return TRUE;
    }
    return FALSE;
}

uint8_t Level_MoveCameraRight(struct Level *level, uint8_t amount)
{
    if (level->cameraX < levelCameraMaxX)
    {
        level->cameraX += amount;
        level->redraw = TRUE;
        return TRUE;
    }
    return FALSE;
}

void Level_Draw(struct Level *level)
{
    if (level->redraw)
    {
        // Update hardware scroll position
        SCY_REG = level->cameraY;
        SCX_REG = level->cameraX;

        // Up or down
        level->mapDrawPosY = (uint8_t)(level->cameraY >> 3u);
        if (level->mapDrawPosY != level->mapDrawPosYOld)
        {
            if (level->cameraY < level->cameraYOld)
            {
                set_bkg_submap(level->mapDrawPosX, level->mapDrawPosY, MIN(21u, levelMapDrawWidth - level->mapDrawPosX), 1u, level->mapDraw, levelMapDrawWidth);
            }
            else
            {
                if ((levelMapDrawHeight - 18u) > level->mapDrawPosY)
                    set_bkg_submap(level->mapDrawPosX, level->mapDrawPosY + 18u, MIN(21u, levelMapDrawWidth - level->mapDrawPosX), 1u, level->mapDraw, levelMapDrawWidth);
            }
            level->mapDrawPosYOld = level->mapDrawPosY;
        }

        // Left or right
        level->mapDrawPosX = (uint8_t)(level->cameraX >> 3u);
        if (level->mapDrawPosX != level->mapDrawPosXOld)
        {
            if (level->cameraX < level->cameraXOld)
            {
                set_bkg_submap(level->mapDrawPosX, level->mapDrawPosY, 1u, MIN(19u, levelMapDrawHeight - level->mapDrawPosY), level->mapDraw, levelMapDrawWidth);
            }
            else
            {
                if ((levelMapDrawWidth - 20u) > level->mapDrawPosX)
                    set_bkg_submap(level->mapDrawPosX + 20u, level->mapDrawPosY, 1u, MIN(19u, levelMapDrawHeight - level->mapDrawPosY), level->mapDraw, levelMapDrawWidth);
            }
            level->mapDrawPosXOld = level->mapDrawPosX;
        }

        // Set old camera position to current camera position
        level->cameraXOld = level->cameraX;
        level->cameraYOld = level->cameraY;

        level->redraw = FALSE;
    }
}