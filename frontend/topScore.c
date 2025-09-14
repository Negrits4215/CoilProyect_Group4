/*
 * Public Functions (available through topScore.h):
 * 
 * podiumInit()
 *   Builds the in-memory podium from "history.log". Parses each line
 *   as "name: score", sorts candidates by score (desc), and stores the
 *   top PODIUM_LENGHT entries in the static 'podium' array.
 * 
 * podiumUpdate(char* pname, int score)
 *   Tries to insert/update a player (name, score) into the podium if the
 *   new score belongs in the top PODIUM_LENGHT. Uses the same comparator
 *   as sorting (higher score is better).
 * 
 * topScoreDraw()
 *   Clears the screen and renders the podium with big index numerals
 *   (topNums frames) and each player's name and score.
 * 
 * -------------------------------------------------------------
 * Private Data & Functions (internal use only in this file):
 * 
 * static TopPlayer podium[PODIUM_LENGHT]
 *   Holds the current top players in memory.
 * 
 * compareTopPlayers(const void* a, const void* b) [static]
 *   qsort comparator for TopPlayer. Returns negative if 'a' should come
 *   before 'b' (i.e., when a.score > b.score), zero if equal, positive
 *   otherwise. Used both by qsort and insertion checks.
 */

#include <stdio.h>
#include <stdlib.h>
#include "topScore.h"
#include "../constants.h"
#include "mainMenu.h"

static TopPlayer podium[PODIUM_LENGHT];

static int compareTopPlayers(const void*, const void*);

void podiumInit() {
    FILE* file = fopen("history.log", "r");
    char line[100];
    int i, j, endOfName;
    TopPlayer buffer;
    TopPlayer *tempList = calloc(PODIUM_LENGHT + 1, sizeof(TopPlayer));


    if (file) {
        for (j = 0; fgets(line, sizeof(line), file); j++) {
            endOfName = 0;
            buffer.score = 0;

            for (i = 0; (line[i] != '\n' && line[i] != '\0'); i++) {
                if (line[i] == ':' && line[i + 1] == ' '){
                    endOfName = 1;
                    buffer.name[i] = '\0';
                }
                if(!endOfName){
                    buffer.name[i] = line[i];
                }
                else if(line[i] >= '0' && line[i] <= '9'){
                    buffer.score = buffer.score * 10 + line[i] - '0';
                }
            }

            tempList[(j < (PODIUM_LENGHT + 1)? j : PODIUM_LENGHT)] = buffer;

            qsort(tempList, PODIUM_LENGHT + 1, sizeof(TopPlayer), compareTopPlayers);
        }
        fclose(file);

        for (i = 0; i < PODIUM_LENGHT; i++) {
            podium[i] = tempList[i];
        }
        free(tempList);
    }
}

void podiumUpdate(char* pname, int score) {
    int i;
    TopPlayer newPlayer, buffer;

    for (i = 0; (pname[i] != '\0' && i < MAX_NAME_LENGHT); i++) {
        newPlayer.name[i] = pname[i];
    }
    newPlayer.name[++i] = '\0';
    newPlayer.score = score;

    for (i = 0; i < PODIUM_LENGHT; i++){
        if (compareTopPlayers(&podium[i], &newPlayer) > 0) {
            buffer = podium[i];
            podium[i] = newPlayer;
            newPlayer = buffer;
        }
    }   
}

void topScoreDraw(){
    int i, j;

    system("cls");

    for (i = 0; i < PODIUM_LENGHT; i++) {
        if (i < TOPNUMS_FRAME_NUM) {
            for (j = 0; j < TOPNUMS_FRAME_HEIGHT; j++) {
                if (j >= TOPNUMS_FRAME_HEIGHT/2 && j < (TOPNUMS_FRAME_HEIGHT/2 + 1)) {
                    printf("%s\t%s\t%d\n", topNums[j + (i * TOPNUMS_FRAME_HEIGHT)], podium[i].name, podium[i].score);
                } 
                else {
                    printf("%s\n", topNums[j + (i * TOPNUMS_FRAME_HEIGHT)]);
                }
            }  
        }
        else {
            for (j = 0; j < TOPNUMS_FRAME_WIDTH; j++) {
                printf(" ");
            }
            
            printf("%d.\t%s\t%d\n", (i + 1), podium[i].name, podium[i].score);
        }
        printf("\n");
    }

    printf("Press SPACE to exit");    
}

//Private functions
static int compareTopPlayers(const void *a, const void *b) {
    const TopPlayer *p1 = (const TopPlayer *)a;
    const TopPlayer *p2 = (const TopPlayer *)b;

    if (p1->score < p2->score) {
        return 1;
    }
    if (p1->score > p2->score) {
        return -1;
    }
    return 0;
}

