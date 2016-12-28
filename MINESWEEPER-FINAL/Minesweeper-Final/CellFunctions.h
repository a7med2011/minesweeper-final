#ifndef CELLFUNCTIONS_H_INCLUDED
#define CELLFUNCTIONS_H_INCLUDED
#define ARRAY_SIZE 100

extern int x_coor, y_coor, array_x_size, array_y_size, remain_cells;
extern char dev_array[ARRAY_SIZE][ARRAY_SIZE];
extern char user_array[ARRAY_SIZE][ARRAY_SIZE];


int calculate_mines(int x_coor, int y_coor); /*Function to be excuted after placing mines in dev_array to calculate and return
the number of mines in each cell*/
void DFS_recursion(int x_coor,int y_coor); /*This function is excuted each time an unopened cell is opened it opens all
other clear cells (only with 'x') ignoring flags and questions
MUST be sure the the cell is unopened in user_grid and empty in dev_grid*/


#endif // CELLFUNCTIONS_H_INCLUDED
