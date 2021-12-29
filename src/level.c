#include "level.h"

void Level_Init(struct Level *level)
{
    DISPLAY_OFF;
    set_bkg_data(0u, 16u, levelTiles);

    // TODO BB 2021-12-29. Init map correctly!
    for (uint8_t x = 0u; x < levelMapWidth; x += 2u)
    {
        for (uint8_t y = 0u; y < levelMapHeight; y += 2u)
        {
            if (rand() > 50)
                Level_SetTile(level, x, y, 4u);
            else
                Level_SetTile(level, x, y, 8u);

            // if (x % 2 == 0)
            // {
            //     if (y % 2 == 0)
            //         level->map[y * levelMapWidth + x] = 0;
            //     else
            //         level->map[y * levelMapWidth + x] = 2;
            // }
            // else
            // {
            //     if (y % 2 == 0)
            //         level->map[y * levelMapWidth + x] = 1;
            //     else
            //         level->map[y * levelMapWidth + x] = 3;
            // }
        }
    }
    Level_SetTile(level, 0u, 0u, 12u);
    Level_SetTile(level, levelMapWidth - 2u, 0u, 12u);
    Level_SetTile(level, 0u, levelMapHeight - 2u, 12u);
    Level_SetTile(level, levelMapWidth - 2u, levelMapHeight - 2u, 12u);

    // level->map[0u] = 0xFFu;
    // level->map[1u] = 0xFFu;
    // level->map[30u] = 0xFFu;
    // level->map[31u] = 0xFFu;
    // level->map[32u] = 0xFFu;
    // level->map[33u] = 0xFFu;
    // level->map[62u] = 0xFFu;
    // level->map[63u] = 0xFFu;
    // level->map[960u] = 0xFFu;
    // level->map[961u] = 0xFFu;
    // level->map[990u] = 0xFFu;
    // level->map[991u] = 0xFFu;
    // level->map[992u] = 0xFFu;
    // level->map[993u] = 0xFFu;
    // level->map[1022u] = 0xFFu;
    // level->map[1023u] = 0xFFu;

    level->mapPosY = level->mapPosX = 0u;
    level->mapPosYOld = level->mapPosXOld = 255u;
    set_bkg_submap(level->mapPosX, level->mapPosY, 20u, 18u, level->map, levelMapWidth);
    DISPLAY_ON;

    level->cameraX = level->cameraY = 0u;
    level->cameraXOld = level->cameraX;
    level->cameraYOld = level->cameraY;

    level->redraw = FALSE;

    SCX_REG = level->cameraX;
    SCY_REG = level->cameraY;
}

void Level_SetTile(struct Level *level, uint8_t x, uint8_t y, uint8_t firstTile)
{
    level->map[y * levelMapWidth + x] = firstTile;
    level->map[y * levelMapWidth + (x + 1u)] = firstTile + 1u;
    level->map[(y + 1u) * levelMapWidth + x] = firstTile + 2u;
    level->map[(y + 1u) * levelMapWidth + (x + 1u)] = firstTile + 3u;
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
        level->mapPosY = (uint8_t)(level->cameraY >> 3u);
        if (level->mapPosY != level->mapPosYOld)
        {
            if (level->cameraY < level->cameraYOld)
            {
                set_bkg_submap(level->mapPosX, level->mapPosY, MIN(21u, levelMapWidth - level->mapPosX), 1u, level->map, levelMapWidth);
            }
            else
            {
                if ((levelMapHeight - 18u) > level->mapPosY)
                    set_bkg_submap(level->mapPosX, level->mapPosY + 18u, MIN(21u, levelMapWidth - level->mapPosX), 1u, level->map, levelMapWidth);
            }
            level->mapPosYOld = level->mapPosY;
        }

        // Left or right
        level->mapPosX = (uint8_t)(level->cameraX >> 3u);
        if (level->mapPosX != level->mapPosXOld)
        {
            if (level->cameraX < level->cameraXOld)
            {
                set_bkg_submap(level->mapPosX, level->mapPosY, 1u, MIN(19u, levelMapHeight - level->mapPosY), level->map, levelMapWidth);
            }
            else
            {
                if ((levelMapWidth - 20u) > level->mapPosX)
                    set_bkg_submap(level->mapPosX + 20u, level->mapPosY, 1u, MIN(19u, levelMapHeight - level->mapPosY), level->map, levelMapWidth);
            }
            level->mapPosXOld = level->mapPosX;
        }

        // Set old camera position to current camera position
        level->cameraXOld = level->cameraX;
        level->cameraYOld = level->cameraY;

        level->redraw = FALSE;
    }
}