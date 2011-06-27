#include "mandelbrot.h"

void test_rendering(SDL_Surface* surface){
    double zoomfactor = 200;
    complex double origin = 0 + 0*I; 
    render_frame(surface, zoomfactor, origin);
}

void render_frame(SDL_Surface* surface, double zoomfactor, complex double origin){
    for(int x=0;  x<surface->w; x++) {
        for(int y=0;  y<surface->h; y++) {
            complex double test_point = (x - surface->w/2) + (y - surface->h/2) * I;
            double scale = iterate_complex(conj(origin) + test_point/zoomfactor, 5000);
            pixel p;
            p.x = x;
            p.y = y;
            p.r = (Uint8)(255*scale);
            p.g = (Uint8)(255*scale);
            p.b = (Uint8)(255*scale);
            put_pixel(surface, p);
        }
    }
}

double iterate_complex(complex double c, int max_iteration) {
    int iteration_step = 0;
    complex double z = 0;
    double scale;
    while(creal(conj(z)*z) <= 4 && iteration_step < max_iteration){
        z = z*z + c;
        iteration_step++;
    }
    scale = iteration_step / max_iteration;
    return scale;
}
