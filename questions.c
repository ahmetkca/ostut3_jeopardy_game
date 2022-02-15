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
        // printf("fgets = %s\n", buff);
        char *token = strtok(buff, delim);
        int y = 0;
        char *tokens[4];
        while (token != NULL) {
            tokens[y] = token;
            // printf("After strtok = %s\n", token);
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
    // int cate_inde[NUM_CATEGORIES];
    // char table[NUM_QUESTIONS/NUM_CATEGORIES][NUM_CATEGORIES];
    // for (int i =0 ; i < NUM_CATEGORIES; i++) {
    //     table[0][i] = categories[i];
    // }
    // print categories and dollar values for each unanswered question in questions array
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered) {
            printf("%s %d\n", questions[i].category, questions[i].value);
        } 
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    for(int i = 0; i < NUM_QUESTIONS; i++){
        if((questions[i].category == category) && (questions[i].value == value)){
            printf("For %d %s", questions[i].value,questions[i].question);
        }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Set valid answer variable
    bool valid_answer; 
    
    // Loop through questions 
    for(int i = 0; i < NUM_QUESTIONS; i++ ){

        if((questions[i].category == category) && (questions[i].value == value)){
            if((strcmp(questions[i].answer,answer) == 0)){

                    valid_answer = true;

            }else{
                    valid_answer = false;
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

        if(questions[i].category==category && questions[i].value == value){

            if(questions[i].answered){
                return true;
            }

        }

    }
    return false;
    
}