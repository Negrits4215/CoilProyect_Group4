/*******************************************************************************
    HEADERS
*******************************************************************************/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "display.h"
#include "bird.h"

/*******************************************************************************
    PREPROCESSING DEFINITIONS
*******************************************************************************/

#define FRAMEDELAY (1000./60.) //60Hz

/*******************************************************************************
    TYPEDEF & STRUCT
*******************************************************************************/

/*******************************************************************************
    GLOBAL PUBLIC VARIABLE PROTOTYPE
*******************************************************************************/

/*******************************************************************************
    GLOBAL STATIC CONST VARIABLE
*******************************************************************************/

/*******************************************************************************
    GLOBAL STATIC VARIABLE
*******************************************************************************/

/*******************************************************************************
    PRIVATE FUNCTION PROTOTYPE
*******************************************************************************/

/*******************************************************************************
    DEFINITION OF GLOBAL FUNCTION
*******************************************************************************/

/*******************************************************************************
    DEFINITION OF LOCAL FUNCTION
*******************************************************************************/

int main(){
    HANDLE hBuffer1 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    HANDLE hBuffer2 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    HANDLE currentBuffer = hBuffer1;
    HANDLE nextBuffer = hBuffer2;

    int quit = 1;
    clock_t frameStart;
    double frameTime;


    birdInit();
    

    while (quit) {
        frameStart = clock();

        flappyBird.updateBird();

        if (_kbhit()) {  // Si se presionó una tecla
            int ch = _getch();
            if (ch == 32) { // Código ASCII de barra espaciadora
                flappyBird.flap();
                flappyBird.updateBird();

            }
            if (ch == 27) { // Si querés permitir salir con ESC (ASCII 27)
                quit = 0;
            }
        }

        drawBuffer(currentBuffer);

        SetConsoleActiveScreenBuffer(currentBuffer);


        HANDLE temp = currentBuffer;
        currentBuffer = nextBuffer;
        nextBuffer = temp;


        frameTime = (clock() - frameStart) * 1000.0 / CLOCKS_PER_SEC;
        if (FRAMEDELAY > frameTime) {
            Sleep((DWORD)(FRAMEDELAY - frameTime));
        }
    }
}
