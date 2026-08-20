#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"
char *macro[100],*body[100];
int count=0,mode=0;
int main(int argc,char *argv[]){
    FILE *fp,*out;
    char *line,*clean,filename[100];
    int i;
    
    fp=fopen(argv[1],"r");
    strcpy(filename,argv[1]);
    i=strlen(filename);
    filename[i-1]='i';
    out=fopen(filename,"w");
    line=malloc(1000);

    while(fgets(line,1000,fp)!=0){
        remove_comments(line,&clean);
        if(strncmp(clean,"#define",7)==0)
            store_macro(clean);
        else if(strncmp(clean,"#include",8)==0)
            header_inclusion(clean,out);
        else
            substitute_macro(clean,out);
        free(clean);
    }
    fclose(fp);
    fclose(out);
    free(line);
    for(i=0;i<count;i++){
        free(macro[i]);
        free(body[i]);
    }
    return 0;
}
