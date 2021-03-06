#include "level.h"

void Level_Init(struct Level *level)
{
    DISPLAY_OFF;
    set_bkg_data(0u, 80u, levelTiles);

    uint8_t xIndex = 0;
    uint8_t yIndex = 0;

    // Generate ground
    enum Level_Tile tile;
    for (xIndex = 0u; xIndex < levelMapWidth; xIndex++)
    {
        for (yIndex = 0u; yIndex < levelMapHeight; yIndex++)
        {
            tile = Level_GetRandomEarthTile();
            Level_SetMapTile(level, xIndex, yIndex, tile);
        }
    }

    // Place entrance
    uint8_t xPos = (uint8_t)rand() >> 4u; // OBS! Skal ændres hvis størrelse på kort ændres.
    uint8_t yPos = (uint8_t)rand() / 11u; // OBS! Skal ændres hvis størrelse på kort ændres.
    level->entranceX = xPos << 4;
    level->entranceY = yPos << 4;
    Level_SetMapTile(level, xPos, yPos, Level_Tile_Enter);
    uint8_t xMin = MIN(xPos - 2u, MIN(xPos - 1u, xPos));
    uint8_t xMax = MIN(xPos + 2u, levelMapWidth - 1u);
    uint8_t yMin = MIN(yPos - 2u, MIN(yPos - 1u, yPos));
    uint8_t yMax = MIN(yPos + 2u, levelMapHeight - 1u);
    for (xIndex = xMin; xIndex <= xMax; xIndex++)
    {
        for (yIndex = yMin; yIndex <= yMax; yIndex++)
        {
            if (xIndex != xPos || yIndex != yPos)
            {
                Level_SetMapTile(level, xIndex, yIndex, Level_Tile_Free);
            }
        }
    }

    // Place exit
    uint8_t objToPlace = 1u;
    while (objToPlace)
    {
        xIndex = (uint8_t)rand() >> 4u; // OBS! Skal ændres hvis størrelse på kort ændres.
        yIndex = (uint8_t)rand() / 11u; // OBS! Skal ændres hvis størrelse på kort ændres.
        tile = Level_GetMapTile(level, xIndex, yIndex);
        if (tile != Level_Tile_Enter &&
            tile != Level_Tile_Free)
        {
            Level_SetMapTile(level, xIndex, yIndex, Level_Tile_Exit);
            objToPlace--;
        }
    }

    // Place mines
    objToPlace = 40u;
    while (objToPlace)
    {
        xIndex = (uint8_t)rand() >> 4u; // OBS! Skal ændres hvis størrelse på kort ændres.
        yIndex = (uint8_t)rand() / 11u; // OBS! Skal ændres hvis størrelse på kort ændres.
        tile = Level_GetMapTile(level, xIndex, yIndex);
        if (tile != Level_Tile_Enter &&
            tile != Level_Tile_Free &&
            tile != Level_Tile_Exit)
        {
            Level_SetMapTile(level, xIndex, yIndex, Level_Tile_Mine);
            objToPlace--;
        }
    }

    // Place numbered blocks
    uint8_t numberOfObj;
    for (xPos = 0u; xPos < levelMapWidth; xPos++)
    {
        for (yPos = 0u; yPos < levelMapHeight; yPos++)
        {
            tile = Level_GetMapTile(level, xPos, yPos);
            if (tile == Level_Tile_Earth1 ||
                tile == Level_Tile_Earth2 ||
                tile == Level_Tile_Earth3 ||
                tile == Level_Tile_Free)
            {
                numberOfObj = 0;

                xMin = MIN(xPos - 1u, xPos);
                xMax = MIN(xPos + 1u, levelMapWidth - 1u);
                yMin = MIN(yPos - 1u, yPos);
                yMax = MIN(yPos + 1u, levelMapHeight - 1u);
                for (xIndex = xMin; xIndex <= xMax; xIndex++)
                {
                    for (yIndex = yMin; yIndex <= yMax; yIndex++)
                    {
                        if (xIndex != xPos || yIndex != yPos)
                        {
                            tile = Level_GetMapTile(level, xIndex, yIndex);
                            if (tile == Level_Tile_Mine || tile == Level_Tile_Exit)
                            {
                                numberOfObj++;
                            }
                        }
                    }
                }

                switch (numberOfObj)
                {
                case 1:
                    Level_SetMapTile(level, xPos, yPos, Level_Tile_Block1);
                    break;

                case 2:
                    Level_SetMapTile(level, xPos, yPos, Level_Tile_Block2);
                    break;

                case 3:
                    Level_SetMapTile(level, xPos, yPos, Level_Tile_Block3);
                    break;

                case 4:
                    Level_SetMapTile(level, xPos, yPos, Level_Tile_Block4);
                    break;

                case 5:
                    Level_SetMapTile(level, xPos, yPos, Level_Tile_Block5);
                    break;

                case 6:
                    Level_SetMapTile(level, xPos, yPos, Level_Tile_Block6);
                    break;

                case 7:
                    Level_SetMapTile(level, xPos, yPos, Level_Tile_Block7);
                    break;

                case 8:
                    Level_SetMapTile(level, xPos, yPos, Level_Tile_Block8);
                    break;

                default:
                    break;
                }
            }
        }
    }

    for (xIndex = 0u; xIndex < levelMapWidth; xIndex++)
    {
        for (yIndex = 0u; yIndex < levelMapHeight; yIndex++)
        {
            enum Level_Tile tile = Level_GetMapTile(level, xIndex, yIndex);
            Level_SetMapDrawTile(level, xIndex, yIndex, tile);
        }
    }

    level->cameraX = level->entranceX + 8u;
    if (level->cameraX > 10u << 3u)
        level->cameraX -= 10u << 3u;
    else
        level->cameraX = 0u;
    if (level->cameraX > levelCameraMaxX)
        level->cameraX = levelCameraMaxX;
    level->cameraXOld = level->cameraX;

    level->cameraY = level->entranceY + 8u;
    if (level->cameraY > 9u << 3u)
        level->cameraY -= 9u << 3u;
    else
        level->cameraY = 0u;
    if (level->cameraY > levelCameraMaxY)
        level->cameraY = levelCameraMaxY;
    level->cameraYOld = level->cameraY;

    level->mapDrawPosX = level->cameraX >> 3u;
    level->mapDrawPosY = level->cameraY >> 3u;
    level->mapDrawPosXOld = 255u;
    level->mapDrawPosYOld = 255u;
    set_bkg_submap(level->mapDrawPosX, level->mapDrawPosY, 20u, 18u, level->mapDraw, levelMapDrawWidth);
    DISPLAY_ON;

    level->redraw = FALSE;

    SCX_REG = level->cameraX;
    SCY_REG = level->cameraY;
}

