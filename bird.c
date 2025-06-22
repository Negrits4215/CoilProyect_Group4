#include <conio.h>
#include "bird.h"
#include "constants.h"

Bird bird;

void handleInput() {
    if (_kbhit()) {
        char c = _getch();
        if (c == ' ') {
            bird.velocity = JUMP_STRENGTH;
        }
    }
}

void updatePhysics() {
    bird.velocity += GRAVITY;

    if (bird.velocity > MAX_FALL_SPEED)
        bird.velocity = MAX_FALL_SPEED;

    bird.y += bird.velocity;

    if (bird.y < 0) {
        bird.y = 0;
        bird.velocity = 0;
    }

    if (bird.y >= SCREEN_HEIGHT - 1) {
        bird.y = SCREEN_HEIGHT - 1;
    }
}
