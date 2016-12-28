#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
#include "IdleFunctionThread.h"

void *one_minute_idle(void *arg)
{
    SYSTEMTIME timeStructure;
    GetSystemTime(&timeStructure);
    unsigned long initialSeconds;
    unsigned long currentSeconds;
    int idleMinutes = 0;
    char inputType = (char*)arg;
    thread_exit_flag = 0;

    initialSeconds = timeStructure.wHour * 60 * 60 + timeStructure.wMinute * 60 + timeStructure.wSecond;

    while(!thread_exit_flag)
    {
        GetSystemTime(&timeStructure);

        currentSeconds = timeStructure.wHour * 60 * 60 + timeStructure.wMinute * 60 + timeStructure.wSecond;

        if((currentSeconds - initialSeconds) == 60)
        {
            initialSeconds = currentSeconds;
            idleMinutes++;
            if (inputType == 'n'){
                printf("\nYou've been idle for %d minute/s. Please enter the coordinate: ", idleMinutes);
            }
            else{
                printf("\nYou've been idle for %d minute/s. Please enter the action: ", idleMinutes);
            }

        }
    }
    pthread_exit(NULL);
}
