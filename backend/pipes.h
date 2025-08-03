#ifndef PIPES_H
#define PIPES_H

#include "../constants.h"

typedef struct {
    int x;
    int gapY;
    int passed;
} Pipe;

extern Pipe pipes[];

void pipesInit();
void updatePipes();

#endif