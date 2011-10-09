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
} targets_t;

void render_frame(surface_t*, real zoomfactor, complexreal origin, real iteration_depth);
real iterate_complex(complexreal, int max_iteration);
pixel_t colorize(real);
void move_file(char*, char*);

void run_rendering(targets_t target_list);
rendering_t *create_rendering(rendering_t target, unsigned int length, real zfactor, real ifactor);
void destroy_rendering(rendering_t *rendering_list);
#endif
