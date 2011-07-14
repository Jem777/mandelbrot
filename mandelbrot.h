#ifndef MANDELBROT_H_
#define MANDELBEOR_H_

#include <complex.h>
#include "surface.h"
#include "common.h"

typedef struct {
    complexreal origin;
    real zoomfactor;
    real iteration_depth;
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
void render_frame(surface_t*, real zoomfactor, real origin_r, real origin_i, real iteration_depth);
real iterate_complex(real, real, int max_iteration);
pixel_t colorize(real);
void move_file(char*, char*);

#endif
