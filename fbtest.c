//
// Created by ellie on 21/03/2022.
//

#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "ansi_colors.h"

uint32_t pixel_color(uint32_t color, struct fb_var_screeninfo* vinfo) {
    uint8_t r,g,b;
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    return (r<<vinfo->red.offset) | (g<<vinfo->green.offset) | (b<<vinfo->blue.offset);
}

void test_pattern(struct fb_var_screeninfo *vinfo, struct fb_fix_screeninfo *finfo,  uint8_t *fbp) {
    for (int x = 0; x < vinfo->xres; x++) {
        for (int y = 0; y < vinfo->yres; y++) {
            long location =
                    (x + vinfo->xoffset) * (vinfo->bits_per_pixel / 8) + (y + vinfo->yoffset) * finfo->line_length;
            *((uint32_t*)(fbp + location)) = pixel_color(YELLOW, vinfo);
        }
    }
}

int main() {
    struct fb_fix_screeninfo finfo;
    struct fb_var_screeninfo vinfo;

    int fb_fd = open("/dev/fb0",O_RDWR);

    //Get variable screen information
    ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);
    vinfo.grayscale=0;
    vinfo.bits_per_pixel=32;
    ioctl(fb_fd, FBIOPUT_VSCREENINFO, &vinfo);
    ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);

    ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo);

    long screensize = vinfo.yres_virtual * finfo.line_length;

    uint8_t *fbp = mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, (off_t)0);

    test_pattern(&vinfo, &finfo, fbp);

    return 0;
}