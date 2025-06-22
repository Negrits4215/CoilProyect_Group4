#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "constants.h"
#include "bird.h"
#include "display.h"

typedef struct {
    int x;
    int gapY;
    int passed;
} Pipe;

Pipe pipes[NUM_PIPES];
int score = 0;

void initGame();
void updatePipes();
int checkCollision();
void logScore();
void waitForKeyRelease();

int main() {
    int playAgain = 1;

    while (playAgain) {
        initGame();

        while (1) {
            handleInput();
            updatePhysics();
            updatePipes();
            draw(score);
            if (checkCollision()) break;
            Sleep(FRAME_TIME_MS);
        }

        printf("\nGame Over! Final Score: %d\n", score);
        logScore();

        waitForKeyRelease();

        printf("Press 'r' to play again, 'q' to quit...\n");

        char choice;
        do {
            choice = _getch();
        } while (choice != 'r' && choice != 'R' && choice != 'q' && choice != 'Q');

        if (choice == 'q' || choice == 'Q') {
            playAgain = 0;
        } else {
            clearScreen();
        }
    }

    return 0;
}

void initGame() {
    bird.x = SCREEN_WIDTH / 4;
    bird.y = SCREEN_HEIGHT / 2;
    bird.velocity = 0;

    srand((unsigned)time(NULL));
    for (int i = 0; i < NUM_PIPES; i++) {
        pipes[i].x = SCREEN_WIDTH + i * PIPE_DISTANCE;
        pipes[i].gapY = rand() % (SCREEN_HEIGHT - PIPE_GAP - 2) + 1;
        pipes[i].passed = 0;
    }

    score = 0;
}

void updatePipes() {
    for (int i = 0; i < NUM_PIPES; i++) {
        pipes[i].x--;

        if (pipes[i].x < -1) {
            pipes[i].x = SCREEN_WIDTH + PIPE_DISTANCE;
            pipes[i].gapY = rand() % (SCREEN_HEIGHT - PIPE_GAP - 2) + 1;
            pipes[i].passed = 0;
        }

        if (!pipes[i].passed && pipes[i].x + 1 < bird.x) {
            score++;
            pipes[i].passed = 1;
        }
    }
}

int checkCollision() {
    int birdY = (int)bird.y;

    if (birdY < 1 || birdY > SCREEN_HEIGHT - 2)
        return 1;

    for (int i = 0; i < NUM_PIPES; i++) {
        if (pipes[i].x <= bird.x && pipes[i].x + 1 >= bird.x) {
            if (birdY < pipes[i].gapY || birdY > pipes[i].gapY + PIPE_GAP)
                return 1;
        }
    }

    return 0;
}

void logScore() {
    FILE *f = fopen("score.log", "a");
    if (f) {
        fprintf(f, "Score: %d\tTime: %ld\n", score, time(NULL));
        fclose(f);
    }
}

void waitForKeyRelease() {
    while (_kbhit()) {
        _getch();
    }
    while (_kbhit()) {
        Sleep(10);
    }
}
