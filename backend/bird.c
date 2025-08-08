#include <stdlib.h>
#include <time.h>
#include "bird.h"
#include "../constants.h"

Bird bird;

static int randStart();

void birdInit() {
    bird.x = SCREEN_WIDTH / 4;
    bird.y = randStart();
    bird.velocity = 0;
}

void updatePhysics() {
    bird.velocity += GRAVITY;

    if (bird.velocity > MAX_FALL_SPEED) {
        bird.velocity = MAX_FALL_SPEED;
    }
    bird.y += bird.velocity;

    if (bird.y < 0) {
        bird.y = 0;
        bird.velocity = 0;
    }

    if (bird.y >= SCREEN_HEIGHT - 1) {
        bird.y = SCREEN_HEIGHT - 1;
    }
}

void birdJump() {
    bird.velocity = JUMP_STRENGTH;    
}

static int randStart() {
    srand(time(NULL));

    int min = SCREEN_HEIGHT / 4;
    int max = SCREEN_HEIGHT - min;

    int ret = rand() % (max - min) + (1 + min);
    return (ret);
}