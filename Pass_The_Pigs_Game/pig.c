#include "names.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // set the amount of players for the game
    printf("How many players? ");
    int players = 0;
    scanf("%d", &players);
    if (players < 2 || players > 10) {
        fprintf(stderr, "Invalid number of players, Using 2 instead.\n");
        players = 2;
    }

    // set the random seed for the game
    printf("Random seed: ");
    int seed = 0;
    scanf("%d", &seed);
    // if statement doesn't need max since int cannot be greater than 2^31-1
    if (seed < 0) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed = 2021;
    }
    srandom(seed);

    // defining possible rolls and assinging values to those rolls
    typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
    const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };
    // creating array filled with 0 for participating player scores
    int player_tot[players - 1];
    for (int i = 0; i < players; i++) {
        player_tot[i] = 0;
    }
    // loop for playing the game and getting rolls
    int cur_player = 0;
    int prev_player = -1;
    while (true) {
        // check to see if player fufills win condition
        if (player_tot[cur_player % players] >= 100) {
            int win_num = player_tot[cur_player % players];
            printf("\n");
            fprintf(stdout, "%s wins with %d points!\n", names[cur_player % players], win_num);
            break;
        }
        // check if next players turn
        if (cur_player != prev_player) {
            printf("%s %s", names[cur_player % players], "rolls the pig...");
            prev_player = cur_player;
        }
        printf(" ");

        // switch cases for determining rolls and points
        switch (pig[random() % 7]) {
        case 0:
            printf("pig lands on side\n");
            cur_player++;
            break;
        case 1:
            printf("pig lands on back");
            player_tot[cur_player % players] += 10;
            break;
        case 2:
            printf("pig lands upright");
            player_tot[cur_player % players] += 10;
            break;
        case 3:
            printf("pig lands on snout");
            player_tot[cur_player % players] += 15;
            break;
        case 4:
            printf("pig lands on ear");
            player_tot[cur_player % players] += 5;
            break;
        }
    }
    return 0;
}
