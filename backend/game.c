/*
 * Public Functions (available through game.h):
 * 
 * gameInit() 
 *   Initializes the game state. Calls birdInit() and pipesInit(). 
 *   If reset is true, resets score to 0 and lifes to 3.
 * 
 * updateGame() 
 *   Updates the physics of the bird and the position of the pipes. 
 *   If the given state indicates an action (state == 1), makes 
 *   the bird jump.
 * 
 * checkCollision() 
 *   Checks if the bird collides with the ground, the ceiling, or 
 *   any pipe. Returns 1 if a collision is detected. Also increases 
 *   the score when the bird successfully passes a pipe.
 * 
 * -------------------------------------------------------------
 * Private Functions:
 *   (none in this file — all functions here are public)
 */

#include "bird.h"
#include "pipes.h"
#include "game.h"

int score;
int lifes;

void gameInit(int reset){
    birdInit();
    pipesInit();

    if (reset) {
        score = 0;
        lifes = 3;
    }
    
}

void updateGame(int state){
    updatePhysics();
    updatePipes();

    if (state == 1){
        birdJump();
    }
    
}

int checkCollision() {
    int birdY = (int)bird.y;

    if (birdY < 1 || birdY > SCREEN_HEIGHT - 2){
        return 1;
    }
    for (int i = 0; i < NUM_PIPES; i++) {
        if (pipes[i].x <= bird.x && pipes[i].x + 1 >= bird.x) {
            if (birdY < pipes[i].gapY || birdY > pipes[i].gapY + PIPE_GAP) {
                return 1;
            }
        }
        if (!pipes[i].passed && pipes[i].x + 1 < bird.x) {
            score++;
            pipes[i].passed = 1;
        }
    }

    return 0;
}


