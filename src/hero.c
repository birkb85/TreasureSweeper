#include "hero.h"

void Hero_Init(struct Hero *hero, uint8_t sprStartIndex)
{
    set_sprite_data(sprStartIndex, 18u, heroSpr);
    for (uint8_t i = 0; i < sizeof(hero->sprIds); i++)
    {
        set_sprite_tile(sprStartIndex + i, sprStartIndex + i);
        hero->sprIds[i] = sprStartIndex + i;
    }
    hero->localX = localCenterX;
    hero->localY = localCenterY;
    hero->w = 16u;
    hero->h = 16u;
    hero->halfW = hero->w >> 1u;
    hero->halfH = hero->w >> 1u;
    hero->localMinX = hero->halfW;
    hero->localMinY = hero->halfH;
    hero->localMaxX = (20u << 3u) - hero->halfW;
    hero->localMaxY = (18u << 3u) - hero->halfH;
    hero->dir = Hero_Dir_Down;
    hero->redraw = TRUE;
}

void Hero_SetDir(struct Hero *hero, enum Hero_Dir dir)
{
    hero->dir = dir;
    hero->redraw = TRUE;
}

void Hero_MoveUp(struct Hero *hero, uint8_t amount)
{
    if (hero->localY > hero->localMinY)
    {
        hero->localY -= amount;
        hero->redraw = TRUE;
    }
}

void Hero_MoveDown(struct Hero *hero, uint8_t amount)
{
    if (hero->localY < hero->localMaxY)
    {
        hero->localY += amount;
        hero->redraw = TRUE;
    }
}

void Hero_MoveLeft(struct Hero *hero, uint8_t amount)
{
    if (hero->localX > hero->localMinX)
    {
        hero->localX -= amount;
        hero->redraw = TRUE;
    }
}

void Hero_MoveRight(struct Hero *hero, uint8_t amount)
{
    if (hero->localX < hero->localMaxX)
    {
        hero->localX += amount;
        hero->redraw = TRUE;
    }
}

void Hero_Draw(struct Hero *hero)
{
    if (hero->redraw)
    {
        uint8_t sprStartIndex = 0;

        switch (hero->dir)
        {
        case Hero_Dir_Up:
            sprStartIndex = 6;
            break;

        case Hero_Dir_Down:
            sprStartIndex = 0;
            break;

        case Hero_Dir_Left:
            sprStartIndex = 12;
            break;

        case Hero_Dir_Right:
            sprStartIndex = 12;
            break;

        default:
            break;
        }

        // TODO BB 2021-12-30. Evt. lave retning bedre, så man kan genbruge tiles til ben..
        // TODO BB 2021-12-30. Tilføj animation.
        if (hero->dir == Hero_Dir_Left)
        {
            for (uint8_t i = 0u; i < sizeof(hero->sprIds); i++)
            {
                set_sprite_prop(hero->sprIds[i], S_FLIPX);
            }
            set_sprite_tile(hero->sprIds[0u], sprStartIndex + 1);
            set_sprite_tile(hero->sprIds[1u], sprStartIndex + 0);
            set_sprite_tile(hero->sprIds[2u], sprStartIndex + 3);
            set_sprite_tile(hero->sprIds[3u], sprStartIndex + 2);
            set_sprite_tile(hero->sprIds[4u], sprStartIndex + 5);
            set_sprite_tile(hero->sprIds[5u], sprStartIndex + 4);
        }
        else
        {
            for (uint8_t i = 0u; i < sizeof(hero->sprIds); i++)
            {
                set_sprite_prop(hero->sprIds[i], 0x00u);
                set_sprite_tile(hero->sprIds[i], sprStartIndex + i);
            }
        }

        uint8_t xLeft = localOffsetX + hero->localX - hero->halfW;
        uint8_t yTop = localOffsetY + hero->localY - hero->halfH - 8u;
        move_sprite(hero->sprIds[0u], xLeft, yTop);
        move_sprite(hero->sprIds[1u], xLeft + 8u, yTop);
        move_sprite(hero->sprIds[2u], xLeft, yTop + 8u);
        move_sprite(hero->sprIds[3u], xLeft + 8u, yTop + 8u);
        move_sprite(hero->sprIds[4u], xLeft, yTop + 16u);
        move_sprite(hero->sprIds[5u], xLeft + 8u, yTop + 16u);
        hero->redraw = FALSE;
    }
}