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

#include "pallet_ansi.h"

#define sgn(x) ((x<0)?-1:((x>0)?1:0)) // macro to return the sign of a number

void * buf_a_ptr;
void * buf_b_ptr;
struct fb_var_screeninfo var_info;
struct fb_fix_screeninfo fix_info;
int fb_dev;

float rel_fb[240][240];

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

    int tty_dev = open("/dev/tty1", O_RDWR);
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
}

inline static void set_pixel(int rx, int ry, uint32_t colour) {
    long loc = (rx+var_info.xoffset) * (var_info.bits_per_pixel/8) + (ry+var_info.yoffset) * fix_info.line_length;
    if (loc > (var_info.yres_virtual * fix_info.line_length)) {
        return;
    }
    *((uint32_t*)(buf_b_ptr + loc)) = colour;
}

void r_line(int x1, int y1, int x2, int y2, uint32_t colour) {
    int dx, dy, sdx, sdy, dx_abs, dy_abs, x, y, px, py;

    dx = x2 - x1;
    dy = y2 - y1;

    dx_abs = abs(dx);
    dy_abs = abs(dy);

    sdx = sgn(dx);
    sdy = sgn(dy);
    x = dy_abs >> 1;
    y = dx_abs >> 1;
    px = x1;
    py = y1;

    set_pixel(px, py, colour);

    if (dx_abs > dy_abs) {
        for (int i = 0; i < dx_abs; ++i) {
            y += dy_abs;
            if (y >= dx_abs) {
                y -= dx_abs;
                py += sdy;
            }
            px += sdx;
            set_pixel(px, py, colour);
        }
    }
    else {
        for (int i = 0; i < dy_abs; ++i) {
            x += dx_abs;
            if (x >= dy_abs) {
                x -= dy_abs;
                px += sdx;
            }
            py += sdy;
            set_pixel(px, py, colour);
        }
    }
}

void r_polygon(int no_vertices, int* vertices, uint32_t colour) {
    for(int i=0;i<no_vertices-1;i++)
    {
        r_line(vertices[(i << 1) + 0],
               vertices[(i << 1) + 1],
               vertices[(i << 1) + 2],
               vertices[(i << 1) + 3],
               colour);
    }
    r_line(vertices[0],
           vertices[1],
           vertices[(no_vertices << 1) - 2],
           vertices[(no_vertices << 1) - 1],
           colour);
}

void r_rectangle_fill(int x1, int y1, int x2, int y2, uint32_t colour) {
    for (int y = y1; y < y2; ++y) {
        r_line(x1, y, x2, y, colour);
    }
}

void r_rectangle(int x1, int y1, int x2, int y2, uint32_t colour) {
    r_line(x1, y1, x1, y2, colour);
    r_line(x1, y1, x2, y1, colour);
    r_line(x1, y2, x2, y2, colour);
    r_line(x2, y2, x2, y1, colour);
}

void r_circle(int cx, int cy, int radius, uint32_t colour) {

}

int main() {
    init_fb();

    fill_src(RED);
    swap_buffers();


    r_rectangle(100, 100, 500, 700, BRIGHT_WHITE);
    r_rectangle_fill(101, 101, 499, 699, BLUE);
    swap_buffers();

    return 0;
}