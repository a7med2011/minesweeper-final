#include <stdio.h>
#include <stdlib.h>
#include "TextOnlyFunctions.h"

void init_home()
{
    player_lost_win=0;
    lost = 0;
    won = 0;
    system ("color 3f");//color
    printf("Please Choose An Option To Continue:-\n");
    printf("\n\n-New Game (N)\n");
    printf("-Load Game (L)\n");
    printf("-Scoreboard (S)\n");
    printf("-Sounds (On \"O\", Off \"F\")\n");
    printf("-Help (H)\n");
    printf("-Exit (E)\n");
}
void print_logo()
{
    printf("\t\t\t---Welcome To---\n");
    printf("\t\t\tMinesweeper Game\n");
    printf("\t     Credits to: Ahmed Hussien & Bassam Aiman\n");
    printf("\t\t\t   HAVE FUN! ;)\n\n\n");
}
void help()
{
    clear();
    printf("\nFor each turn of the game you have to make three inputs:");
    printf("\n(Enter X:) It's where you should enter the desired cell X-coordinate.");
    printf("\n(Enter Y:) It's where you should enter the desired cell Y-coordinate.");
    printf("\n(Action:) It's where you enter the action you want to do with the specified cell.");
    printf("\n\nActions available are:");
    printf("\n(O) For opening an/a unopened/opened cell.");
    printf("\n(F) To flag/unflag an unopened cell.");
    printf("\n(?) To put a question mark on a cell (treated as a flag and used when you are uncertain).");
    printf("\n(S) To save the game.\n");
    printf("\n(E) To exit the game.\n");
    printf("\nPress any key to continue ... ");
    char dummy[1];
    gets(dummy);
    clear();
}
