#ifndef MANDELBROT_H_
#define MANDELBEOR_H_

#include <SDL.h>
#include <complex.h>
#include <math.h>

#include "pixels.h"

void test_rendering(SDL_Surface*);
void render_frame(SDL_Surface*, double zoomfactor, complex double origin);
double iterate_complex(complex double, int max_iteration);

#endif
