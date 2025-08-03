#include "pipes.h"
#include "../constants.h"
#include <stdlib.h>
#include <time.h>

Pipe pipes[NUM_PIPES];

static Pipe genPipe(int);

void pipesInit(){
    for (int i = 0; i < NUM_PIPES; i++) {
        pipes[i] = genPipe(i);
    }
}

void updatePipes() {
    for (int i = 0; i < NUM_PIPES; i++) {
        pipes[i].x--;

        if (pipes[i].x < -1) {
            pipes[i] = genPipe(1);
        }
    }
}



static Pipe genPipe(int offSet) {
    Pipe newPipe;

    srand((unsigned)time(NULL));
    newPipe.x = SCREEN_WIDTH + offSet * PIPE_DISTANCE;
    newPipe.gapY = rand() % (SCREEN_HEIGHT - PIPE_GAP - 2) + 1;
    newPipe.passed = 0;

    return newPipe;
}