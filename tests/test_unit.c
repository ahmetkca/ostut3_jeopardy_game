#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include "acutest.h"
#include "../players.h"
#include "../questions.h"
// #include "../jeopardy.h"


/* --------------- players.c test cases -------------- */

void test_player_exists(void) {
    //TODO: use player_exists function from players.c and test if the given array of players contains the given name
    int NUM_PLAYERS = 1;
    player players[NUM_PLAYERS];
    player *p1 = &players[0];
    strcpy(p1->name, "player 1");
    p1->score = 99;
    char players_str[256];
    char *check_name = "player 1";
    TEST_CHECK_(
        player_exists(players, NUM_PLAYERS, check_name) == true, 
        "players array SHOULD contain player with name \"%s\"", check_name);
    TEST_CHECK_(
        player_exists(players, NUM_PLAYERS, "player 2") == false, 
        "players array should NOT contain player with name \"%s\"", "player 2");
    TEST_MSG("players array: \n");
    for (int i = 0;i < NUM_PLAYERS; i++) {
        TEST_MSG("\tp%d = { .name=\"%s\", .score=%d }", i+1, players[i].name, players[i].score);
    }
}

void test_update_score(void) {
    //TODO: use update_score function from players.c and test if it updates player's score
    int NUM_PLAYERS = 1;
    player players[NUM_PLAYERS];
    player *p1 = &players[0];
    char *check_name = "player 1";
    strcpy(p1->name, check_name);
    p1->score = 55;
    update_score(players, NUM_PLAYERS, check_name, 44);
    TEST_CHECK_(
        players[0].score == (55 + 44), "(players[0].score = %d) is equals to %d", 
        players[0].score, (55 + 44));
    TEST_MSG("After update_score players array: \n");
    for (int i = 0;i < NUM_PLAYERS; i++) {
        TEST_MSG("\tp%d = { .name=\"%s\", .score=%d }", i+1, players[i].name, players[i].score);
    }
}

/* --------------------------------------------------- */


/* -------------  questions.c test cases ------------- */

void test_initialize_game(void) {
    //TODO test if the initialize_game function properly reads from questions.txt and setupthe array of questions
    set_questions_file_path("../questions.txt");
    initialize_game();
    TEST_CHECK_(strcmp(questions[8].category, "databases") == 0, "(questions[8].category = %s) is equals to \"%s\"", questions[8].category, "databases");
    TEST_MSG("Expected: %s", "databases");
    TEST_MSG("Produced: %s", questions[8].category);
    TEST_CHECK_(strcmp(questions[8].answer, "query") == 0, "(questions[8].answer = %s) is equals to \"%s\"", questions[8].answer, "query");
    TEST_MSG("Expected: %s", "query");
    TEST_MSG("Produced: %s", questions[8].answer);
    TEST_CHECK(strcmp(questions[8].question, "A database object which enables you to locate multiple records matching specified criteria.") == 0);
    TEST_MSG("Expected: %s", "A database object which enables you to locate multiple records matching specified criteria.");
    TEST_MSG("Produced: %s", questions[8].question);
    TEST_CHECK_(questions[8].value == 200, "(questions[8].value = %d) is equals to %d", questions[8].value, 200);
    TEST_MSG("Expected: %d", 200);
    TEST_MSG("Produced: %d", questions[8].value);
}

void test_display_question(void) {
    //TODO test display question function by capturing stdout and comparing it with the given parameters
    set_questions_file_path("../questions.txt");
    initialize_game();
    char * category = "databases";
    int value = 200;
    // char bufbuf[MAX_LEN];
    freopen("/dev/null", "w", stdout);
    // setbuf(stdout, bufbuf);
    bool first_test = display_question(category, value);
    freopen ("/dev/tty", "w", stdout);
    // printf("%s\n", bufbuf);
    // printf("%c\n", bufbuf[10]);
    TEST_CHECK_( first_test == true, "display_question(\"%s\", \"%d\") -> %d should return TRUE.",category, value, display_question(category, value));
    question *q = &questions[0];
    q->answered = true;
    category = "programming";
    TEST_CHECK_(display_question(category, value) == false, "display_question(\"%s\", \"%d\") -> %d should return FALSE.",category, value, display_question(category, value));
    TEST_MSG("EXPECTED: display_question(\"%s\", \"%d\") -> %d",category, value, false);
    TEST_MSG("PRODUCED: display_question(\"%s\", \"%d\") -> %d",category, value, display_question(category, value));
    TEST_CHECK(display_question("test category", 555) == false);
    TEST_MSG("EXPECTED: display_question(\"%s\", \"%d\") -> %d","test category", 555, false);
    TEST_MSG("PRODUCED: display_question(\"%s\", \"%d\") -> %d","test category", 555, display_question("test category", 555));
}

