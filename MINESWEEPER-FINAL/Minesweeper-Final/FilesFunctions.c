#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "FilesFunctions.h"

extern won;

void sort_file()
{
    FILE *fp,*fp1;
    fp=fopen("scoreboard.txt","a+");
    char names[100][100],tmp_ch[100];
    int scores[100],tmp_sc;
    int i=0,j=0,count=0;
    while(!feof(fp))
    {
        fscanf(fp,"%s",&names[count]);
        fscanf(fp,"%d",&scores[count]);
        count++;
    }
    count--;
    for(i=0; i<count; i++)
    {
        for(j=0; j<count-1; j++)
        {
            if(scores[j]<scores[j+1])
            {
                //swap names
                strcpy(tmp_ch,names[j]);
                strcpy(names[j],names[j+1]);
                strcpy(names[j+1],tmp_ch);
                //swap scores
                tmp_sc=scores[j];
                scores[j]=scores[j+1];
                scores[j+1]=tmp_sc;
            }
        }
    }
    char buffer[100];
    fp1=fopen("tempo.txt","a+");
    for(i=0; i<count; i++)
    {
        fprintf(fp1,"%s\n",names[i]);
        fprintf(fp1,"%d\n",scores[i]);
    }
    fclose(fp);
    fclose(fp1);
    remove("scoreboard.txt");
    rename("tempo.txt","scoreboard.txt");

}

