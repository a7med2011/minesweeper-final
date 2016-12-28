#ifndef FILESFUNCTIONS_H_INCLUDED
#define FILESFUNCTIONS_H_INCLUDED
#define ARRAY_SIZE 100

extern int score, array_x_size, array_y_size, current_time, start_time, moves, minutes, seconds, total_flags, total_questions, num_mines, remain_cells, action;
extern char user_array[ARRAY_SIZE][ARRAY_SIZE], dev_array[ARRAY_SIZE][ARRAY_SIZE];

void sort_file();
void save_game();
void load_game();
void load_scoreboard();
void register_score();

#endif // FILESFUNCTIONS_H_INCLUDED
