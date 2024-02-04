//
// Created by ellie on 21/03/2022.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <fcntl.h>
#include <linux/fb.h>
#include <linux/kd.h>

#include <sys/ioctl.h>
#include <sys/mman.h>

#include <string.h>

#include <math.h>
#include <complex.h>

#include <ncurses.h>

#include "../oldsrc/colour_utils.h"

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

void escape_time(double left, double right, double top, double bottom) {
    int max_iter = 1024;

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

    initscr();
    noecho();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    bool running = true;

    double left = -2,
            right = 1,
            top = 1.125,
            bottom = -1.125;

    fill_src(BLUE);
    swap_buffers();

    while (running) {
        int key = getch();
        switch (key) {
            case 'q':
                running = false;
                break;
            case 'w':
                top += 0.01;
                bottom += 0.01;
                break;
            case 's':
                top -= 0.01;
                bottom -= 0.01;
                break;
            case 'a':
                left += 0.01;
                right += 0.01;
                break;
            case 'd':
                left -= 0.01;
                right -= 0.01;
                break;
            default:
                ;
        }

        escape_time(left, right, top, bottom);
        swap_buffers();
    }

    endwin();
    ioctl(tty_dev,KDSETMODE,KD_TEXT);
    return 0;
}