#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "utils.h"

#define BUFLEN 256 

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