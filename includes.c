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

        while(line[i]!='>'&&line[i]!='\0')
            filename[j++]=line[i++];

        filename[j]='\0';

        if(strcmp(filename,"stdio.h")==0||
           strcmp(filename,"stdlib.h")==0||
           strcmp(filename,"string.h")==0){

            strcpy(path,
                   "C:/mingw64/mingw64/x86_64-w64-mingw32/include/");
            strcat(path,filename);

            fp=fopen(path,"r");
        }
        else
            return 0;
    }
    else{
        i++;

        while(line[i]!='"'&&line[i]!='\0')
            filename[j++]=line[i++];

        filename[j]='\0';

        fp=fopen(filename,"r");
    }

    while(fgets(temp,1000,fp)!=NULL)
        fputs(temp,out);

    fclose(fp);

    return 0;
}