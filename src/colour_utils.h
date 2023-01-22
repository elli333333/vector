//
// Created by ellie on 21/03/2022.
//

#ifndef VECTOR_COLOUR_UTILS_H
#define VECTOR_COLOUR_UTILS_H

#define BLACK               0x010101
#define RED                 0xDE382B
#define GREEN               0x39B54A
#define YELLOW              0xFFC706
#define BLUE                0x006FB8
#define MAGENTA             0x762671
#define CYAN                0x30B5B8
#define WHITE               0xCCCCCC
#define BRIGHT_BLACK        0x7F7F7F
#define BRIGHT_RED          0xFF0000
#define BRIGHT_GREEN        0x00FF00
#define BRIGHT_YELLOW       0xFFFF00
#define BRIGHT_BLUE         0x0000FF
#define BRIGHT_MAGENTA      0xFF00FF
#define BRIGHT_CYAN         0x00FFFF
#define BRIGHT_WHITE        0xFFFFFF

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

#endif //VECTOR_COLOUR_UTILS_H
