#include "bird.h"
#include "../constants.h"

Bird bird;

void birdInit(){
    bird.x = SCREEN_WIDTH / 4;
    bird.y = SCREEN_HEIGHT / 2;
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