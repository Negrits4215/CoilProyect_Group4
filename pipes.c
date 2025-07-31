#include "bird.h"
#include "pipes.h"
#include "constants.h"

void updatePipes() {
    for (int i = 0; i < NUM_PIPES; i++) {
        pipes[i].x--;

        if (pipes[i].x < -1) {
            pipes[i].x = SCREEN_WIDTH + PIPE_DISTANCE;
            pipes[i].gapY = rand() % (SCREEN_HEIGHT - PIPE_GAP - 2) + 1;
            pipes[i].passed = 0;
        }

        if (!pipes[i].passed && pipes[i].x + 1 < bird.x) {
            //score++;      THIS NEEDS TO BE CHANGED WHEN THE GAME MODULE IS CREATED
            pipes[i].passed = 1;
        }
    }
}

int checkCollision() {
    int birdY = (int)bird.y;

    if (birdY < 1 || birdY > SCREEN_HEIGHT - 2)
        return 1;

    for (int i = 0; i < NUM_PIPES; i++) {
        if (pipes[i].x <= bird.x && pipes[i].x + 1 >= bird.x) {
            if (birdY < pipes[i].gapY || birdY > pipes[i].gapY + PIPE_GAP)
                return 1;
        }
    }

    return 0;
}