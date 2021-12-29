#include "global.h"

void Global_ClearBKG()
{
    for (uint8_t x = 0u; x < 20u; x++)
        for (uint8_t y = 0u; y < 18u; y++)
            set_bkg_tile_xy(x, y, 0xFFu);
}

uint8_t frame;
void Global_Wait(uint8_t frames)
{
    frame = 0u;
    while (frame < frames)
    {
        frame++;
        wait_vbl_done();
    }
}