/*
 * Public Functions (available through bird.h):
 * 
 * birdInit() 
 *   Initializes the bird's position and velocity. Places the bird 
 *   at 1/4 of the screen width and a random vertical position.
 * 
 * updatePhysics() 
 *   Updates the bird's physics on each frame. Applies gravity, 
 *   limits maximum falling speed, and ensures the bird stays 
 *   within the screen boundaries.
 * 
 * birdJump() 
 *   Makes the bird "jump" by setting its velocity to the 
 *   predefined jump strength.
 * 
 * -------------------------------------------------------------
 * Private Functions (internal use only in this file):
 * 
 * randStart() [static] 
 *   Generates a random starting vertical position for the bird, 
 *   constrained between 1/4 of the screen height and 
 *   (screen height - 1/4).
 */

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