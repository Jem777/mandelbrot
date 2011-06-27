#ifndef PIXELS_H_
#define PIXELS_H_

#include <SDL.h>
typedef struct {
    int x;
    int y;
    Uint8 r;
    Uint8 g;
    Uint8 b;
} pixel_t;

void put_pixel(struct SDL_Surface* surface, pixel_t);

#endif
