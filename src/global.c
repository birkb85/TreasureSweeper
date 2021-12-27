#include "global.h"

void Global_ClearBKG()
{
    for (uint8_t x = 0; x < 20; x++)
        for (uint8_t y = 0; y < 18; y++)
            set_bkg_tile_xy(x, y, 0xFF);
}

uint8_t frame;
void Global_Wait(uint8_t frames)
{
    frame = 0;
    while (frame < frames)
    {
        frame++;
        wait_vbl_done();
    }
}