#include "mandelbrot.h"

void test_rendering(surface_t* surface){
    double zoomfactor = 300;
    complex double origin = - 0.743643887037151 + 0.131825904205330*I; 
    render_frame(surface, zoomfactor, origin, 100);
    write_bmp(surface, "foobar.bmp");
}

void run_rendering(surface_t* surface) {
    double zoomfactor = 300;
    complex double origin = - 0.743643887037151 + 0.131825904205330*I; 
    double iteration_depth = 100;
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

void render_frame(surface_t* surface, double zoomfactor, complex double origin, double iteration_depth){
    for(unsigned int x=0;  x<surface->w; x++) {
        for(unsigned int y=0;  y<surface->h; y++) {
            complex double test_point = (x - surface->w/2) + (y - surface->h/2) * I;
            double scale = iterate_complex(conj(origin) + test_point/zoomfactor, iteration_depth);
            //pixel_t p = colorize(scale);
            //set_pixel(surface, x, y, p);
            pixel_t p;
            p.r = (unsigned char)(255*scale);
            p.g = (unsigned char)rand();
            p.b = 0;
            set_pixel(surface, x, y, p);
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
    p.r = (unsigned char)(255*scale);
    p.g = (unsigned char)(255*scale);
    p.b = (unsigned char)(255*scale);
    return p;
}
