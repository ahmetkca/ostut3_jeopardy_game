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
int compare_two_players_by_score(const void * a, const void * b)
{
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
    for (long unsigned int i = 0; i < (strlen(ans) - 1); i++) {
        tmp_ans[i] = ans[i];
    }
    strcpy(tokens[2], tmp_ans);
}


// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players){
    
    //Quick sort players score
    qsort(players, num_players, sizeof(player), compare_two_players_by_score);

    //Print player scores by ranking
    char * rand_ansi_color = get_random_ansi_color();
    for(int i = 0; i < NUM_PLAYERS; i++){
        color_printf(rand_ansi_color ,true, "Rank: %d\t Name: %s\tScore:%d", i+1, players[i].name, players[i].score);
    }
    free(rand_ansi_color);
}

// check if the given response is at least 3 words
// for example:
//          what is table
//          who is masoud
bool is_valid_response(char *response) {
    char delim[2] = { ' ', 0 };
    char *token = strtok(response, delim);
    int i = 0;
    while (token != NULL) {
        i++;
        token = strtok(NULL, delim);
    }
    if (i >= 3)
        return true;
    return false;
}

int main(void)
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    // char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    set_questions_file_path("questions.txt");
    initialize_game();

    // Prompt for players names
    color_printf(ANSI_COLOR_CYAN, true, "Welcome to Jeopardy");
    color_printf(ANSI_COLOR_RED, true, "Please enter the players names: ");
    
    // initialize each of the players in the array
    for(int i =0; i < NUM_PLAYERS; i++){
        player *p = &players[i];
        do {
            printf("Enter %d. player name: ", (i+1));
            fgets(p->name, sizeof p->name, stdin);
            // check for new line 
            p->name[strcspn(p->name, "\r\n")] = 0;
            // scanf("%s", p->name);

        } while(strlen(p->name) <= (unsigned long) 0);
        printf("%d. player's name is %s\n", (i+1), p->name);
        p->score = 0;
    }

    
    // Perform an infinite loop getting command input from users until game ends
    // while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    // {
        
        //variables
        int num_questions = NUM_QUESTIONS;
        char *category = malloc(sizeof(char)*BUFFER_LEN);
        int value = 0;
        char response[BUFFER_LEN];
        char token[3][BUFFER_LEN] = {{0}};

        // Execute the game until all questions are answered
        // while(num_questions > 0){

             // Call functions from the questions and players source files

            for(int i = 0; i < NUM_PLAYERS && num_questions > 0; i++)
            {
                printf("DEBUG: Number of questions: %d\n", num_questions);
                display_categories();

                // Pick Category
                do {
                    color_printf(ANSI_COLOR_MAGENTA, false, "It is %s turn. \nPlease select the category: ",players[i].name);
                    scanf("%s", category);
                    getchar();
                } while (category_exists(category) == false);
                

                // Pick value of question
                do {
                    color_printf(ANSI_COLOR_BLUE, false, "The value of question: ");
                    scanf("%d", &value);
                    getchar();
                    // Display question
                } while(display_question(category, value) == false);
                
                // take player's response for the current question
                char temp_response[BUFFER_LEN];
                do {
                    printf("Please state What is or Who is before your answer.\n");
                    printf("%s", "Enter your answer: ");
                    scanf("%[^\n]", response);
                    getchar();
                    strcpy(temp_response, response);
                } while(is_valid_response(temp_response) == false);
                
                tokenize(response, token);
                
                printf("DEBUG: Response %s\n", token[2]);
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
                num_questions--;
            }
            free(category);
        // }
    // }
    show_results(players, NUM_PLAYERS);
    return EXIT_SUCCESS;        
}