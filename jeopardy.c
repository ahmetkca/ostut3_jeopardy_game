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
#include "utils.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Compare function used to sort players array by score 
int compare_two_players_by_score(const void * a, const void * b){
    player *playerA = (player *)a; 
    player *playerB = (player *)b;
    return (playerB->score - playerA->score);
}

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char tokens[3][MAX_LEN]) {
    char delim[2];
    delim[0] = ' ';
    delim[1] = 0;
    char ans[MAX_LEN] = {0};
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
    strcpy(tokens[2], tmp_ans);
}


// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players){
    
    //Quick sort players score
    qsort(players, num_players, sizeof(player), compare_two_players_by_score);

    //Print player scores by ranking
    for(int i = 0; i < NUM_PLAYERS; i++){
        color_printf(ANSI_COLOR_GREEN ,true, "Rank: %d\t Name: %s\tScore:%d", i+1, players[i].name, players[i].score);
    }
}

int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    set_questions_file_path("questions.txt");
    initialize_game();

    // Prompt for players names
    color_printf(ANSI_COLOR_CYAN, true, "Welcome to Jeopardy");
    color_printf(ANSI_COLOR_RED, true, "Please enter the players names: ");
    
    // initialize each of the players in the array
    for(int i =0; i < NUM_PLAYERS; i++){
        scanf("%s", players[i].name);
        players[i].score = 0;
    }
    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        
        //variables
        int questions = NUM_QUESTIONS;
        char *category = malloc(sizeof(char)*BUFFER_LEN);
        int value = 0;
        char response[BUFFER_LEN];
        char token[3][BUFFER_LEN] = {{0}};

        // Execute the game until all questions are answered
        while(questions != 0){

             // Call functions from the questions and players source files

            for(int i = 0; i < NUM_PLAYERS; i++)
            {
                    display_categories();

                    // Pick Category
                    color_printf(ANSI_COLOR_MAGENTA, false, "It is %s turn. \nPlease select the category: ",players[i].name);
                    scanf("%s", category);
                    getchar();

                    // Pick value of question
                    color_printf(ANSI_COLOR_BLUE, false, "The value of question: ");
                    scanf("%d", &value);
                    getchar();
                    
                    // Display question take player response
                    display_question(category, value);
                    printf("%s", "Enter your answer: ");
                    scanf("%[^\n]", response);
                    getchar();

                    tokenize(response, token);
                    
                    if(valid_answer(category,value,token[2]) == true)
                    {
                        color_printf(ANSI_COLOR_GREEN, true, "Your answer is correct you may choose again.");
                        update_score(players, NUM_PLAYERS, players[i].name, value);
                        i--;
                    }
                    else
                    {
                        color_printf(ANSI_COLOR_RED, true, "Sorry that is the incorrect answer.");
                    }
                    questions--;
                }
            }
            show_results(players, NUM_PLAYERS);
        }          
        
        return EXIT_SUCCESS;
}
    

