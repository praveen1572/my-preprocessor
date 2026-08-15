#include <stdio.h>
#include <stdlib.h>
#include "preprocessor.h"
int find_macro(char *word, Macro *macros, int count)
{
    int i;
    int j;
    for (i = 0; i < count; i++)
    {
        j = 0;
        while (word[j] != '\0' && word[j] == macros[i].name[j])
            j++;
        if (word[j] == '\0' && macros[i].name[j] == '\0')
            return i;
    }
    return -1;
}
int store_macro(char *line, Macro **macros, int *count)
{
    char name[50];
    char value[200];
    Macro *temp;
    int i = 7;
    int j = 0;
    int k = 0;
    while (line[i] == ' ')
        i++;
    while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
        name[j++] = line[i++];
    name[j] = '\0';
    while (line[i] == ' ')
        i++;
    while (line[i] != '\n' && line[i] != '\0')
        value[k++] = line[i++];
    value[k] = '\0';
    temp = realloc(*macros, (*count + 1) * sizeof(Macro));
    if (temp == NULL)
        return -1;
    *macros = temp;
    (*macros)[*count].name = malloc(j + 1);
    (*macros)[*count].replacement = malloc(k + 1);
    if ((*macros)[*count].name == NULL ||
        (*macros)[*count].replacement == NULL)
        return -1;
    for (i = 0; i <= j; i++)
        (*macros)[*count].name[i] = name[i];
    for (i = 0; i <= k; i++)
        (*macros)[*count].replacement[i] = value[i];
    (*count)++;
    return 0;
}
int substitute_macro(char *line, Macro *macros, int count, char **output, int *size)
{
    int i = 0;
    int j;
    int k;
    int found;
    int len;
    int depth;
    char word[100];
    char *replacement;
    char *temp;
    while (line[i] != '\0')
    {
        if (line[i] == '"' || line[i] == '\'')
        {
            char quote = line[i++];
            temp = realloc(*output, *size + 2);
            if (temp == NULL)
                return -1;
            *output = temp;
            (*output)[(*size)++] = quote;
            while (line[i] != '\0')
            {
                temp = realloc(*output, *size + 2);
                if (temp == NULL)
                    return -1;
                *output = temp;
                (*output)[(*size)++] = line[i];
                if (line[i] == '\\' && line[i + 1] != '\0')
                {
                    i++;
                    temp = realloc(*output, *size + 2);
                    if (temp == NULL)
                        return -1;
                    *output = temp;
                    (*output)[(*size)++] = line[i];
                }
                else if (line[i] == quote)
                {
                    i++;
                    break;
                }
                i++;
            }
            (*output)[*size] = '\0';
        }
        else if ((line[i] >= 'A' && line[i] <= 'Z') ||
                 (line[i] >= 'a' && line[i] <= 'z') ||
                 line[i] == '_')
        {
            j = 0;
            while ((line[i] >= 'A' && line[i] <= 'Z') ||
                   (line[i] >= 'a' && line[i] <= 'z') ||
                   (line[i] >= '0' && line[i] <= '9') ||
                   line[i] == '_')
                word[j++] = line[i++];
            word[j] = '\0';
            replacement = word;
            depth = 0;
            while (depth < 20)
            {
                found = find_macro(replacement, macros, count);
                if (found == -1)
                    break;
                replacement = macros[found].replacement;
                depth++;
            }
            len = 0;
            while (replacement[len] != '\0')
                len++;
            temp = realloc(*output, *size + len + 1);
            if (temp == NULL)
                return -1;
            *output = temp;
            for (k = 0; k < len; k++)
                (*output)[*size + k] = replacement[k];
            *size += len;
            (*output)[*size] = '\0';
        }
        else
        {
            temp = realloc(*output, *size + 2);
            if (temp == NULL)
                return -1;
            *output = temp;
            (*output)[(*size)++] = line[i++];
            (*output)[*size] = '\0';
        }
    }
    return 0;
}
