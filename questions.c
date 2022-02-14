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

void load_questions(char *path) {
    FILE *fp;
    char buff[MAX_LEN];

    fp = fopen(path, "r");
    if (fp == NULL) { printf("Could not open file %s\n", path); return;  }
    char delim[2];
    delim[0] = '|';
    delim[1] = 0;
    while (fgets(buff, MAX_LEN, (FILE*)fp) != NULL) {
        printf("fgets = %s\n", buff);
        while (strtok(buff, delim) != NULL) {
            char *b = strtok(buff, delim);
            printf("After strtok = %s\n", b);
        }
        
    }
    fclose(fp);
}
int main() {
    load_questions("questions.txt");
}

// Initializes the array of questions for the game
void initialize_game(void)
{
    question *q1 = &questions[0];
    strcpy(q1->category, categories[0]);
    strcpy(q1->question, "What do you call a program that translates Java bytecode into machine language instructions?");
    strcpy(q1->answer, "Interpreter");
    q1->answered = false;
    q1->value = 200;
    
    question *q2 = &questions[0];
    strcpy(q2->category, categories[0]);
    strcpy(q2->question, "Is Java bytecode a high-level language or a low-level language?");
    strcpy(q2->answer, "Low-level language");
    q2->answered = false;
    q2->value = 200;

    question *q3 = &questions[0];
    strcpy(q3->category, categories[0]);
    strcpy(q3->question, "Is Java bytecode a high-level language or a low-level language?");
    strcpy(q3->answer, "Low-level language");
    q3->answered = false;
    q3->value = 200;
    // initialize each question struct and assign it to the questions array
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}