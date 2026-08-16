#include <stdlib.h>
#include "preprocessor.h"

int remove_comments(char *line, char **clean, int *mode){
    int i = 0;
    int size = 0;
    int len = 0;
    char *out;
    while (line[len] != '\0')
        len++;
    out = malloc(len + 1);
    if (out == NULL)
        return -1;
    while (line[i] != '\0'){
        switch (*mode){
        
        case 0:
            if (line[i] == '/' && line[i + 1] == '/'){
                while (line[i] != '\0' && line[i] != '\n')
                    i++;
            }
            else if (line[i] == '/' && line[i + 1] == '*'){
                *mode = 1;
                i += 2;
            }
            else if (line[i] == '"'){
                out[size++] = line[i++];
                *mode = 2;
            }
            else if (line[i] == '\''){
                out[size++] = line[i++];
                *mode = 3;
            }
            else{
                out[size++] = line[i++];
            }
            break;

        case 1:
            if (line[i] == '*' && line[i + 1] == '/'){
                *mode = 0;
                i += 2;
            }
            else{
                if (line[i] == '\n')
                    out[size++] = '\n';
                i++;
            }
            break;

        case 2:
            out[size++] = line[i];
            if (line[i] == '\\' && line[i + 1] != '\0')
                out[size++] = line[++i];
            else if (line[i] == '"')
                *mode = 0;
            i++;
            break;

        case 3:
            out[size++] = line[i];
            if (line[i] == '\\' && line[i + 1] != '\0')
                out[size++] = line[++i];
            else if (line[i] == '\'')
                *mode = 0;
            i++;
            break;
        }
    }

    out[size] = '\0';
    *clean = out;
    return 0;
}
