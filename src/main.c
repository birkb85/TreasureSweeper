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
    Hero_Init(&hero, 0u);
}

void Update()
{
    controls = joypad();
    if (controls & J_UP)
    {
        if (!Level_MoveCameraUp(&level, 1))
            Hero_MoveY(&hero, -1);
    }
    else if (controls & J_DOWN)
    {
        if (!Level_MoveCameraDown(&level, 1))
            Hero_MoveY(&hero, 1);
    }
    if (controls & J_LEFT)
    {
        if (!Level_MoveCameraLeft(&level, 1))
            Hero_MoveX(&hero, -1);
    }
    else if (controls & J_RIGHT)
    {
        if (!Level_MoveCameraRight(&level, 1))
            Hero_MoveX(&hero, 1);
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
