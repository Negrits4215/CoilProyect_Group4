#ifndef TOPSCORE_H
#define TOPSCORE_H

#include "../constants.h"

typedef struct {
    char name[MAX_NAME_LENGHT + 1];
    int score;
} TopPlayer;

void podiumInit();
void podiumUpdate(char*, int);
void topScoreDraw();

#endif