#ifndef BIRD_H
#define BIRD_H

/*******************************************************************************
    HEADERS
*******************************************************************************/

#include <stdint.h>
#include "display.h"

/*******************************************************************************
    PREPROCESSING DEFINITIONS
*******************************************************************************/

#define MAVITY 9.8f
#define SPEEDUP 0.2f
#define POSS_YMIN ((HEIGHT*20)/100)
#define POSS_YMAX (HEIGHT - POSS_YMIN)
#define POSS_X ((WIDTH*5)/100)

/*******************************************************************************
    TYPEDEF & STRUCT
*******************************************************************************/

typedef struct {
    float velx, vely;
    uint8_t possx;
    uint8_t possy;
    float floaposs;

    void (*flap) ();
    void (*updateBird) ();
} bird;

/*******************************************************************************
    GLOBAL PUBLIC VARIABLE PROTOTYPE
*******************************************************************************/
extern bird flappyBird; 

/*******************************************************************************
    PUBLIC FUNCTION PROTOTYPE
*******************************************************************************/

void birdInit();

/*******************************************************************************
*******************************************************************************/

#endif 