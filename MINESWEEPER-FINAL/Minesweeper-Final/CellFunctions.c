#include <stdio.h>
#include <stdlib.h>
#include "CellFunctions.h"

int calculate_mines(int x_coor, int y_coor)
{
    /*Function to be excuted after placing mines in dev_array to calculate and return the number of mines in each cell*/

    int i, j;
    int number_of_mines = 0;

    if(dev_array[x_coor][y_coor] != '*')
    {
        for(i=x_coor-1; i<=x_coor+1; i++)
        {
            for(j=y_coor-1; j<=y_coor+1; j++)
            {
                if((i>=0 && j>=0) && (i<array_x_size && j<array_y_size)) //!(i==x_coor && j==y_coor) &&
                {
                    if(dev_array[i][j]=='*')
                    {
                        number_of_mines++;
                    }
                }
            }
        }
    }
    return number_of_mines;
}

void DFS_recursion(int x_coor, int y_coor)
{
    /*This function is excuted each time an unopened cell is opened it opens all other clear cells (only with 'X') ignoring flags and questions
    MUST be sure the the cell is unopened in user_grid and empty in dev_grid*/

    int i, j;
    if(user_array[x_coor][y_coor]=='X') remain_cells--;
    user_array[x_coor][y_coor] = dev_array[x_coor][y_coor];

    if(dev_array[x_coor][y_coor]>='1' && dev_array[x_coor][y_coor]<='8')
    {
        return;
    }

    if(user_array[x_coor][y_coor]=='F' || user_array[x_coor][y_coor]=='?')
    {
        return;
    }

    for(i=x_coor-1; i<=x_coor+1; i++)
    {
        for(j=y_coor-1; j<=y_coor+1; j++)
        {
            if(((i>=0 && i<array_x_size) && (j>=0 && j<array_y_size)) && ((user_array[i][j]== 'X')&&(dev_array[i][j]!='*')))
            {
                DFS_recursion(i, j);
            }
        }
    }
}
