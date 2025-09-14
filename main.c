/*
 * main(int argc, char const* argv[])
 *   Entry point of the program. Initializes console and podium,
 *   handles the main menu loop (Play, Log, TOP Score, Exit),
 *   runs the gameplay loop with pause handling and animations,
 *   manages lives/score updates, persists scores to history.log,
 *   and renders history and top score views on demand.
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "frontend/display.h"
#include "frontend/mainMenu.h"
#include "frontend/topScore.h"
#include "backend/game.h"
#include "constants.h"

extern int score;

int main(int argc, char const *argv[])
{
    consoleSetup();
    podiumInit();

    int playAgain;
    int gameLoop = 1;
    int exitGame = 1;
    int reset;
    char username[MAX_NAME_LENGHT + 1];

    int arrow;
    int selection;
    char choice;

    getUsername(username, MAX_NAME_LENGHT);
    while (exitGame) {
        playAgain = 1;

        arrow = 0;
        do {
            system("cls");
            selection = menu(arrow);
    
            do {
                arrow = handleInput(3, ARROW_DOWN, ARROW_UP, ' ');
            } while (!arrow);
        } while (arrow != 3);
    
        if (selection == 1) {
            gameInit(1);

            while(lifes && playAgain){
                reset = 0;
                
                system("cls");
        
                draw(score, lifes, 1);

                do {
                    choice = handleInput(1, ' ');
                } while (!choice);
                
                waitForKeyRelease();

                gameLoop = 1;
        
                while (gameLoop) {
                    choice = handleInput(2, ' ', 'p', 'P');

                    if (choice == 2 || choice == 3){
                        arrow = 0;
                        do {
                            system("cls");
                            selection = pauseMenu(arrow);
                    
                            do {
                                arrow = handleInput(3, ARROW_DOWN, ARROW_UP, ' ');
                            } while (!arrow);
                        } while (arrow != 3);
                        if(selection == 2){
                            reset = 1;
                            gameLoop = 0;
                        }
                        else if(selection == 3){
                            gameLoop = 0;
                            playAgain = 0;
                        }
                    }
                    else{
                        updateGame(choice);
                        draw(score, lifes, 0);
                        if (checkCollision()) {
                            lifes--;
                            gameLoop = 0;

                            int i;
                            system("cls");
                            for (i = 0; i < NO_FRAMES; i++){
                                drawFrame(i);
                                Sleep(FRAME_BIRD_MS);
                                system("cls");
                            }
                            
                        }
                        Sleep(FRAME_TIME_MS);
                    }
                }
        
                if (!reset && playAgain){
                    if (!lifes) {
                        system("cls");
                        
                        reset = 1;
    
                        saveScore(username, score);
                        
                        podiumUpdate(username, score);

                        gameOver();
                        
                        printf("\nFinal Score: %d\n", score);
                
                        waitForKeyRelease();
                
                        printf("Press 'r' to play again, 'q' to quit...\n");
                        
                
                        do {
                            choice = handleInput(4, 'q', 'Q', 'r', 'R');
                        } while (!choice);
                
                        if (choice == 1 || choice == 2) {
                            playAgain = 0;
                        }
                    }
                }
                
                
                gameInit(reset);
            }
        }
        else if(selection == 2){
            showHistory();

            do {
                choice = handleInput(1, ' ');
            } while (!choice);
        }
        else if(selection == 3){
            topScoreDraw();

            do {
                choice = handleInput(1, ' ');
            } while (!choice);
        }
        else if(selection == 4) {
            exitGame = 0;
        }
        
    }
    

    
    return 0;
}