void save_game()
{
    clear();
    int i,j,size_buffer=0,size_name=0;
    char name[100],tmp;
    printf("Enter Your Name : ");
    scanf("%s",name);
    for(i=0; name[i]; i++)
    {
        name[i]=toupper(name[i]);
    }
    FILE *fp;
    fp=fopen("save game.txt","a+");
//remove name if found
    char buffer[100],*tempo;
    int num_line=1,num_line2=1;
    FILE *tmp_file;
    tmp_file=fopen("tmp.txt","w");
    while(!feof(fp))
    {
        fgets(buffer,100,fp);
        tempo=strstr(buffer,name);
        size_buffer=strlen(buffer);
        size_name=strlen(name);
        if(tempo!=NULL && size_buffer-size_name-1==0)
        {
            break;
        }
        else num_line ++;
    }
    rewind(fp);
    while(!feof(fp))
    {
        fgets(buffer,100,fp);
        num_line2++;
        if(num_line!=num_line2-1)fprintf(tmp_file,"%s",buffer);
    }
    fclose(fp);
    fclose(tmp_file);
    remove("save game.txt");
    rename("tmp.txt","save game.txt");


//end removal
    fp=fopen("save game.txt","a+");

    fprintf(fp,"%s\n",name);
    for(i=0; i<array_x_size; i++)
    {
        for(j=0; j<array_y_size; j++)
        {

            fprintf(fp,"%c",user_array[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"-\n");
    for(i=0; i<array_x_size; i++)
    {
        for(j=0; j<array_y_size; j++)
        {
            fprintf(fp,"%c",dev_array[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"-\n");
    fprintf(fp,"%d\n",(current_time-start_time)/60);
    fprintf(fp,"%d\n",(current_time-start_time)%60);
    fprintf(fp,"%d\n",moves);
    fprintf(fp,"%d\n",total_flags);
    fprintf(fp,"%d\n",total_questions);
    fprintf(fp,"%d\n",num_mines);
    fprintf(fp,"%d\n",remain_cells);
    fprintf(fp,"-\n");
    exit(1);
}

void load_game()
{
    clear();
    SYSTEMTIME str_t;
    GetSystemTime(&str_t);
    start_time =str_t.wHour*60*60+str_t.wMinute*60+str_t.wSecond;
    int i,j;
    int flag2=0;
    char tmp2;
    printf("Enter Your Name : ");
    char name[100],buffer[100],*tmp;
    scanf("%s",name);
    for(i=0; name[i]; i++)
    {
        name[i]=toupper(name[i]);
    }
    FILE *fp;
    fp=fopen("save game.txt","a+");
    while(!feof(fp))
    {
        fgets(buffer,100,fp);
        tmp=strstr(buffer,name);
        if(tmp!=NULL)
        {
            flag2=1;
            break;
        }
    }
    if(flag2==1)
    {
        //obtain user array
        for(i=0; i<100; i++)
        {
            for(j=0; j<100; j++)
            {
                tmp2=fgetc(fp);
                if(tmp2!='\n')
                {
                    user_array[i][j]=tmp2;
                    array_y_size++;
                }
                else break;
            }
            tmp2=fgetc(fp);
            if(tmp2=='-') break;
            array_x_size++;
            fseek( fp, -1, SEEK_CUR );
        }
        array_x_size++;
        array_y_size++;
        array_y_size=array_y_size/array_x_size;
//obtain developper array
        tmp2=fgetc(fp);
        for(i=0; i<100; i++)
        {
            for(j=0; j<100; j++)
            {
                tmp2=fgetc(fp);
                if(tmp2!='\n')
                {
                    dev_array[i][j]=tmp2;
                }
                else break;
            }
            tmp2=fgetc(fp);
            if(tmp2=='-') break;
            fseek( fp, -1, SEEK_CUR );
        }
//obtain time,moves,flags,questions
        tmp2=fgetc(fp);
        fscanf(fp,"%d",&minutes);
        fscanf(fp,"%d",&seconds);
        fscanf(fp,"%d",&moves);
        fscanf(fp,"%d",&total_flags);
        fscanf(fp,"%d",&total_questions);
        fscanf(fp,"%d",&num_mines);
        fscanf(fp,"%d",&remain_cells);
        action='l';
        play();
    }
    else
    {
        printf("NOT FOUND!!\n");
        system("pause");
        clear();
        main();
    }
}

void load_scoreboard()
{
    clear();
    char buffer;
    FILE *fp;
    fp=fopen("scoreboard.txt","a+");

    rewind(fp);
    while(!feof(fp))
    {
        buffer=fgetc(fp);
        printf("%c",buffer);
    }
    fclose(fp);
    system("color 3f");
    system("pause");
    clear();
    if(won!=1) main();
    else exit(0);
}

void register_score()
{
    char name[100];
    int flag=0,old_score=0,counter=0,size_buffer=0,size_name=0; //counter to count number of times the code is entered to escape the last line
    score=(power(array_x_size,4)*power(array_y_size,4))/((current_time-start_time+1)*moves);
    printf("\n\nPlease enter your name : ");
    scanf("%s", name);
    int i;
    for(i=0; name[i]; i++)
    {
        name[i]=toupper(name[i]);
    }

    FILE *fp;
    fp=fopen("scoreboard.txt","a+");
    rewind(fp);

//remove name if found
    char buffer[100],*tempo;
    int num_line=1,num_line2=0,last_line=1;
    FILE *tmp_file;
    tmp_file=fopen("tmp.txt","w");
// count lines of file
    while(!feof(fp))
    {
        fgets(buffer,100,fp);
        last_line++;
    }
//end count
    rewind(fp);
    while(!feof(fp))
    {
        fgets(buffer,100,fp);
        tempo=strstr(buffer,name);
        if(tempo!=NULL )
        {
            flag=1;
            break;
        }
        else num_line ++;
    }
    if(flag==1)
    {
        fscanf(fp,"%d",&old_score);
    }
    if(old_score<score)
    {
        rewind(fp);
        while(!feof(fp))
        {
            counter++;
            fgets(buffer,100,fp);
            num_line2++;
            if(num_line!=num_line2 && num_line!=num_line2-1&&counter<last_line-2)
            {
                fprintf(tmp_file,"%s",buffer);
            }
        }

        int q;
       // rewind(tmp_file);

        fprintf(tmp_file,"%s\n",name);
        fprintf(tmp_file,"%d\n",score);

        fflush(stdin);
        fflush(stdout);
        fclose(fp);
        fclose(tmp_file);
        remove("scoreboard.txt");
        rename("tmp.txt","scoreboard.txt");
    }

//end removal
    sort_file();
    load_scoreboard();
    exit(0);
}


