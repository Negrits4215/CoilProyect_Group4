#include <windows.h>
#include <stdio.h>
#include "frontend/display.h"
#include "backend/game.h"
#include "constants.h"

extern int score;

int main(int argc, char const *argv[])
{
    int playAgain = 1;

    while(playAgain){

        system("cls");
        gameInit();


        while (1) {
            updateGame(handleInput(1, ' '));
            draw(score);
            if (checkCollision()) break;
            Sleep(FRAME_TIME_MS);
        }

        printf("\nGame Over! Final Score: %d\n", score);
        //logScore(); hacer el log

        waitForKeyRelease();

        printf("Press 'r' to play again, 'q' to quit...\n");

        char choice = 0;
        

        do {
            choice = handleInput(4, 'q', 'Q', 'r', 'R');
        } while (!choice);

        if (choice == 1 || choice == 2) {
            playAgain = 0;
        }
    }
    return 0;
}
