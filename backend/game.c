#include "bird.h"
#include "pipes.h"

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


