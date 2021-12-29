#include "level.h"

void Level_Init(struct Level *level)
{
    // TODO BB 2021-12-29. Init map correctly!
    // for (uint8_t x = 0u; x < levelMapWidth; x++)
    //     for (uint8_t y = 0u; y < levelMapHeight; y++)
    //         level->map[] = 0;
    //set_bkg_tile_xy(x, y, 0xFFu);
    for (uint16_t i = 0u; i < sizeof(level->map); i++)
    {
        level->map[i] = 0;
    }
    level->map[0u] = 0xFFu;
    level->map[31u] = 0xFFu;
    level->map[992u] = 0xFFu;
    level->map[1023u] = 0xFFu;

    DISPLAY_OFF;
    set_bkg_data(0u, 4u, heroSpr);

    level->mapPosY = level->mapPosX = 0u;
    level->mapPosYOld = level->mapPosXOld = 255u;
    set_bkg_submap(level->mapPosX, level->mapPosY, 20, 18, level->map, levelMapWidth);
    DISPLAY_ON;

    level->cameraX = level->cameraY = 0;
    level->cameraXOld = level->cameraX;
    level->cameraYOld = level->cameraY;

    level->redraw = FALSE;

    SCX_REG = level->cameraX;
    SCY_REG = level->cameraY;
}

void Level_MoveCameraUp(struct Level *level, uint8_t amount)
{
    if (level->cameraY)
    {
        level->cameraY -= amount;
        level->redraw = TRUE;
    }
}

void Level_MoveCameraDown(struct Level *level, uint8_t amount)
{
    if (level->cameraY < levelCameraMaxY)
    {
        level->cameraY += amount;
        level->redraw = TRUE;
    }
}

void Level_MoveCameraLeft(struct Level *level, uint8_t amount)
{
    if (level->cameraX)
    {
        level->cameraX -= amount;
        level->redraw = TRUE;
    }
}

void Level_MoveCameraRight(struct Level *level, uint8_t amount)
{
    if (level->cameraX < levelCameraMaxX)
    {
        level->cameraX += amount;
        level->redraw = TRUE;
    }
}

void Level_Draw(struct Level *level)
{
    if (level->redraw)
    {
        // update hardware scroll position
        SCY_REG = level->cameraY;
        SCX_REG = level->cameraX;

        // up or down
        level->mapPosY = (uint8_t)(level->cameraY >> 3u);
        if (level->mapPosY != level->mapPosYOld)
        {
            if (level->cameraY < level->cameraYOld)
            {
                set_bkg_submap(level->mapPosX, level->mapPosY, MIN(21u, levelMapWidth - level->mapPosX), 1, level->map, levelMapWidth);
            }
            else
            {
                if ((levelMapHeight - 18u) > level->mapPosY)
                    set_bkg_submap(level->mapPosX, level->mapPosY + 18u, MIN(21u, levelMapWidth - level->mapPosX), 1, level->map, levelMapWidth);
            }
            level->mapPosYOld = level->mapPosY;
        }

        // left or right
        level->mapPosX = (uint8_t)(level->cameraX >> 3u);
        if (level->mapPosX != level->mapPosXOld)
        {
            if (level->cameraX < level->cameraXOld)
            {
                set_bkg_submap(level->mapPosX, level->mapPosY, 1, MIN(19u, levelMapHeight - level->mapPosY), level->map, levelMapWidth);
            }
            else
            {
                if ((levelMapWidth - 20u) > level->mapPosX)
                    set_bkg_submap(level->mapPosX + 20u, level->mapPosY, 1, MIN(19u, levelMapHeight - level->mapPosY), level->map, levelMapWidth);
            }
            level->mapPosXOld = level->mapPosX;
        }

        // set old camera position to current camera position
        level->cameraXOld = level->cameraX;
        level->cameraYOld = level->cameraY;

        level->redraw = FALSE;
    }
}