#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdarg.h>
#include "../backend/bird.h"
#include "../backend/pipes.h"
#include "../constants.h"

extern Pipe pipes[];

void clearScreen() {
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, topLeft);
}

void draw(int score) {
    clearScreen();

    char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            screen[y][x] = ' ';
        }
    }
    for (int i = 0; i < NUM_PIPES; i++) {
        if (pipes[i].x >= 0 && pipes[i].x < SCREEN_WIDTH) {
            for (int y = 0; y < SCREEN_HEIGHT; y++) {
                if (y < pipes[i].gapY || y > pipes[i].gapY + PIPE_GAP)
                    screen[y][pipes[i].x] = '|';
            }
        }
    }

    int birdY = (int)bird.y;
    if (birdY >= 0 && birdY < SCREEN_HEIGHT)
        screen[birdY][bird.x] = 'O';

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++)
            putchar(screen[y][x]);
        putchar('\n');
    }

    printf("Score: %d\n", score);
    printf("Press SPACE to flap!\n");
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