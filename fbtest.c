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

#include "ansi_colors.h"

uint8_t * buf_a_ptr, buf_b_ptr;
struct fb_var_screeninfo var_info;
struct fb_fix_screeninfo fix_info;


uint32_t pixel_color(uint32_t color, struct fb_var_screeninfo* vinfo) {
    uint8_t r,g,b;
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    return (r<<vinfo->red.offset) | (g<<vinfo->green.offset) | (b<<vinfo->blue.offset);
}

void init_fb() {
    int fb_dev = open("/dev/fb0", O_RDWR);

    ioctl(fb_dev, FBIOGET_VSCREENINFO, &var_info);
    var_info.grayscale = 0;
    var_info.bits_per_pixel = 32;
    ioctl(fb_dev, FBIOPUT_VSCREENINFO, &var_info);
    ioctl(fb_dev, FBIOGET_VSCREENINFO, &var_info);

    ioctl(fb_dev, FBIOGET_FSCREENINFO, &fix_info);

    long screensize = var_info.yres_virtual * fix_info.line_length;

    buf_a_ptr = mmap(0, screensize * 2, PROT_READ | PROT_WRITE, MAP_SHARED, fb_dev, (off_t)0);
    buf_b_ptr = buf_a_ptr + screensize;
}

void cleanup() {

}

int main() {


    return 0;
}