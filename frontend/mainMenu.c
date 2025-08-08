#include <stdio.h>
#include <stdlib.h>



void menu(int input) {
    static int selection = 1;

    if (selection != 1 && input == 1) {
        selection--;
    }
    else if(selection != 2 && input == 2) {
        selection++;
    }
    
    printf("Play Game %s", (selection == 1)? "<-\n":"\n");
    printf("Log %s", (selection == 2)? "<-\n":"\n");
}

char* getUsername() {
    char choice = 1;
    int memorySpace = 0;
    char* str = NULL;

    printf("Enter you name\n");

    choice = getchar();

    while(choice != '\n' && choice != EOF) {
        str = realloc(str, memorySpace + 1);
        str[memorySpace++] = choice;
        
        choice = getchar();
    }

    str = realloc(str, memorySpace + 1);
    str[memorySpace] = '\0';

    return str;
}