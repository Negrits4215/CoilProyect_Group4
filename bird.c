/*******************************************************************************
    HEADERS
*******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "bird.h"

#define SCORE 10 //game score Cambiar/Remover al hacer struct game

/*******************************************************************************
    PREPROCESSING DEFINITIONS
*******************************************************************************/

/*******************************************************************************
    TYPEDEF & STRUCT
*******************************************************************************/

/*******************************************************************************
    GLOBAL PUBLIC VARIABLE PROTOTYPE
*******************************************************************************/

bird flappyBird;

/*******************************************************************************
    GLOBAL STATIC CONST VARIABLE
*******************************************************************************/

/*******************************************************************************
    GLOBAL STATIC VARIABLE
*******************************************************************************/

/*******************************************************************************
    PRIVATE FUNCTION PROTOTYPE
*******************************************************************************/

static uint8_t setBirdHeight();
static void update();
static void jump();

/*******************************************************************************
    DEFINITION OF GLOBAL FUNCTION
*******************************************************************************/
void birdInit(){
    flappyBird.velx = 1.0;
    flappyBird.vely = 0;
    flappyBird.possx = POSS_X;
    flappyBird.possy = 25; //setBirdHeight();
    flappyBird.floaposs = 25.; //(float)setBirdHeight();

    flappyBird.flap = jump;
    flappyBird.updateBird = update;
}

/*******************************************************************************
    DEFINITION OF LOCAL FUNCTION
*******************************************************************************/

static uint8_t setBirdHeight(){
    uint8_t ret;
    uint32_t seed;
    
    seed = (uint32_t)time(NULL);

    srand(seed);
    ret = rand()%(POSS_YMAX - POSS_YMIN + 1) + POSS_YMIN;

    return ret;
}

static void update(){
    

    if(SCORE%10)
        flappyBird.velx += SPEEDUP;

    flappyBird.floaposs = flappyBird.floaposs + flappyBird.vely*PERIOD - ((MAVITY/2)*(PERIOD*PERIOD));
    flappyBird.possy = (uint8_t)flappyBird.floaposs;

    flappyBird.vely = flappyBird.vely - (MAVITY*PERIOD);

}

static void jump(){
    flappyBird.vely = 10.;
}