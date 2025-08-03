#ifndef GAME_H
#define GAME_H

extern int score;
extern int lifes;

void gameInit();
int checkCollision();
void updateGame(int);
void birdJump();

#endif