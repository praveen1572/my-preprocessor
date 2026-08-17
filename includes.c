#include"myheader.h"

int header_inclusion(char *line, FILE *out)
{
    FILE *fp;
    char filename[100], temp[1000], *clean;
    int i = 0, j = 0, mode = 0;

    while(line[i] != '"' && line[i] != '<' && line[i] != '\0')
        i++;

    i++;

    while(line[i] != '"' && line[i] != '>' && line[i] != '\0')
        filename[j++] = line[i++];

    filename[j] = '\0';

    fp = fopen(filename, "r");

    while(fgets(temp, 1000, fp) != NULL)
    {
        remove_comments(temp, &clean, &mode);

        if(strncmp(clean, "#define", 7) == 0)
            store_macro(clean);

        else if(strncmp(clean, "#include", 8) == 0)
            header_inclusion(clean, out);

        else
            substitute_macro(clean, out);

        free(clean);
    }

    fclose(fp);

    return 0;
}