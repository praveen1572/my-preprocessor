#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"

int header_inclusion(char *line,FILE *out)
{
    FILE *fp;
    char filename[100],path[300],temp[1000];
    int i=0,j=0;

    while(line[i]!='"'&&line[i]!='<'&&line[i]!='\0')
        i++;

    if(line[i]=='<'){
        i++;

        while(line[i]!='>')
            filename[j++]=line[i++];
        filename[j]='\0';
        strcpy(path,"C:/mingw64/mingw64/x86_64-w64-mingw32/include/");
        strcat(path,filename);
        fp=fopen(path,"r");
    }
    else{
        i++;

        while(line[i]!='"')
            filename[j++]=line[i++];

        filename[j]='\0';
        fp=fopen(filename,"r");
    }
    char *clean;
    int mode = 0;

    while(fgets(temp,1000,fp) != 0)
    {
        remove_comments(temp, &clean, &mode);
        fputs(clean, out);
        free(clean);
    }
    fclose(fp);
    return 0;
}
