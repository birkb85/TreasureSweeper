#include "global.h"
#include "hero.h"
#include "level.h"
#include "../res/splash_data.c"
#include "../res/splash_map.c"
#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <rand.h>

// struct Level level;

struct Hero hero;

uint8_t controls;

void ShowTitleScreen()
{
    DISPLAY_OFF;
    set_bkg_data(0, 212, splash_data);
    set_bkg_tiles(0, 0, 20, 18, splash_map);        
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
    waitpad(J_START | J_SELECT);
    waitpadup();
    Global_ClearBKG();
}

void Init()
{
    initarand(DIV_REG);

    Hero_Init(&hero, 0);
}

void Update()
{
    controls = joypad();
    if (controls & J_LEFT)
    {
        Hero_MoveX(&hero, -1);
    }
    else if (controls & J_RIGHT)
    {
        Hero_MoveX(&hero, 1);
    }
    if (controls & J_UP)
    {
        Hero_MoveY(&hero, -1);
    }
    else if (controls & J_DOWN)
    {
        Hero_MoveY(&hero, 1);
    }    
}

void Draw()
{
    Hero_Draw(&hero);
}

void main(void)
{
    ShowTitleScreen();
    Init();
    while (1)
    {
        Update();
        Draw();
        wait_vbl_done();
    }
}
