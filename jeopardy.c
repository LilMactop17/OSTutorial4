#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here
int questions_left = 12;
// toeknize user input
void tokenize(char *input, char **tokens) 
{
    // who or what
    tokens[0] = strtok(input, " ");
    
    // getting is
    tokens[1] = strtok(NULL, " ");
    
    // getting answer
    char *remaining = strtok(NULL, "");
    
    // clean leading space
    if (remaining != NULL && remaining[0] == ' ') {
        remaining++;
    }
    tokens[2] = remaining;
}

// shows all the score sof eah player
void show_results(player *players, int num_players) {
    for (int i = 0; i<num_players; i++) {
        printf("%s scored %d points.", players[i].name, players[i].score);
    }
}


int main(int argc, char *argv[])
{
    player players[NUM_PLAYERS];
    char buffer[BUFFER_LEN] = { 0 };
    int questions_left = NUM_QUESTIONS;

    initialize_game();

    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %d, choose a name: ", i+1);
        scanf("%s", players[i].name);
        players[i].score = 0;
    }
    
    getchar(); 

    int player = 0;

    while (questions_left > 0)
    {
        display_categories();

        char category_chosen[50];
        int value;
        bool valid_choice = false;
        question *selected_question = NULL;

        while (!valid_choice) {
            printf("\n%s's turn. Choose a category: ", players[player].name);
            scanf("%s", category_chosen);
            printf("Choose a Value: ");
            scanf("%d", &value);
            getchar(); 

            selected_question = already_answered(category_chosen, value);

            if (selected_question != NULL && !selected_question->answered) {
                valid_choice = true;
            }
            else {
                printf("Invalid choice or already answered.\n");
            }
        }

        display_question(selected_question->category, selected_question->value);

        printf("Your answer (Must start with 'what is' or 'who is'): ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = 0; 

        char *tokens[3] = {NULL};

        tokenize(buffer, tokens);
        if (valid_answer(tokens, selected_question->answer)) {
            printf("CORRECT!\n");
            update_score(selected_question->value, &players[player]);
            selected_question->answered = true;
            questions_left--;
        } else {
            printf("Wrong! The correct answer was: %s\n", selected_question->answer);
        }
        player = (player + 1) % NUM_PLAYERS; 
    }

    show_results(players, NUM_PLAYERS);

    return EXIT_SUCCESS;
}
