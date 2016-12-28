#include <stdio.h>
#include <stdlib.h>
#include "MinorDebuggersAndTools.h"
#define ARRAY_SIZE 100

void print_test(char array[ARRAY_SIZE][ARRAY_SIZE], int array_x_size, int array_y_size)
{
    int i, j;

    for (i=0; i<array_x_size; i++)
    {
        for(j=0; j<array_y_size; j++)
        {
            printf("%c ", array[i][j]);
        }
        printf("\n");
    }
}

int power(int x,int y)
{
    int i,newx=1;
    for(i=0; i<y; i++)
    {
        newx=newx*x;
    }
    return newx;
}

void clear()
{
    system("@cls||clear");
}
