#include <stdio.h>
#include <stdlib.h>
#include "ExceptionHandlers.h"

int exceptionHandledIntInput(int lowerLimit, int upperLimit)
{
    int integer = 0;
    char firstChar;
    char dummyChar;
    int integerArray[100];
    int integerArraySize=0;
    int integerStart;
    int integerEnd;
    int integerSize = 0;
    int i;

    fflush(stdin);
    fflush(stdout);
    firstChar = getchar();

    integerArraySize = 0;
    if(firstChar>='0'&&firstChar<='9')
    {
        integerSize++;
    }
    integerArray[integerArraySize] =(char) firstChar;
    integerArraySize++;

    while((dummyChar = getchar()) != '\n')
    {
        integerArray[integerArraySize]=dummyChar;
        integerArraySize++;
        if(dummyChar>='0'&&dummyChar<='9')
        {
            integerSize++;
        }
    }

    integerEnd = integerArraySize-1;
    while(integerArray[integerEnd] == '\n' || integerArray[integerEnd] == ' ' || integerArray[integerEnd] == '\t')
    {
        integerEnd--;
    }

    integerStart = 0;
    while(integerArray[integerStart] == '\n' || integerArray[integerStart] == ' ' || integerArray[integerStart] == '\t')
    {
        integerStart++;
    }

    if(integerSize != (integerEnd - integerStart + 1))
    {
        printf("\nInvalid Input! Re-enter the integer correctly!\n");
        exceptionHandledIntInput(lowerLimit, upperLimit);
        return;
    }

    int expValue = 0;

    for(i=integerEnd; i>=integerStart; i--)
    {
        integer += (integerArray[i]-48)*(int)pow(10,expValue++);
    }

    if(integer>upperLimit)
    {
        printf("\nToo Large Number! Please consider the boundaries.\n");
        exceptionHandledIntInput(lowerLimit, upperLimit);
        return;
    }
    else if(integer<lowerLimit)
    {
        printf("\nToo Small Number! Please consider the boundaries.\n");
        exceptionHandledIntInput(lowerLimit, upperLimit);
        return;
    }
    return integer;
}

char exceptionHandledCharInput()
{
    char character;
    int dummy[100];
    char dummyChar;
    int dummySize = 0;
    int spaces = 0;
    int charPosition;
    int i;

    while(((dummyChar=getchar())!= '\n'))
    {
        dummy[dummySize++]=dummyChar;
    }

    dummy[dummySize]='\0';

    for(i=0; i<dummySize; i++){
        if(dummy[i] == ' ' || dummy[i] == '\t'){
            spaces++;
        }
    }

    if (dummy[0]=='\0')
    {
        exceptionHandledCharInput();
        return;
    }
    else if(dummy[1] == '\0')
    {
        character = dummy[0];
        return character;
    }
    else if((dummySize- spaces) == 1){
        for(i=0; i<dummySize; i++){
            if(dummy[i] != ' ' && dummy[i] != '\t'){
                character = dummy[i];
                return character;
            }
        }
    }
    else
    {
        printf("\nInvalid Input! Please Type The Correct Character.\n");
        exceptionHandledCharInput();
    }
}
