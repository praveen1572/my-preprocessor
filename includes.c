#include <stdio.h>
#include <stdlib.h>
#include "preprocessor.h"

int header_inclusion(char *line, char **output, int *size, Macro **macros, int *count)
{
    FILE *fp;
    char filename[100];
    char *start;
    char *end;
    char *header;
    char *clean;
    char *temp;
    char buffer[1000];
    long header_size;
    int name_size;
    int i;
    int len;
    int mode = 0;

    start = line;

    while (*start != '"' && *start != '<' && *start != '\0')
        start++;

    if (*start == '\0')
        return -1;

    start++;
    end = start;

    while (*end != '"' && *end != '>' && *end != '\0')
        end++;

    if (*end == '\0')
        return -1;

    name_size = end - start;

    if (name_size >= 100)
        return -1;

    for (i = 0; i < name_size; i++)
        filename[i] = start[i];

    filename[name_size] = '\0';

    fp = fopen(filename, "r");

    if (fp == NULL)
        return -1;

    fseek(fp, 0, SEEK_END);
    header_size = ftell(fp);
    rewind(fp);

    if (header_size < 0)
    {
        fclose(fp);
        return -1;
    }

    header = malloc(header_size + 1);

    if (header == NULL)
    {
        fclose(fp);
        return -1;
    }

    if (fread(header, 1, header_size, fp) != (size_t)header_size)
    {
        free(header);
        fclose(fp);
        return -1;
    }

    header[header_size] = '\0';
    fclose(fp);

    i = 0;

    while (i < header_size)
    {
        len = 0;

        while (header[i + len] != '\n' && header[i + len] != '\0')
            len++;

        if (len >= 999)
        {
            free(header);
            return -1;
        }

        for (int j = 0; j < len; j++)
            buffer[j] = header[i + j];

        buffer[len] = '\0';

        if (remove_comments(buffer, &clean, &mode) != 0)
        {
            free(header);
            return -1;
        }

        if (clean[0] == '#' && clean[1] == 'd' && clean[2] == 'e' &&
            clean[3] == 'f' && clean[4] == 'i' && clean[5] == 'n' &&
            clean[6] == 'e')
        {
            if (store_macro(clean, macros, count) != 0)
            {
                free(clean);
                free(header);
                return -1;
            }
        }
        else if (clean[0] == '#' && clean[1] == 'i' && clean[2] == 'n' &&
                 clean[3] == 'c' && clean[4] == 'l' && clean[5] == 'u' &&
                 clean[6] == 'd' && clean[7] == 'e')
        {
            if (header_inclusion(clean, output, size, macros, count) != 0)
            {
                free(clean);
                free(header);
                return -1;
            }
        }
        else
        {
            if (substitute_macro(clean, *macros, *count, output, size) != 0)
            {
                free(clean);
                free(header);
                return -1;
            }

            temp = realloc(*output, *size + 2);

            if (temp == NULL)
            {
                free(clean);
                free(header);
                return -1;
            }

            *output = temp;
            (*output)[(*size)++] = '\n';
            (*output)[*size] = '\0';
        }

        free(clean);

        i += len;

        if (header[i] == '\n')
            i++;
    }

    free(header);

    return 0;
}
