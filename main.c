#include <stdio.h>

#include "mandelbrot.h"

int main(void){

    surface_t *surface = create_surface(800, 860);
    run_rendering(surface);

    return 0;
}
