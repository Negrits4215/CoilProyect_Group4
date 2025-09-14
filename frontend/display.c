/*
 * Public Functions (available through display.h):
 * 
 * clearScreen() 
 *   Clears the console by resetting the cursor position to the top-left corner.
 * 
 * draw(int score, int lifes, int preView)
 *   Renders the current game state to the console: pipes, bird, a separator line,
 *   and the HUD (Lifes and Score). Always shows "Press SPACE to flap!".
 *   If preView is 0 (false), also shows "Press P to pause"; if non-zero, omits the pause hint.
 * 
 * handleInput() 
 *   Handles keyboard input. Accepts a variable number of characters 
 *   to check for, and returns the index (1-based) of the matching key. 
 *   Returns 0 if no match is found.
 * 
 * waitForKeyRelease() 
 *   Waits until all pressed keys are released before continuing. 
 *   Useful to avoid unintentional repeated input.
 * 
 * consoleSetup() 
 *   Configures the console for the game. Hides the blinking cursor 
 *   and enables UTF-8 encoding to display special characters.
 * 
 * -------------------------------------------------------------
 * Private Functions:
 *   (none in this file — all functions here are public)
 */

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdarg.h>
#include "display.h"
#include "../backend/bird.h"
#include "../backend/pipes.h"
#include "../constants.h"

void clearScreen() {
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, topLeft);
}

void draw(int score, int lifes, int preView) {
    int y;
    int x;
    int i;

    clearScreen();

    char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
    for (y = 0; y < SCREEN_HEIGHT; y++) {
        for (x = 0; x < SCREEN_WIDTH; x++) {
            screen[y][x] = ' ';
        }
    }
    for (i = 0; i < NUM_PIPES; i++) {
        if (pipes[i].x >= 0 && pipes[i].x < SCREEN_WIDTH) {
            for (y = 0; y < SCREEN_HEIGHT; y++) {
                if (y < pipes[i].gapY || y > pipes[i].gapY + PIPE_GAP) {
                    screen[y][pipes[i].x] = '|';
                }
            }
        }
    }

    int birdY = (int)bird.y;
    if (birdY >= 0 && birdY < SCREEN_HEIGHT){
        screen[birdY][bird.x] = 'O';
    }
    for (y = 0; y < SCREEN_HEIGHT; y++) {
        for (x = 0; x < SCREEN_WIDTH; x++) {
            putchar(screen[y][x]);
        }
        putchar('\n');
    }
    for(x = 0; x < SCREEN_WIDTH; x++) {
        putchar('-');
    }
    putchar('\n');

    printf("Lifes: %d\n", lifes);
    printf("Score: %d\n", score);
    printf("Press SPACE to flap!\n");
    if (!preView){
        printf("Press P to pause");
    }
    
}

int handleInput(int noParams, ...) {
    va_list charsList;
    va_start(charsList, noParams);
    
    if (_kbhit()) {
        int i;

        char c = _getch();
        for (i = 0; i < noParams; i++) {
            if (c == va_arg(charsList, int)) {
                va_end(charsList);
                return (i + 1);
            }
        }
    }
    va_end(charsList);
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

void consoleSetup() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = FALSE;                // hide cursor
    SetConsoleCursorInfo(consoleHandle, &info);
    SetConsoleOutputCP(CP_UTF8);          // enable grafic characters
    SetConsoleCP(CP_UTF8);
}
