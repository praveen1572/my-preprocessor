#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"

int store_macro(char *line){
    int i=8,j=0,k=0;

    macro[count]=malloc(50);
    body[count]=malloc(50);

    while(line[i]!=' ')
        macro[count][j++]=line[i++];
    macro[count][j]='\0';
    
    i++;

    while(line[i]!='\n'&&line[i]!='\0')
        body[count][k++]=line[i++];
    body[count][k]='\0';

    count++;
    return 0;
}

int substitute_macro(char *line,FILE *out){
    int i=0,j,k;
    char temp[100];

    while(line[i]!='\0'){
        if((line[i]>='A'&&line[i]<='Z')||(line[i]>='a'&&line[i]<='z')||line[i]=='_'){

            j=0;

            while((line[i]>='A'&&line[i]<='Z')||(line[i]>='a'&&line[i]<='z')||(line[i]>='0'&&line[i]<='9')||line[i]=='_')
                temp[j++]=line[i++];

            temp[j]='\0';

            for(k=0;k<count;k++){
                if(strcmp(temp,macro[k])==0)
                    break;
            }

            if(k<count)
                fputs(body[k],out);
            else
                fputs(temp,out);
        }
        else{
            fputc(line[i],out);
            i++;
        }
    }

    return 0;
}