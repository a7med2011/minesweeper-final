#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <pthread.h>
#include "ExceptionHandlers.h"
#include "TextOnlyFunctions.h"
#include "IdleFunctionThread.h"
#include "MinorDebuggersAndTools.h"
#include "CellFunctions.h"
#define ARRAY_SIZE 100

int x_coor, y_coor;
int array_x_size, array_y_size;
char user_array[ARRAY_SIZE][ARRAY_SIZE];
char dev_array[ARRAY_SIZE][ARRAY_SIZE];
char action;
int start_time;
int current_time;
int num_mines;
int remain_cells=0;
int flag;
int player_lost_win;
int moves,total_flags,total_questions,num_flags,mines_in_square, questions_in_square;
int lost;
int won;
int musicOn = 1;
int minutes=0,seconds=0,score=0,new_time=0;
int thread_exit_flag;


void new_game(); // scan array size , return array size ,ahmed
void regen_user_grid(); //Ahmed
void open_first_cell(); //Open first cell, generate mines, place number of mines in empty cells,Ahmed
void cell_action(); // Open cell , compare cell with debugging grid, choose an action to do with the cell
void scan_home_input(); //Scans the input from the user in the main page and decides what action to do, goes to new_game, load_game, load_scoreboard, music, help, exit
void lose();
void win();
void play();


int main()
{
//color
    system ("color 3f");
//end color

//Initialzing values
    remain_cells = 0;
    flag = 0;
    player_lost_win = 0;
    moves = 0;
    total_flags = 0;
    total_questions = 0;
    num_flags = 0;
    mines_in_square =0 ;
    lost = 0;
    won = 0;
    questions_in_square = 0;

//Initialzing values

    fflush(stdin);
    fflush(stdout);
    print_logo();
    init_home();
    scan_home_input();

    system("pause");
    return 0;
}

void scan_home_input()
{
    //Scans the input from the user in the main page and decides what action to do, goes to new_game, load_game, load_scoreboard, music, help, exit

    printf("\nPlease enter the desired action: ");

    char action;

    action = exceptionHandledCharInput();

    if ((action == 'N' || action == 'n'))
    {
        new_game();
        play();
        main();
        return;
    }
    else if ((action == 'L' || action == 'l'))
    {
        load_game();
        return;
    }
    else if ((action == 'S' || action == 's'))
    {
        load_scoreboard();
        return;
    }
    else if ((action == 'O' || action == 'o' || action == 'F' || action == 'f'))
    {
        musicOn = !musicOn;
        if(musicOn!=0)
        {
            printf("\nSound turned on.\n");
        }
        else
        {
            printf("\nSound turned off.\n");
        }
        scan_home_input();
        return;
    }
    else if ((action == 'H' || action == 'h'))
    {
        help();
        main();
        return;
    }
    else if ((action == 'E' || action == 'e'))
    {
        exit(0);
    }
    else
    {
        printf("\nPlease type the action correctly!\n");
        scan_home_input();
        return;
    }
}
void new_game()
{
    int i,j,tmp;

//color
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
//end color

    printf("\nEnter the Height : ");

    array_x_size = exceptionHandledIntInput(2,ARRAY_SIZE);

    printf("\nEnter the Width : ");
    array_y_size = exceptionHandledIntInput(2,ARRAY_SIZE);

    remain_cells=array_x_size*array_y_size;
    clear();

//initializing the user & dev array
    for(i=0; i<array_x_size; i++)
    {
        for(j=0; j<array_y_size; j++)
        {
            user_array[i][j]='X';
            dev_array[i][j]=' ';
        }
    }
//printing the first array
    for(i=0; i<=array_x_size; i++)
    {
        for(j=0; j<=array_y_size; j++)
        {
            if(i==0)
            {
                SetConsoleTextAttribute(hConsole, saved_attributes); //color
                if(j<10) printf("%d    ",j);
                else printf("%d   ",j);
            }
            else if(j==0)
            {
                SetConsoleTextAttribute(hConsole, saved_attributes);//color
                if(i<10) printf("%d   ",i);
                else printf("%d  ",i);
            }
            else
            {
                int c, d;
                if(array_x_size<20 && array_y_size<20)
                {
                    for ( c = 1 ; c <= 1500 ; c++ )
                    {
                        for ( d = 1 ; d <= 1500 ; d++ ) {}
                    }
                }
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_INTENSITY  | BACKGROUND_BLUE | BACKGROUND_RED |BACKGROUND_GREEN);
                printf("|%c|  ",user_array[i-1][j-1]);
            }
        }
        printf("\n\n");
    }
    SetConsoleTextAttribute(hConsole, saved_attributes); //color

    pthread_t idleThread;

    printf("Enter X : ");
    pthread_create(&idleThread, NULL, one_minute_idle, 'n');//starts thread
    x_coor = exceptionHandledIntInput(0, array_x_size)-1;
    thread_exit_flag = 1;
    pthread_cancel(idleThread);//ends thread

    printf("Enter Y : ");
    pthread_create(&idleThread, NULL, one_minute_idle, 'n');//starts thread
    y_coor = exceptionHandledIntInput(0, array_y_size)-1;
    thread_exit_flag = 1;
    pthread_cancel(idleThread);//ends thread
}
void play()
{
    if(action!='l')open_first_cell();

    while(flag==0)
    {
        regen_user_grid();
        cell_action();
    }
    if(lost)
    {
        lose();
    }
    else if(won)
    {
        win();
    }
}

