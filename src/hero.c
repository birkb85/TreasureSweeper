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
    hero->x = 16u;
    hero->y = 24u;
    hero->w = 16u;
    hero->h = 16u;
    hero->dirY = 0u;
    hero->dirX = 0u;
    hero->redraw = TRUE;
}

void Hero_MoveX(struct Hero *hero, int8_t x)
{
    hero->x += x;
    hero->redraw = TRUE;
}

void Hero_MoveY(struct Hero *hero, int8_t y)
{
    hero->y += y;
    hero->redraw = TRUE;
}

void Hero_Draw(struct Hero *hero)
{
    if (hero->redraw)
    {
        move_sprite(hero->sprIds[0u], hero->x, hero->y);
        move_sprite(hero->sprIds[1u], hero->x + 8u, hero->y);
        move_sprite(hero->sprIds[2u], hero->x, hero->y + 8u);
        move_sprite(hero->sprIds[3u], hero->x + 8u, hero->y + 8u);
        hero->redraw = FALSE;
    }
}