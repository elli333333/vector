//
// Created by ellie on 21/03/2022.
//

#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <string.h>

#include "pallet_ansi.h"

#define pixel(x, y) *((uint32_t*)(buf_b_ptr + (x+var_info.xoffset) * (var_info.bits_per_pixel/8) + (y+var_info.yoffset) * fix_info.line_length))

void * buf_a_ptr;
void * buf_b_ptr;
struct fb_var_screeninfo var_info;
struct fb_fix_screeninfo fix_info;
int fb_dev;


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

int main() {
    init_fb();

    fill_src(CYAN);
    swap_buffers();

    return 0;
}