void cell_action()
{
    //color
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
//end color
    int i,j;
    moves++;
    num_flags=0;
    mines_in_square=0;
    questions_in_square = 0;
    for(i=x_coor-1; i<=x_coor+1; i++)
    {
        for(j=y_coor-1; j<=y_coor+1; j++)
        {
            if((i>=0 && j>=0) && (i<array_x_size && j<array_y_size))
            {
                if(user_array[i][j]=='F')
                {
                    num_flags++;
                }
                if(dev_array[i][j]=='*')
                {
                    mines_in_square++;
                }
                if(user_array[i][j]=='?')
                {
                    questions_in_square++;
                }
            }
        }
    }
    if(action=='o' || action == 'O')
    {
        if(dev_array[x_coor][y_coor]!='*' && user_array[x_coor][y_coor]!='F')
        {
            if(user_array[x_coor][y_coor]=='X')
            {
                DFS_recursion(x_coor,y_coor);
                if(num_mines==remain_cells)
                {
                    flag = 1;
                    won = 1;
                    return;
                }
            }
            else
            {
                if(num_flags == mines_in_square || questions_in_square == mines_in_square)
                {
                    for(i=x_coor-1; i<=x_coor+1 && i>=0 && i<array_x_size; i++)
                    {
                        for(j=y_coor-1; j<=y_coor+1 && j>=0 && j<array_y_size; j++)
                        {
                            if(user_array[i][j]=='X' && dev_array[i][j]=='*')
                            {
                                flag = 1;
                                lost = 1;

                            }
                            else if(user_array[i][j]=='X' && dev_array[i][j]==' ')
                            {
                                DFS_recursion(i, j);

                            }
                            else if(user_array[i][j]=='X' && dev_array[i][j]>='1' && dev_array[i][j]<='8')
                            {
                                user_array[i][j]=dev_array[i][j];
                                remain_cells --;

                            }
                            if(remain_cells == num_mines)
                            {
                                won = 1;
                                flag = 1;

                            }

                        }
                    }
                }
                if(num_mines==remain_cells)
                {
                    flag = 1;
                    won = 1;
                    return;

                }
            }
        }
        //lose
        else if(dev_array[x_coor][y_coor]=='*' &&user_array[x_coor][y_coor]!='F' )
        {
            flag = 1;
            lost = 1;
            return;
        }
    }
    else if(action=='f' || action =='F')
    {
        if(user_array[x_coor][y_coor]=='F' )
        {
            user_array[x_coor][y_coor]='X';
            total_flags--;
        }
        else if(user_array[x_coor][y_coor]=='X' )
        {

            user_array[x_coor][y_coor]='F';
            total_flags++;
        }
        else if(user_array[x_coor][y_coor]=='?')
        {
            user_array[x_coor][y_coor]='F';
            total_flags++;
            total_questions--;
        }
    }
    else if (action=='?')
    {
        if(user_array[x_coor][y_coor]=='?')
        {
            user_array[x_coor][y_coor]='X';
            total_questions--;
        }

        else if(user_array[x_coor][y_coor]=='X' )
        {
            user_array[x_coor][y_coor]='?';
            total_questions++;
        }
        else if(user_array[x_coor][y_coor]=='F')
        {
            user_array[x_coor][y_coor]='?';
            total_questions++;
            total_flags--;
        }
    }
    else if(action=='e' || action =='E')
    {
        exit(0);
    }
    else if(action=='s' || action =='S')
    {
        save_game();
        return;
    }
    else
    {
        pthread_t idleThread;

        printf("Enter a valid action : ");
        pthread_create(&idleThread, NULL, one_minute_idle, 'a');
        action = exceptionHandledCharInput();
        thread_exit_flag = 1;
        pthread_cancel(idleThread);
        cell_action();
    }
}

