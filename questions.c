/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U: Operating Systems
 *
 * Copyright (C) 2026, <GROUP NUMBER>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "questions.h"


question questions[NUM_QUESTIONS];
// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    for (int i = 0; i<NUM_QUESTIONS; i++) {
        strcpy(questions[i].category, categories[i/4]);
        strcpy(questions[i].question, questions_strings[i]);
        strcpy(questions[i].answer, answers[i]);
        questions[i].value = (250 * ((i%4)+1));
        questions[i].answered = false;
    }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    for (int i = 0; i<NUM_CATEGORIES; i++) {
        printf("%s\n", categories[i]);
        for (int j = 0; j<NUM_QUESTIONS; j++) {
            if (strcmp(questions[j].category, categories[i]) == 0 && !questions[j].answered) {
                printf("%d\n", questions[j].value);
            }
        }
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    for (int i = 0; i<NUM_QUESTIONS; i++) {
        if (strcasecmp(questions[i].category, category) == 0 && questions[i].value == value) {
            if (!questions[i].answered) {
                printf("Question: %s\n", questions[i].question);
            }
            else {
                printf("Question has already been answered");
            }
        }
    }
}


// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char **tokens, char *correct_answer) 
{
    if (tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL) {
        return false;
    }

    // Requirement 7: Check for "what/who" AND "is"
    bool has_prefix = (strcasecmp(tokens[0], "what") == 0 || strcasecmp(tokens[0], "who") == 0) &&
                      (strcasecmp(tokens[1], "is") == 0);

    if (!has_prefix) {
        printf("FORMAT ERROR: Answer must start with 'What is' or 'Who is'.\n");
        return false;
    }

    return (strcasecmp(tokens[2], correct_answer) == 0);
}

// Returns true if the question has already been answered
question* already_answered(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcasecmp(questions[i].category, category) == 0 && questions[i].value == value) {
            if (!questions[i].answered) {
                return &questions[i];
            }
            return NULL;
        }
    }
    return NULL;
}
