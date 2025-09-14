/*
 * Public Functions (available through mainMenu.h):
 * 
 * getUsername(char* str, int maxLen)
 *   Reads a username from stdin, up to maxLen characters. If the user
 *   exceeds the limit, it clears the extra input and asks again.
 * 
 * menu(int input)
 *   Renders the main menu centered on screen and updates the current
 *   selection based on input (e.g., up/down). Returns the selected option.
 * 
 * pauseMenu(int input)
 *   Renders the pause menu centered on screen and updates the selection
 *   based on input. Returns the selected option.
 * 
 * gameOver()
 *   Prints a centered ASCII "GAME OVER" banner using the GM_* constants
 *   and the global 'sing' frame data.
 * 
 * saveScore(char* username, int score)
 *   Appends a "username: score" line to history.log.
 * 
 * showHistory()
 *   Clears the screen and prints the history.log contents centered. If the
 *   file does not exist, shows a centered fallback message.
 * 
 * drawFrame(int frame)
 *   Draws a single animation frame from 'birdnimation' centered on the
 *   screen. Does nothing if the frame index is out of range.
 * 
 * -------------------------------------------------------------
 * Private Functions (internal use only in this file):
 * 
 * printCenter(const char* str, int strLength) [static]
 *   Prints 'str' centered horizontally according to SCREEN_WIDTH.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mainMenu.h"
#include "../constants.h"

static void printCenter(const char*, int);

void getUsername(char* str, int maxLen) {
    int valid = 0;

    while (!valid) {
        int i = 0;
        char choice;
        int strEnd = 0;

        system("cls");
        printf("Enter your name (max %d characters):\n", maxLen);

        while (i < maxLen && !strEnd) {
            choice = getchar();
            if (choice == '\n' || choice == EOF) {
                strEnd = 1;
            }
            else {
                str[i++] = choice;
            }
        }

        str[i] = '\0'; 

        if (choice != '\n' && choice != EOF) {
            while ((choice = getchar()) != '\n' && choice != EOF) {
                //clear the buffer
            }
            printf("Input too long! Max %d characters. Try again.\n", maxLen);
            system("pause");
        } else {
            valid = 1;
        }
    }
}

int menu(int input) {
    static int selection;
    const char play[] = "Play Game";
    const char log[] = "Log";
    const char top[] = "TOP Score";
    const char ex[] = "Exit Game";
    const int options = 4;

    if (!input){
        selection = 1;
    }
    
    if (selection != 1 && input == 1) {
        selection--;
    }
    else if(selection != options && input == 2) {
        selection++;
    }
    
    printCenter(play, (sizeof(play)));
    printf("%s", (selection == 1)? " <-\n":"\n");
    
    printCenter(log, (sizeof(log)));
    printf("%s", (selection == 2)? " <-\n":"\n");

    printCenter(top, (sizeof(top)));
    printf("%s", (selection == 3)? " <-\n":"\n");
    
    printCenter(ex, (sizeof(ex)));
    printf("%s", (selection == 4)? " <-\n":"\n");

    return selection;
}

int pauseMenu(int input) {
    static int selection;
    const char resm[] = "Resume";
    const char rest[] = "Restart";
    const char ex[] = "Exit";

    if (!input){
        selection = 1;
    }

    if (selection != 1 && input == 1) {
        selection--;
    }
    else if(selection != 3 && input == 2) {
        selection++;
    }
    printCenter(resm, (sizeof(resm)));
    printf("%s", (selection == 1)? " <-\n":"\n");

    printCenter(rest, (sizeof(rest)));
    printf("%s", (selection == 2)? " <-\n":"\n");

    printCenter(ex,sizeof(ex));
    printf("%s", (selection == 3)? " <-\n":"\n");

    return selection;
}

void gameOver() {
    int singLenght = GM_WIDTH;
    int espacios = (((SCREEN_WIDTH - singLenght) / 2) > 0)? ((SCREEN_WIDTH - singLenght) / 2) : 0;
    int i, s;

    for (i = 0; i < GM_HEIGHT; i++) {
        for (s = 0; s < espacios; s++) {
            putchar(' ');
        }
        printf("%s\n", sing[i]);
    }
}


void saveScore(char* username, int score) {
    FILE* file = fopen("history.log", "a");
    if (file) {
        fprintf(file, "%s: %d\n", username, score);
        fclose(file);
    }
}

void showHistory() {
    FILE* file = fopen("history.log", "r");
    char line[100];

    const char hLog[] = "--- History Log ---\n";
    const char end[] = "-------------------\n";
    const char noEnt[] = "No history entries found.";
    const char ex[] = "Press SPACE to exit";

    system("cls");

    if (file) {
        printCenter(hLog, sizeof(hLog));
        while (fgets(line, sizeof(line), file)) {
            printCenter(line, (sizeof(hLog) + 2)); //same space as the top print plus a space
        }
        fclose(file);
        printCenter(end, sizeof(end));
        printCenter(ex, sizeof(ex));
    } else {
        printCenter(noEnt, sizeof(hLog));
    }
}

void drawFrame(int frame) {
    int totalFrames = NO_FRAMES;

    if (frame >= totalFrames){
        return;
    } 

    int start = frame * FRAME_HEIGHT;
    int topOffset = (SCREEN_HEIGHT - FRAME_HEIGHT) / 2;

    for (int i = 0; i < topOffset; i++){
        putchar('\n');
    }
    
    int lineLen = FRAME_WIDTH; 
    int leftOffset = ((SCREEN_WIDTH - lineLen) / 2) < 0?(SCREEN_WIDTH - lineLen) / 2:0;

    for (int i = 0; i < FRAME_HEIGHT; i++) {
        for (int j = 0; j < leftOffset; j++){
            putchar(' ');
        }

        printf("%s\n", birdnimation[start + i]);
    }
}




//Private functions
static void printCenter(const char* str, int strLenth){
    int spaces = ((SCREEN_WIDTH - strLenth)/2 > 0 )?(SCREEN_WIDTH - strLenth)/2 : 0;
    int i;
    for (i = 0; i < spaces; i++){
        putchar(' ');
    }
    printf("%s", str);
}