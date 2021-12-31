#ifndef GLOBAL_H
#define GLOBAL_H

#include <gb/gb.h>

#define localOffsetX 8u
#define localOffsetY 16u
#define localCenterX (10u << 3u)
#define localCenterY (9u << 3u)

extern void Global_ClearBKG();
extern void Global_Wait(uint8_t frames);

#endif