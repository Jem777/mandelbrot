#include "surface.h"

void convert_uint(unsigned char *target, unsigned int index, unsigned int value);
void convert_ushort(unsigned char *target, unsigned int index, unsigned short value);


surface_t *create_surface(unsigned int w, unsigned int h) {
    surface_t *s = (surface_t*)malloc(sizeof(surface_t));
    s->w = w;
    s->h = h;
    pixel_t *array = (pixel_t*)malloc(sizeof(pixel_t)*w*h);
    s->pixels = array;
    return s;
}

void destroy_surface(surface_t *s) {
    free(s->pixels);
    free(s);
}

void set_pixel(surface_t *s, unsigned int w, unsigned int h, pixel_t color) {
    if (w <= s->w && h <= s->h) {
        s->pixels[w + h * s->w] = color;
    }
}

pixel_t get_pixel(surface_t *s, unsigned int w, unsigned int h) {
    return s->pixels[w + h * s->w];
}

int write_bmp(surface_t *s, const char *path) {
    FILE *handler = fopen(path, "wb");
    if (handler == NULL) {
        return 1;
    }

    unsigned char header[54];
    header[0] = 'B';
    header[1] = 'M';
    convert_uint(header, 2, 54 + 3 * s->w * s->h); // file size
    convert_uint(header, 6, 0); // reserved
    convert_uint(header, 10, 54); // start of the bitmap
    convert_uint(header, 14, 40); // header size
    convert_uint(header, 18, s->w); // width
    convert_uint(header, 22, s->h); // height
    convert_ushort(header, 26, 1); // bullshit
    convert_ushort(header, 28, 24); // bpp
    convert_uint(header, 30, 0); // compression
    convert_uint(header, 34, 54 + 3 * s->w * s->h); // compressed filesize
    convert_uint(header, 38, 0); // horizontal resolution
    convert_uint(header, 42, 0); // vertical resolution
    convert_uint(header, 46, 0); // number colors
    convert_uint(header, 50, 0); // number important colors

    fwrite(header, sizeof(unsigned char), 54, handler);

    unsigned char pixel[3];
    pixel_t p;
    for (unsigned int i = 0; i < s->w; i++) {
        for (unsigned int j = 0; j < s->h; j++) {
            p = get_pixel(s, s->w - i, s->h - j);
            pixel[0] = p.b;
            pixel[1] = p.g;
            pixel[2] = p.r;
            fwrite(pixel, sizeof(unsigned char), 3, handler);
        }
    }
    fclose(handler);
    return 0;
}

void convert_ushort(unsigned char *target, unsigned int index, unsigned short value) {
    target[index] = (unsigned char)value;
    target[index+1] = (unsigned char)(value >> 8);
}

void convert_uint(unsigned char *target, unsigned int index, unsigned int value) {
    convert_ushort(target, index, (unsigned short)value);
    convert_ushort(target, index+2, (unsigned short)(value >> 16));
}
