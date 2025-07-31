#ifndef PIPES_H
#define PIPES_H

#include "constants.h"

typedef struct {
    int x;
    int gapY;
    int passed;
} Pipe;

Pipe pipes[NUM_PIPES];

void updatePipes();
int checkCollision();

#endif