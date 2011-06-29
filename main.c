#include <stdio.h>

#include "mandelbrot.h"

int main(void){
    //SDL_SetVideoMode(400, 400, 24, SDL_SWSURFACE);
    //SDL_Surface *main_surface = SDL_GetVideoSurface();

    //run_rendering(main_surface);

    surface_t *surface = create_surface(800, 820);
    run_rendering(surface);
    //write_bmp(surface, "foobar.bmp");

    return 0;
}
