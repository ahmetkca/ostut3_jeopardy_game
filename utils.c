#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include "utils.h"

#define BUFLEN 256
#define MAX_RGB_VAL 255


// wrapper funtion around printf to output to console with colors
void color_printf(const char *color, const bool newline, const char *format,  ...) {
    char temp[BUFLEN*8] = {0};
    strcat(temp, color);
    strcat(temp, format);
    strcat(temp, ANSI_COLOR_RESET);
    if (newline == true) {
        strcat(temp, "\n");
    }
    va_list args;
    va_start(args, format);
    vprintf(temp,  args);
    va_end(args);
}

// random ansi color generator
char * get_random_ansi_color(void) {
    int rand_rgb_val = rand() % 255;
    char * random_ansi_color;
    if (random_ansi_color != NULL)
        random_ansi_color = malloc((64 * sizeof(char))+1);
    snprintf(random_ansi_color, 64 - 1, "\x1b[38;5;%dm", rand_rgb_val);
    return random_ansi_color;
}