void open_first_cell()
{
    moves ++;
    SYSTEMTIME str_t;
    GetSystemTime(&str_t);
    start_time =str_t.wHour*60*60+str_t.wMinute*60+str_t.wSecond;
    srand(str_t.wSecond);

    int random_pose,i,j,xrand,yrand;

    num_mines=1+(array_x_size*array_y_size)/10;

    for(i=0; i<num_mines; i++)
    {
        xrand=rand()%array_x_size;
        yrand=rand()%array_y_size;
        if(array_x_size==2&&array_y_size==2)
        {
            if(xrand==x_coor&&yrand==y_coor) i--;
            else dev_array[xrand][yrand]='*';
        }
        else if(array_x_size==3&&array_y_size==3 &&x_coor==1&&y_coor==1)
        {

            if(xrand==x_coor&&yrand==y_coor) i--;
            else dev_array[xrand][yrand]='*';
        }

        else if(dev_array[xrand][yrand]=='*' || (xrand==x_coor&&yrand==y_coor) || (xrand==x_coor-1&&yrand==y_coor) || (xrand==x_coor+1&&yrand==y_coor) ||
                (xrand==x_coor&&yrand==y_coor-1) || (xrand==x_coor-1&&yrand==y_coor-1) || (xrand==x_coor+1&&yrand==y_coor-1)||
                (xrand==x_coor&&yrand==y_coor+1) || (xrand==x_coor-1&&yrand==y_coor+1) || (xrand==x_coor+1&&yrand==y_coor+1) ) i--;

        else  dev_array[xrand][yrand]='*';
    }
    for (i=0; i<array_x_size; i++)
    {
        for(j=0; j<array_y_size; j++)
        {
            int number_of_mines=calculate_mines(i, j);
            if(number_of_mines!=0)//doesn't print '0'
            {
                dev_array[i][j]='0'+number_of_mines; //converts int to char
            }
        }
    }
    //user_array[x_coor][y_coor]=dev_array[x_coor][y_coor];
    DFS_recursion(x_coor,y_coor);

    if(remain_cells == num_mines)
    {
        won = 1;
        flag = 1;
    }
}

