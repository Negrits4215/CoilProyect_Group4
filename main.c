#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "constants.h"
#include "bird.h"
#include "display.h"
#include "pipes.h"
#include "game.h"

extern Pipe pipes[];
extern int score;

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

void waitForKeyRelease() {
    while (_kbhit()) {
        _getch();
    }
    while (_kbhit()) {
        Sleep(10);
    }
}
