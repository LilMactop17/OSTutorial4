#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "questions.h"


question questions[NUM_QUESTIONS];
void initialize_game(void)
{
    // initialize all the questions
    for (int i = 0; i<NUM_QUESTIONS; i++) {
        strcpy(questions[i].category, categories[i/4]);
        strcpy(questions[i].question, questions_strings[i]);
        strcpy(questions[i].answer, answers[i]);
        questions[i].value = (250 * ((i%4)+1));
        questions[i].answered = false;
    }
}

// Display remaining categories
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


// Returns true if the answer is correct 
bool valid_answer(char **tokens, char *correct_answer) 
{
    // Check if user provided enough words
    if (tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL) {
        return false;
    }

    // checking fro who is or what is
    bool has_prefix = (strcasecmp(tokens[0], "what") == 0 || strcasecmp(tokens[0], "who") == 0) &&
                      (strcasecmp(tokens[1], "is") == 0);

    if (!has_prefix) {
        printf("FORMAT ERROR: Answer must start with 'What is' or 'Who is'.\n");
        return false;
    }

    // Compare the user answet to db answer
    return (strcasecmp(tokens[2], correct_answer) == 0);
}

// returns true if the question already answered
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
