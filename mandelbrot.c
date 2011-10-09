#include "mandelbrot.h"
#include <stdio.h>
#include <errno.h>

void test_rendering(surface_t* surface){
    real zoomfactor = 300;
    complexreal origin = - 0.743643887037151 + 0.131825904205330*I; 
    render_frame(surface, zoomfactor, origin, 100);
    write_bmp(surface, "foobar.bmp");
}

void run_single_rendering(surface_t* surface) {
    real zoomfactor = 300;
    complexreal origin = - 0.743643887037151 + 0.131825904205330*I; 
    real iteration_depth = 100;
    int counter = 0;
    while(1) {
        if(zoomfactor > 300000000000 || counter == 10) {
            exit(0);
        }
        render_frame(surface, zoomfactor, origin, iteration_depth);

        zoomfactor *= 1.01;
        iteration_depth += 2.0;
        printf("iteration depth: %e, iterations: %e\n", iteration_depth, surface->w*surface->h*iteration_depth);

        char output_file[100];
        snprintf(output_file, 100, "out_%04d.bmp", counter);
        write_bmp(surface, output_file);
        //printf("%s\n", output_file);
        counter++;
    }
}

void render_frame(surface_t* surface, real zoomfactor, complexreal origin, real iteration_depth){
    for(unsigned int x=0;  x < surface->w; x++) {
        for(unsigned int y=0;  y < surface->h; y++) {
            complexreal test_point = ((int)x - (int)surface->w / 2) + ((int)y - (int)surface->h / 2) * I;
            real scale = iterate_complex(origin + test_point/zoomfactor, iteration_depth);
            pixel_t p = colorize(scale);
            set_pixel(surface, x, y, p);
        }
    }
}

real iterate_complex(complexreal c, int max_iteration) {
    int iteration_step = 0;
    complexreal z = 0;
    real scale;
    while(creal(conj(z)*z) <= 4 && iteration_step < max_iteration){
        z = z*z + c;
        iteration_step++;
    }
    scale = (real)iteration_step / max_iteration;
    return scale;
}

pixel_t colorize(real scale) {
    pixel_t p;
    p.r = (unsigned char)(255*scale);
    p.g = (unsigned char)(255*scale);
    p.b = (unsigned char)(255*scale);
    return p;
}

void move_file(char *file, char *dirname){
  char newname[256];
  snprintf(newname, 256, "%s/%s", dirname, file);
  if(rename(file, newname) == -1){
    char errormessage[256];
    snprintf(errormessage, 256, "Error moving '%s' to '%s/'", file, dirname);
    perror(errormessage);
  }
}

rendering_t *create_rendering(rendering_t target, unsigned int length, real zfactor, real ifactor) {
    rendering_t *rendering_list = malloc(sizeof(rendering_t) * length);
    real current_zoom = target.zoomfactor;
    real current_depth = target.iteration_depth;
    for (unsigned int i = 0; i < length; i++) {
        rendering_list[i].origin = target.origin;
        rendering_list[i].zoomfactor = current_zoom;
        rendering_list[i].iteration_depth = current_depth;
        rendering_list[i].counter = i;
        current_zoom *= zfactor;
        current_depth += ifactor;
    }
    return rendering_list;
}

void destroy_rendering(rendering_t *rendering_list) {
    free(rendering_list);
}

void run_rendering(targets_t target_list) {
    char output_file[100];
    surface_t *surface;
#pragma omp parallel private(surface)
    {
    surface = create_surface(target_list.x, target_list.y);
#pragma omp for private(output_file)
    for (unsigned int i = 0; i < target_list.length; i++) {
        printf("rendering target %d\n", target_list.data[i].counter);
        render_frame(surface, target_list.data[i].zoomfactor, target_list.data[i].origin, target_list.data[i].iteration_depth);
        snprintf(output_file, 100, "out_%04d.bmp", target_list.data[i].counter);
        write_bmp(surface, output_file);
        move_file(output_file, "output");
    }
    destroy_surface(surface);
    }
}

