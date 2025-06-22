#ifndef BIRD_H
#define BIRD_H

typedef struct {
    int x;
    float y;
    float velocity;
} Bird;

extern Bird bird;

void handleInput();
void updatePhysics();

#endif
