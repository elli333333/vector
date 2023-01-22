//
// Created by ellie on 03/04/2022.
//

#ifndef VECTOR_FBTEST_EXTRAS_H
#define VECTOR_FBTEST_EXTRAS_H

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

void f_swap() {
    for (int x = 0; x < scr_x; ++x) {
        for (int y = 0; y < scr_y; ++y) {
            set_pixel(x,(scr_y - y), rel_fb[x][y]);
        }
    }
    swap_buffers();
}

void f_line(int x1, int y1, int x2, int y2, uint32_t colour) {
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

    rel_fb[px][py] = colour;

    if (dx_abs > dy_abs) {
        for (int i = 0; i < dx_abs; ++i) {
            y += dy_abs;
            if (y >= dx_abs) {
                y -= dx_abs;
                py += sdy;
            }
            px += sdx;
            rel_fb[px][py] = colour;
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
            rel_fb[px][py] = colour;
        }
    }
}

void f_polygon(int no_vertices, int* vertices, uint32_t colour) {
    for(int i=0;i<no_vertices-1;i++)
    {
        f_line(vertices[(i << 1) + 0],
               vertices[(i << 1) + 1],
               vertices[(i << 1) + 2],
               vertices[(i << 1) + 3],
               colour);
    }
    f_line(vertices[0],
           vertices[1],
           vertices[(no_vertices << 1) - 2],
           vertices[(no_vertices << 1) - 1],
           colour);
}

void f_rectangle_fill(int x1, int y1, int x2, int y2, uint32_t colour) {
    for (int y = y1; y < y2; ++y) {
        f_line(x1, y, x2, y, colour);
    }
}

void f_rectangle(int x1, int y1, int x2, int y2, uint32_t colour) {
    f_line(x1, y1, x1, y2, colour);
    f_line(x1, y1, x2, y1, colour);
    f_line(x1, y2, x2, y2, colour);
    f_line(x2, y2, x2, y1, colour);
}

#endif //VECTOR_FBTEST_EXTRAS_H
