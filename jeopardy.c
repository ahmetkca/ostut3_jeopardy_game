/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// wrapper funtion around printf to output to console with colors
void color_printf(const char *color, const bool *newline, const char *format,  ...) {
    va_list args;
    va_start(args, format);
    char *temp = malloc(1);
    strcat(temp, color);
    strcat(temp, format);
    strcat(temp, ANSI_COLOR_RESET);
    if (newline)
        strcat(temp, "\n");
    vprintf(temp,  args);
    va_end(args);
}

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens) {
    char delim[2];
    delim[0] = ' ';
    delim[1] = 0;
    char *ans = malloc(1);
    char *token = strtok(input, delim);
    int i = 0;
    while (token != NULL) {
        if (i > 1) {
            strcat(ans, token);
            strcat(ans, " ");
        } else {
            strcpy(tokens[i], token);
        }
        token = strtok(NULL, delim);
        i++;
    }
    char *tmp_ans = malloc(strlen(ans) - 1);
    for (int i = 0; i < strlen(ans) - 1; i++) {
        tmp_ans[i] = ans[i];
    }
    strcpy(token[2], tmp_ans);
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    
    // initialize each of the players in the array

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files

        // Execute the game until all questions are answered

        // Display the final results and exit
    }
    return EXIT_SUCCESS;
}
