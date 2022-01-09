#include "global.h"
#include "hero.h"
#include "level.h"
#include "../res/splash_data.c"
#include "../res/splash_map.c"
#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <rand.h>

struct Level level;

struct Hero hero;

uint8_t controls;

void ShowTitleScreen()
{
    DISPLAY_OFF;
    set_bkg_data(0u, 213u, splash_data);
    set_bkg_tiles(0u, 0u, 20u, 18u, splash_map);
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
    waitpad(J_START | J_SELECT);
    waitpadup();
    Global_ClearBKG();
}

void Init()
{
    initrand(DIV_REG);

    Level_Init(&level);

    Hero_Init(&hero, level.entranceX - level.cameraX, level.entranceY - level.cameraY, 0u);
}

void Update()
{
    controls = joypad();

    if (controls & J_UP)
    {
        Hero_SetDir(&hero, Hero_Dir_Up);

        uint8_t collision = Level_CheckMapCollision(
            &level,
            (level.cameraX + hero.localX) >> 4u,
            (level.cameraY + hero.localY - 1u) >> 4u);

        if (!collision)
            collision = Level_CheckMapCollision(
                &level,
                (level.cameraX + hero.localX + (hero.w - 1u)) >> 4u,
                (level.cameraY + hero.localY - 1u) >> 4u);

        if (!collision)
        {
            if (hero.localY > hero.localCenterY)
                Hero_MoveUp(&hero, 1u);
            else if (!Level_MoveCameraUp(&level, 1u))
                Hero_MoveUp(&hero, 1u);
        }
    }
    else if (controls & J_DOWN)
    {
        Hero_SetDir(&hero, Hero_Dir_Down);

        uint8_t collision = Level_CheckMapCollision(
            &level,
            (level.cameraX + hero.localX) >> 4u,
            (level.cameraY + hero.localY + (hero.h - 1u) + 1u) >> 4u);

        if (!collision)
            collision = Level_CheckMapCollision(
                &level,
                (level.cameraX + hero.localX + (hero.w - 1u)) >> 4u,
                (level.cameraY + hero.localY + (hero.h - 1u) + 1u) >> 4u);

        if (!collision)
        {
            if (hero.localY < hero.localCenterY)
                Hero_MoveDown(&hero, 1u);
            else if (!Level_MoveCameraDown(&level, 1u))
                Hero_MoveDown(&hero, 1u);
        }
    }

    if (controls & J_LEFT)
    {
        Hero_SetDir(&hero, Hero_Dir_Left);

        uint8_t collision = Level_CheckMapCollision(
            &level,
            (level.cameraX + hero.localX - 1u) >> 4u,
            (level.cameraY + hero.localY) >> 4u);

        if (!collision)
            collision = Level_CheckMapCollision(
                &level,
                (level.cameraX + hero.localX - 1u) >> 4u,
                (level.cameraY + hero.localY + (hero.h - 1u)) >> 4u);

        if (!collision)
        {
            if (hero.localX > hero.localCenterX)
                Hero_MoveLeft(&hero, 1u);
            else if (!Level_MoveCameraLeft(&level, 1u))
                Hero_MoveLeft(&hero, 1u);
        }
    }
    else if (controls & J_RIGHT)
    {
        Hero_SetDir(&hero, Hero_Dir_Right);

        uint8_t collision = Level_CheckMapCollision(
            &level,
            (level.cameraX + hero.localX + (hero.w - 1u) + 1u) >> 4u,
            (level.cameraY + hero.localY) >> 4u);

        if (!collision)
            collision = Level_CheckMapCollision(
                &level,
                (level.cameraX + hero.localX + (hero.w - 1u) + 1u) >> 4u,
                (level.cameraY + hero.localY + (hero.h - 1u)) >> 4u);

        if (!collision)
        {
            if (hero.localX < hero.localCenterX)
                Hero_MoveRight(&hero, 1u);
            else if (!Level_MoveCameraRight(&level, 1u))
                Hero_MoveRight(&hero, 1u);
        }
    }

    if (controls & J_A)
    {
        switch (hero.dir)
        {
        case Hero_Dir_Up:
            Level_DestroyMapTile(
                &level,
                (level.cameraX + hero.localX + ((hero.w - 1u) >> 1)) >> 4u,
                (level.cameraY + hero.localY - 4u) >> 4u);
            break;

        case Hero_Dir_Down:
            Level_DestroyMapTile(
                &level,
                (level.cameraX + hero.localX + ((hero.w - 1u) >> 1)) >> 4u,
                (level.cameraY + hero.localY + (hero.h - 1u) + 4u) >> 4u);
            break;

        case Hero_Dir_Left:
            Level_DestroyMapTile(
                &level,
                (level.cameraX + hero.localX - 4u) >> 4u,
                (level.cameraY + hero.localY + ((hero.h - 1u) >> 1)) >> 4u);
            break;

        case Hero_Dir_Right:
            Level_DestroyMapTile(
                &level,
                (level.cameraX + hero.localX + (hero.w - 1u) + 4u) >> 4u,
                (level.cameraY + hero.localY + ((hero.h - 1u) >> 1)) >> 4u);
            break;
        }
    }
}

void DrawBefore()
{
    Hero_Draw(&hero);
}

void DrawAfter()
{
    Level_Draw(&level);
}

void main(void)
{
    ShowTitleScreen();
    Init();
    while (1u)
    {
        Update();
        DrawBefore();
        wait_vbl_done();
        DrawAfter();
    }
}
