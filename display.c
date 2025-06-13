/*******************************************************************************
    HEADERS
*******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <windows.h>
#include "display.h"
#include "bird.h"

/*******************************************************************************
    PREPROCESSING DEFINITIONS
*******************************************************************************/

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

static void limpiarBuffer(HANDLE);

/*******************************************************************************
    DEFINITION OF GLOBAL FUNCTION
*******************************************************************************/

void printGame(){
    uint8_t x,y;

    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++){
            if (y == 0 || y == (HEIGHT - 1)){
                printf("-");
            }
            else if(y == (HEIGHT - flappyBird.possy) && x == flappyBird.possx){
                printf("*");
            }
            else{
                printf(" ");        //FALTA AÑADIR EL PRINT DE LOS TUBOS
            }
        }
        printf("\n");
        
    }
    
}

void drawBuffer(HANDLE hBuffer) {
    int i, j;

    limpiarBuffer(hBuffer);

    for (i = 0; i < HEIGHT; i++) {
        DWORD written;
        for (j = 0; j < WIDTH; j++) {
            if (i == 0 || i == (HEIGHT - 1)){
                WriteConsoleOutputCharacter(hBuffer, "-", 1, (COORD){j, i}, &written);
            }
            else if(i == (HEIGHT - flappyBird.possy) && j == flappyBird.possx){
                WriteConsoleOutputCharacter(hBuffer, "*", 1, (COORD){j, i}, &written);
            }
            else{
                WriteConsoleOutputCharacter(hBuffer, " ", 1, (COORD){j, i}, &written);        //FALTA AÑADIR EL PRINT DE LOS TUBOS
            }
            
        }
    }
}

/*******************************************************************************
    DEFINITION OF LOCAL FUNCTION
*******************************************************************************/
static void limpiarBuffer(HANDLE hBuffer) {
    DWORD charsWritten;
    COORD coord = {0, 0};
    FillConsoleOutputCharacter(hBuffer, ' ', HEIGHT * WIDTH, coord, &charsWritten);
}