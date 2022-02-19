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
#include "questions.h"
#include "utils.h"

char * QUESTIONS_FILE_PATH;

// reads questions file line by line
// each line contains question, answer, category, value that are splitted by |
void load_questions(char *path) {
    FILE *fp;
    char buff[4*MAX_LEN];

    fp = fopen(path, "r");
    if (fp == NULL) { printf("Could not open file %s\n", path); return;  }
    char delim[2];
    delim[0] = '|';
    delim[1] = 0;
    int i = 0;
    while (fgets(buff, MAX_LEN, (FILE*)fp) != NULL && i < NUM_QUESTIONS ) {
        question *q = &questions[i];
        q->answered=false;
        char *token = strtok(buff, delim);
        int y = 0;
        char *tokens[4];
        while (token != NULL) {
            tokens[y] = token;
            token  = strtok(NULL, delim);
            y++;
        }
        strcpy(q->question, tokens[0]);
        strcpy(q->answer, tokens[1]);
        strcpy(q->category, tokens[2]);
        q->value = atoi(tokens[3]);
        i++;
    }
    fclose(fp);
}

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array

    load_questions(QUESTIONS_FILE_PATH);
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{

    // print categories and their values for each unanswered question in questions array
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered) {
            char *random_ansi_color = get_random_ansi_color();
            color_printf(random_ansi_color, true, "%s %d", questions[i].category, questions[i].value);
            free(random_ansi_color);
        } 
    }
}

// Displays the question for the category and dollar value
bool display_question(char *category, int value)
{
    for(int i = 0; i < NUM_QUESTIONS; i++){
        question *q = &questions[i];
        if((strcmp(q->category, category) == 0) && q->value == value && q->answered == false) {
            char *random_ansi_color = get_random_ansi_color();
            color_printf(random_ansi_color, true, "\nFor %d %s", questions[i].value,questions[i].question);
            free(random_ansi_color);
            return true;
        }
    }
    return false;
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Set valid answer variable
    bool valid_answer; 
    
    // Loop through questions 
    for(int i = 0; i < NUM_QUESTIONS; i++ ){

        if((strcmp(questions[i].category, category) == 0) && questions[i].value == value){
            if((strcmp(questions[i].answer,answer) == 0)){

                    valid_answer = true;
                    questions[i].answered = true;
            }else{
                    valid_answer = false;
                    questions[i].answered = true;
            }
        }
    }

    return valid_answer;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered

    for(int i = 0; i<NUM_QUESTIONS; i++){

        if((strcmp(questions[i].category, category) == 0) && questions[i].value == value){

            if(questions[i].answered){
                return true;
            }

        }

    }
    return false;

}

bool category_exists(char *category) {
    for (int i = 0; i < NUM_CATEGORIES ; i++) {
        if(strcmp(categories[i], category) == 0)
            return true;
    }
    return false;
}

void set_questions_file_path(char * filepath) {
    QUESTIONS_FILE_PATH = malloc(MAX_LEN);
    strcpy(QUESTIONS_FILE_PATH, filepath);
    // free(QUESTIONS_FILE_PATH);
}