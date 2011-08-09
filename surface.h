#ifndef SURFACE_H_
#define SURFACE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} pixel_t;

typedef struct{
    unsigned int w;
    unsigned int h;
    pixel_t *pixels;
} surface_t;

surface_t *create_surface(unsigned int, unsigned int);
void destroy_surface(surface_t*);

void set_data(surface_t*, unsigned int, unsigned int, pixel_t*);
void set_pixel(surface_t*, unsigned int, unsigned int, pixel_t);
pixel_t get_pixel(surface_t*, unsigned int, unsigned int);
int write_bmp(surface_t*, const char*);

#endif
