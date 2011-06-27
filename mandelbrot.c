#include "mandelbrot.h"

void test_rendering(SDL_Surface* surface){
    double zoomfactor = 300;
    complex double origin = - 0.743643887037151 + 0.131825904205330*I; 
    render_frame(surface, zoomfactor, origin, 100);
}

void run_rendering(SDL_Surface* surface) {
    double zoomfactor = 300;
    complex double origin = - 0.743643887037151 + 0.131825904205330*I; 
    double iteration_depth = 100;
    while(1) {
        render_frame(surface, zoomfactor, origin, iteration_depth);

        SDL_PumpEvents();

        SDL_UpdateRect(surface, 0, 0, 0, 0);
        
        zoomfactor *= 1.2;
        iteration_depth += 100.0;
        printf("iteration depth: %e, iterations: %e\n", iteration_depth, surface->w*surface->h*iteration_depth);

        if(zoomfactor > 300000000000) {
            exit(0);
        }
    }
}

void render_frame(SDL_Surface* surface, double zoomfactor, complex double origin, double iteration_depth){
    for(int x=0;  x<surface->w; x++) {
        for(int y=0;  y<surface->h; y++) {
            complex double test_point = (x - surface->w/2) + (y - surface->h/2) * I;
            double scale = iterate_complex(conj(origin) + test_point/zoomfactor, iteration_depth);
            pixel_t p = colorize(scale);
            p.x = x;
            p.y = y;
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
    scale = (double)iteration_step / max_iteration;
    return scale;
}

pixel_t colorize(double scale) {
    pixel_t p;
    p.x = 0;
    p.y = 0;
    p.r = (Uint8)(255*scale);
    p.g = (Uint8)(255*scale);
    p.b = (Uint8)(255*scale);
    return p;
}
