#ifndef MANDELBROT_H_
#define MANDELBEOR_H_

#include <complex.h>
#include "surface.h"

typedef struct {
    complex double origin;
    double zoomfactor;
    double iteration_depth;
    unsigned int counter;
}rendering_t;

void test_rendering(surface_t*);
void run_rendering(surface_t* surface);
void run_renderingp(unsigned int x, unsigned int y, rendering_t *data, unsigned length);
void render_frame(surface_t*, double zoomfactor, complex double origin, double iteration_depth);
double iterate_complex(complex double, int max_iteration);
pixel_t colorize(double);


#endif
