#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"

int remove_comments(char *line,char **clean,int *mode){
    int i=0,index=0;
    int len=strlen(line);
    char *out=malloc(len+1);
    while(line[i]!='\0'){
        switch(*mode){
        case 0:
            if(line[i]=='/'&&line[i+1]=='/')
                while(line[i]!='\0'&&line[i]!='\n')
                    i++;
            else if(line[i]=='/'&&line[i+1]=='*'){
                *mode=1;
                i+=2;
            }
            else if(line[i]=='"'){
                out[index++]=line[i++];
                *mode=2;
            }
            else
                out[index++]=line[i++];
            break;
        case 1:
            if(line[i]=='*'&&line[i+1]=='/'){
                *mode=0;
                i+=2;
            }
            else{
                if(line[i]=='\n')
                    out[index++]='\n';
                i++;
            }
            break;
        case 2:
            out[index++]=line[i];
            if(line[i]=='"')
                *mode=0;
            i++;
            break;
        }
    }
    out[index]='\0';
    *clean=out;
    return 0;
}

