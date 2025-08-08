#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "frontend/display.h"
#include "frontend/mainMenu.h"
#include "backend/game.h"
#include "constants.h"

extern int score;

int main(int argc, char const *argv[])
{
    int playAgain = 1;
    int gameLoop = 1;
    char* username;

    int arrow;

    username = getUsername();

    //ARREGLAR MAÑANA, NO FUNCIONA EL ESPACIO PARA SEGUIR
    do {
        arrow = handleInput(2, 72, 80, ' ');
        menu(arrow);

        system("cls");
    } while (arrow != 3);

    free(username);

    gameInit(1);

    while(lifes && playAgain){

        system("cls");
        gameLoop = 1;

        while (gameLoop) {
            updateGame(handleInput(1, ' '));
            draw(score, lifes);
            if (checkCollision()) {
                lifes--;
                gameLoop = 0;
            }
            Sleep(FRAME_TIME_MS);
        }

        printf("\nGame Over! Final Score: %d\n", score);

        waitForKeyRelease();

        printf("Press 'r' to play again, 'q' to quit...\n");

        char choice = 0;
        

        do {
            choice = handleInput(4, 'q', 'Q', 'r', 'R');
        } while (!choice);

        if (choice == 1 || choice == 2) {
            playAgain = 0;
        }

        gameInit(0);
    }

    
    return 0;
}
