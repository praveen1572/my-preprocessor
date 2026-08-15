#include <stdio.h>
#include <stdlib.h>
#include "preprocessor.h"
int main(int argc, char *argv[])
{
    FILE *fp;
    FILE *out;
    char *line;
    char *clean;
    char *output;
    char filename[100];
    Macro *macros = NULL;
    int count = 0;
    int size = 0;
    int mode = 0;
    int i;
    if (argc != 2)
    {
        printf("Usage: %s <input.c>\n", argv[0]);
        return 1;
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Unable to open input file\n");
        return 1;
    }
    output = malloc(1);
    if (output == NULL)
    {
        fclose(fp);
        return 1;
    }
    output[0] = '\0';
    line = malloc(1000);
    if (line == NULL)
    {
        free(output);
        fclose(fp);
        return 1;
    }
    while (fgets(line, 1000, fp) != NULL)
    {
        if (remove_comments(line, &clean, &mode) != 0)
            break;
        if (clean[0] == '#' && clean[1] == 'd' && clean[2] == 'e' &&
            clean[3] == 'f' && clean[4] == 'i' && clean[5] == 'n' &&
            clean[6] == 'e')
        {
            if (store_macro(clean, &macros, &count) != 0)
                break;
        }
        else if (clean[0] == '#' && clean[1] == 'i' && clean[2] == 'n' &&
                 clean[3] == 'c' && clean[4] == 'l' && clean[5] == 'u' &&
                 clean[6] == 'd' && clean[7] == 'e')
        {
            if (header_inclusion(clean, &output, &size, &macros, &count) != 0)
                break;
        }
        else
        {
            if (substitute_macro(clean, macros, count, &output, &size) != 0)
                break;
        }
        free(clean);
    }
    fclose(fp);
    free(line);
    i = 0;
    while (argv[1][i] != '\0' && i < 99)
    {
        filename[i] = argv[1][i];
        i++;
    }
    filename[i] = '\0';
    if (i > 1 && filename[i - 2] == '.' && filename[i - 1] == 'c')
        filename[i - 1] = 'i';
    else
    {
        filename[i++] = '.';
        filename[i++] = 'i';
        filename[i] = '\0';
    }
    out = fopen(filename, "w");
    if (out == NULL)
    {
        free(output);
        for (i = 0; i < count; i++)
        {
            free(macros[i].name);
            free(macros[i].replacement);
        }
        free(macros);
        return 1;
    }
    fputs(output, out);
    fclose(out);
    free(output);
    for (i = 0; i < count; i++)
    {
        free(macros[i].name);
        free(macros[i].replacement);
    }
    free(macros);
    return 0;
}
