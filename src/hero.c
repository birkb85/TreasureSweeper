#include "hero.h"

uint8_t hero_i;
uint8_t hero_e;

void Hero_Init(struct Hero *hero, uint8_t sprStartIndex)
{
    set_sprite_data(sprStartIndex, sizeof(hero->sprIds), heroSpr);
    for (hero_i = 0; hero_i < sizeof(hero->sprIds); hero_i++)
    {
        set_sprite_tile(sprStartIndex + hero_i, sprStartIndex + hero_i);
        hero->sprIds[hero_i] = sprStartIndex + hero_i;
    }
    hero->localX = 9u << 3u;
    hero->localY = 8u << 3u;
    hero->w = 16u;
    hero->h = 16u;
    hero->dirY = 0u;
    hero->dirX = 0u;
    hero->redraw = TRUE;
}

void Hero_MoveX(struct Hero *hero, int8_t x)
{
    hero->localX += x;
    hero->redraw = TRUE;
}

void Hero_MoveY(struct Hero *hero, int8_t y)
{
    hero->localY += y;
    hero->redraw = TRUE;
}

void Hero_Draw(struct Hero *hero)
{
    if (hero->redraw)
    {
        move_sprite(hero->sprIds[0u], localOffsetX + hero->localX, localOffsetY + hero->localY);
        move_sprite(hero->sprIds[1u], localOffsetX + hero->localX + 8u, localOffsetY + hero->localY);
        move_sprite(hero->sprIds[2u], localOffsetX + hero->localX, localOffsetY + hero->localY + 8u);
        move_sprite(hero->sprIds[3u], localOffsetX + hero->localX + 8u, localOffsetY + hero->localY + 8u);
        hero->redraw = FALSE;
    }
}