//
// Created by ellie on 21/03/2022.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <fcntl.h>
#include <linux/fb.h>
#include <linux/kd.h>

#include <sys/ioctl.h>
#include <sys/mman.h>

#include <string.h>

#include <math.h>
#include <complex.h>

#include "pallet_ansi.h"

#define sgn(x) ((x<0)?-1:((x>0)?1:0)) // macro to return the sign of a number

void * buf_a_ptr;
void * buf_b_ptr;
struct fb_var_screeninfo var_info;
struct fb_fix_screeninfo fix_info;
int fb_dev;
int tty_dev;


#define scr_x 1024
#define scr_y 768
uint32_t rel_fb[scr_x][scr_y]; // relative scale framebuffer [x][y], adjusted such that rel_fb[0][0] is lower right

uint32_t set_pixel_color(uint32_t color) {
    uint8_t r,g,b;
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    return (r<<var_info.red.offset) | (g<<var_info.green.offset) | (b<<var_info.blue.offset);
}

void init_fb() {
    fb_dev = open("/dev/fb0", O_RDWR);

    ioctl(fb_dev, FBIOGET_VSCREENINFO, &var_info);
    var_info.grayscale = 0;
    var_info.bits_per_pixel = 32;
    ioctl(fb_dev, FBIOPUT_VSCREENINFO, &var_info);
    ioctl(fb_dev, FBIOGET_VSCREENINFO, &var_info);

    ioctl(fb_dev, FBIOGET_FSCREENINFO, &fix_info);

    long screensize = var_info.yres_virtual * fix_info.line_length;

    buf_a_ptr = mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_dev, (off_t)0);
    buf_b_ptr = mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t)0);

    tty_dev = open("/dev/tty1", O_RDWR);
    ioctl(tty_dev, KDSETMODE, KD_GRAPHICS);
}

void swap_buffers() {
    long screensize = var_info.yres_virtual * fix_info.line_length;

    memcpy(buf_a_ptr, buf_b_ptr, screensize);
}

inline static void memset_uint32(uint32_t* ptr, uint32_t val, size_t size){
    while(size--) *ptr++ = val;
}

void fill_src(uint32_t colour) {
    long screensize = var_info.yres_virtual * fix_info.line_length;
    memset_uint32(buf_b_ptr, colour, screensize/4);
    for (int x = 0; x < scr_x; ++x) {
        memset_uint32(rel_fb[x], colour, scr_y);
    }
}

inline static void set_pixel(int rx, int ry, uint32_t colour) {
    long loc = (rx+var_info.xoffset) * (var_info.bits_per_pixel/8) + (ry+var_info.yoffset) * fix_info.line_length;
    if (loc > (var_info.yres_virtual * fix_info.line_length)) {
        return;
    }
    *((uint32_t*)(buf_b_ptr + loc)) = colour;
}

uint32_t rgb(double ratio) {
    // derived from https://stackoverflow.com/a/40639903/12454856
    int normalized = (int)(ratio * 256 * 6);

    int x = normalized % 256;

    int red = 0;
    int green = 0;
    int blue = 0;

    switch (normalized / 256) {
        case 0:
            red = 255;
            green = x;
            blue = 0;
            break;
        case 1:
            red = 255 - x;
            green = 255;
            blue = 0;
            break;
        case 2:
            red = 0;
            green = 255;
            blue = x;
            break;
        case 3:
            red = 0;
            green = 255 - x;
            blue = 255;
            break;
        case 4:
            red = x;
            green = 0;
            blue = 255;
            break;
        case 5:
            red = 255;
            green = 0;
            blue = 255 - x;
            break;
    }

    return red + (green << 8) + (blue << 16);
}

void escape_time() {
    int max_iter = 1024;

    double left = -2,
        right = 1,
        top = 1.125,
        bottom = -1.125;

    double complex c, z;
    int iterations;

    for (int y = 0; y < scr_y; ++y) {
        for (int x = 0; x < scr_x; ++x) {
            c = (left + (x * (right - left)) / scr_x) +
                    ((top + (y * (bottom - top)) / scr_y) * I);
            z = 0 + (0 * I);

            iterations = 0;
            while ((cabs(z) < 2.0) && (iterations < max_iter)) {
                z = ((z*z) + c);
                ++iterations;
            }
            if (iterations == max_iter) {
                set_pixel(x, y, BLACK);
            }
            else {
                uint32_t colour = rgb((double)((double)iterations / max_iter));
                set_pixel(x, y, colour);
            }
        }
    }
}

int main() {
    init_fb();

//    fill_src(BLUE);
//    f_rectangle(99, 99, 513, 513, BRIGHT_WHITE);
//    f_rectangle_fill(100, 100, 512, 512, BRIGHT_CYAN);
//    f_swap();

    escape_time();
    swap_buffers();

    ioctl(tty_dev,KDSETMODE,KD_TEXT);
    return 0;
}