#ifndef MANDELBROT_H_
#define MANDELBEOR_H_

#include <complex.h>
#include "surface.h"

typedef struct {
    complex double origin;
    double zoomfactor;
    double iteration_depth;
    unsigned int counter;
} rendering_t;

typedef struct {
    unsigned int x, y;
    rendering_t *data;
    unsigned int length;
    unsigned int thread_number;
    unsigned int thread_max;
} targets_t;

void test_rendering(surface_t*);
void run_rendering(surface_t* surface);
void run_renderingp(targets_t);
void render_frame(surface_t*, double zoomfactor, complex double origin, double iteration_depth);
double iterate_complex(complex double, int max_iteration);
pixel_t colorize(double);
void move_file(char*, char*);

#endif