enum Level_Tile Level_GetRandomEarthTile()
{
    if ((uint8_t)rand() > (228))
    {
        if ((uint8_t)rand() > 128)
            return Level_Tile_Earth3;
        else
            return Level_Tile_Earth2;
    }
    else
        return Level_Tile_Earth1;
}

enum Level_Tile Level_GetMapTile(struct Level *level, uint8_t tileX, uint8_t tileY)
{
    return level->map[tileY * levelMapWidth + tileX];
}

void Level_SetMapTile(struct Level *level, uint8_t tileX, uint8_t tileY, enum Level_Tile tile)
{
    level->map[tileY * levelMapWidth + tileX] = tile;
}

void Level_SetMapDrawTile(struct Level *level, uint8_t tileX, uint8_t tileY, enum Level_Tile tile)
{
    uint8_t xTemp = tileX << 1u;
    uint8_t yTemp = tileY << 1u;
    level->mapDraw[yTemp * levelMapDrawWidth + xTemp] = tile;
    level->mapDraw[yTemp * levelMapDrawWidth + (xTemp + 1u)] = tile + 1u;
    level->mapDraw[(yTemp + 1u) * levelMapDrawWidth + xTemp] = tile + 2u;
    level->mapDraw[(yTemp + 1u) * levelMapDrawWidth + (xTemp + 1u)] = tile + 3u;
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

uint8_t Level_CheckMapCollision(struct Level *level, uint8_t tileX, uint8_t tileY)
{
    if (tileX < levelMapWidth && tileY < levelMapHeight)
    {
        enum Level_Tile tile = Level_GetMapTile(level, tileX, tileY);
        if (tile < Level_Tile_Block)
            return FALSE;
    }

    return TRUE;
}

void Level_DestroyMapTile(struct Level *level, uint8_t tileX, uint8_t tileY)
{
    if (tileX < levelMapWidth && tileY < levelMapHeight)
    {
        enum Level_Tile tile = Level_GetMapTile(level, tileX, tileY);
        if (tile >= Level_Tile_Block)
        {
            tile = Level_GetRandomEarthTile();
            Level_SetMapTile(level, tileX, tileY, tile);
            Level_SetMapDrawTile(level, tileX, tileY, tile);
            set_bkg_submap(tileX << 1u, tileY << 1u, 2u, 2u, level->mapDraw, levelMapDrawWidth);
        }
    }
}