#include "level.h"

// void Ball_Setup(struct Ball *ball, UINT8 sprStartIndex, UINT8 tileStartIndex, UINT8 isInit)
// {
//     set_sprite_tile(sprStartIndex, tileStartIndex);
//     ball->sprId = sprStartIndex;

//     ball->x = 76; //(SCREENWIDTH >> 1) - 4;
//     ball->y = 68; //(SCREENHEIGHT >> 1) - 4;
//     ball->w = 8;
//     ball->h = 8;
//     if (isInit)
//         ball->dirX = 0; // TODO BB 2021-06-21. Make random.
//     ball->dirY = 0;
//     ball->forceX = ball_forceXMin;
//     ball->forceY = 0;

//     Ball_Draw(ball);
// }