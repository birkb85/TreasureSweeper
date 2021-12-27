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
    hero->x = 16;
    hero->y = 24;
    hero->w = 16;
    hero->h = 16;
    hero->dirY = 0;
    hero->dirX = 0;

    Hero_Draw(hero);
}

void Hero_MoveX(struct Hero *hero, int8_t x)
{
    hero->x += x;
}

void Hero_MoveY(struct Hero *hero, int8_t y)
{
    hero->y += y;
}

void Hero_Draw(struct Hero *hero)
{
    move_sprite(hero->sprIds[0], hero->x, hero->y);
    move_sprite(hero->sprIds[1], hero->x + 8, hero->y);
    move_sprite(hero->sprIds[2], hero->x, hero->y + 8);
    move_sprite(hero->sprIds[3], hero->x + 8, hero->y + 8);
}