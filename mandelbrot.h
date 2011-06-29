#ifndef MANDELBROT_H_
#define MANDELBEOR_H_

#include <complex.h>
#include "surface.h"

void test_rendering(surface_t*);
void run_rendering(surface_t* surface);
void render_frame(surface_t*, double zoomfactor, complex double origin, double iteration_depth);
double iterate_complex(complex double, int max_iteration);
pixel_t colorize(double);


#endif