void test_valid_answer(void) {
    set_questions_file_path("../questions.txt");
    initialize_game();
    char category[MAX_LEN] = "databases";
    int value = 200;
    char answer[MAX_LEN] = "query";
    TEST_CHECK(valid_answer(category, value, answer) == true);
    TEST_CHECK(valid_answer(category, value, "incorrect answer") == false);

}

void test_already_answered(void) {
    set_questions_file_path("../questions.txt");
    initialize_game();
    question *q = &questions[2];
    q->answered = true;
    char *category= "programming";
    int value = 600;
    printf("questions[2]:\n");
    printf("\tquestion = %s\n", q->question);
    printf("\tanswer = %s\n", q->answer);
    printf("\tcategory = %s\n", q->category);
    printf("\tvalue = %d\n", q->value);
    printf("\tanswered = %d\n", q->answered);
    TEST_CHECK_(
        already_answered(category, value) == true,
        "questions[2].answered = %d, bool already_answered(\"%s\", \"%d\") -> %d", q->answered, category, value, already_answered(category, value));
    category = "databases";
    value = 200;
    printf("questions[8]:\n");
    printf("\tquestion = %s\n", questions[8].question);
    printf("\tanswer = %s\n", questions[8].answer);
    printf("\tcategory = %s\n", questions[8].category);
    printf("\tvalue = %d\n", questions[8].value);
    printf("\tanswered = %d\n", questions[8].answered);
    TEST_CHECK_(
        already_answered(category, value) == false,
        "questions[8].answered = %d, bool already_answered(\"%s\", \"%d\") -> %d", questions[8].answered, category, value, already_answered(category, value));
}

/* --------------------------------------------------- */

/* --------------- jeopardy.c test cases ------------- */

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

void test_tokenize(void) {
    char tokens[3][MAX_LEN];
    char input[MAX_LEN] = "what is merge sort";
    tokenize(input, tokens);
    TEST_CHECK(strcmp(tokens[0], "what") == 0);
    TEST_MSG("Expected: \"%s\"", "what");
    TEST_MSG("Produced: \"%s\"", tokens[0]);
    TEST_CHECK(strcmp(tokens[1], "is") == 0);
    TEST_MSG("Expected: \"%s\"", "is");
    TEST_MSG("Produced: \"%s\"", tokens[1]);
    TEST_CHECK(strcmp(tokens[2], "merge sort") == 0);
    TEST_MSG("Expected: \"%s\"", "merge sort");
    TEST_MSG("Produced: \"%s\"", tokens[2]);

    char input2[MAX_LEN] = "who is masoud";
    tokenize(input2, tokens);
    TEST_CHECK(strcmp(tokens[0], "who") == 0);
    TEST_CHECK(strcmp(tokens[1], "is") == 0);
    TEST_CHECK(strcmp(tokens[2], "masoud") == 0);
}

/* --------------------------------------------------- */


TEST_LIST = {
    {"players.c | bool player_exists(player *players, int num_players, char *name)", test_player_exists},
    {"players.c | void update_score(player *players, int num_players, char *name, int score)", test_update_score},
    {"questions.c | void initialize_game(void) calls load_questions(void)", test_initialize_game},
    {"jeopardy.c | void tokenize(char *input, char **tokens)", test_tokenize},
    {"questions.c | bool display_question(char *category, int value)", test_display_question},
    {"questions.c | bool valid_answer(char *category, int value, char *answer)", test_valid_answer},
    {"questions.c | bool already_answered(char *category, int value)", test_already_answered},
    { NULL, NULL }     /* zeroed record marking the end of the list */
};