void regen_user_grid()
{
    clear();

//color
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
//end color

    SYSTEMTIME str_t;
    GetSystemTime(&str_t);
    current_time=str_t.wHour*60*60+str_t.wMinute*60+str_t.wSecond;
    new_time=current_time-start_time+minutes*60+seconds;
    printf("\t\t\t\tTime : %d minutes & %d seconds\n",new_time/60,new_time%60);
    printf("\t\t\t\tMoves : %d\n",moves);
    printf("\t\t\t\tFlags : %d\n",total_flags);
    printf("\t\t\t\tQuestions : %d\n\n",total_questions);
    int i, j, temp;
    for(i=0; i<=array_x_size; i++)
    {
        for(j=0; j<=array_y_size; j++)
        {
            if(i==0)
            {
                SetConsoleTextAttribute(hConsole, saved_attributes);
                if(j<10) printf("%d    ",j);
                else printf("%d   ",j);
            }
            else if(j==0)
            {
                SetConsoleTextAttribute(hConsole, saved_attributes);
                if(i<10) printf("%d   ",i);
                else printf("%d  ",i);
            }
            else
            {
                if(user_array[i-1][j-1]=='F') SetConsoleTextAttribute(hConsole,64);
                else if(user_array[i-1][j-1]=='?')  SetConsoleTextAttribute(hConsole,32);
                else if(user_array[i-1][j-1]=='X')  SetConsoleTextAttribute(hConsole,240);
                else SetConsoleTextAttribute(hConsole,224);
                printf("|%c|",user_array[i-1][j-1]);
                SetConsoleTextAttribute(hConsole,240);
                printf("  ");
            }
        }
        printf("\n\n");
    }
    if (player_lost_win == 0)
    {
        pthread_t idleThread;

        SetConsoleTextAttribute(hConsole, saved_attributes);//color

        printf("Enter X : ");
        pthread_create(&idleThread, NULL, one_minute_idle, 'n');//starts thread
        x_coor = exceptionHandledIntInput(0, array_x_size)-1;
        thread_exit_flag = 1;
        pthread_cancel(idleThread);//ends thread

        printf("Enter Y : ");
        pthread_create(&idleThread, NULL, one_minute_idle, 'n');//starts thread
        y_coor = exceptionHandledIntInput(0, array_y_size)-1;
        thread_exit_flag = 1;
        pthread_cancel(idleThread);//ends thread

        printf("Enter action ( O , F , ?, S, E): ");
        pthread_create(&idleThread, NULL, one_minute_idle, 'a');//starts thread
        action = exceptionHandledCharInput();
        thread_exit_flag = 1;
        pthread_cancel(idleThread);//ends thread

    }
}
void lose()
{
    system("color 3f");
    int i, j;

    player_lost_win = 1;

    if(musicOn)
    {
        Beep(250,300);
        Beep(300,600);
        Beep(400,500);
        Beep(550,1000);
    }

    for(i=0; i<array_x_size; i++)
    {
        for(j=0; j<array_y_size; j++)
        {
            if((user_array[i][j] == 'F' || user_array[i][j] == '?')&& dev_array[i][j] != '*' )
            {
                user_array[i][j]='_';
            }
            if((user_array[i][j] == 'F' || user_array[i][j] == '?') && dev_array[i][j] == '*' )
            {
                user_array[i][j]='*';
            }
            if(user_array[i][j] == 'X' && dev_array[i][j] == '*' )
            {
                user_array[i][j]='M';
            }

        }
    }
    user_array[x_coor][y_coor] = '!';
    clear();
    regen_user_grid();
    printf("\n\t\t\tYou Lost! Hard Luck Amigo!\n");
    printf("\nEnter any key to continue... ");
    fflush(stdin);
    fflush(stdout);
    char dummy[1];
    gets(dummy);
    system("color 3f");
    //dummy [1] = getchar();
    clear();

}

void win()
{
    system("color 3f");
    int i, j;
    player_lost_win=1;
    if(musicOn)
    {
        Beep(600,300);
        Beep(650,500);
        Beep(700,700);
        Beep(750,900);
        Beep(800,1500);
    }
    for(i=0; i<array_x_size; i++)
    {
        for(j=0; j<array_y_size; j++)
        {
            if (dev_array[i][j]=='*')
            {
                user_array[i][j]='F';
            }
        }
    }

    regen_user_grid();
    printf("\n\n\t\t\tCongratulations! You WON!");
    char name[100];
    register_score();

    clear();
    load_scoreboard();
}
