/*
 * Public Functions (available through pipes.h):
 * 
 * pipesInit() 
 *   Initializes the pipe array. Generates NUM_PIPES pipes 
 *   with increasing horizontal offsets.
 * 
 * updatePipes() 
 *   Updates the position of each pipe by moving it to the left. 
 *   When a pipe goes off-screen, it is regenerated at the right 
 *   side with a new random gap position.
 * 
 * -------------------------------------------------------------
 * Private Functions (internal use only in this file):
 * 
 * genPipe() [static] 
 *   Creates and returns a new Pipe object. Assigns its horizontal 
 *   position based on the offset, sets a random vertical gap, 
 *   and marks it as not yet passed.
 */

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