#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "utils.h"

// wrapper funtion around printf to output to console with colors
void color_printf(const char *color, const bool newline, const char *format,  ...) {
    va_list args;
    va_start(args, format);
    char *temp = malloc(sizeof(char) * 256);
    strcat(temp, color);
    strcat(temp, format);
    strcat(temp, ANSI_COLOR_RESET);
    if (newline)
        strcat(temp, "\n");
    vprintf(temp,  args);
    va_end(args);
}