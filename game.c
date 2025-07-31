#include <stdio.h>
#include "constants.h"
#include "bird.h"
#include "game.h"
#include "pipes.h"

extern score;

void initGame() {
    bird.x = SCREEN_WIDTH / 4;
    bird.y = SCREEN_HEIGHT / 2;
    bird.velocity = 0;

    srand((unsigned)time(NULL));
    for (int i = 0; i < NUM_PIPES; i++) {
        pipes[i].x = SCREEN_WIDTH + i * PIPE_DISTANCE;
        pipes[i].gapY = rand() % (SCREEN_HEIGHT - PIPE_GAP - 2) + 1;
        pipes[i].passed = 0;
    }

    score = 0;
}



void logScore() {
    FILE *f = fopen("score.log", "a");
    if (f) {
        fprintf(f, "Score: %d\tTime: %ld\n", score, time(NULL));
        fclose(f);
    }
}