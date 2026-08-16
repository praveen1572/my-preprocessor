#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
typedef struct{
    char *name;
    char *replacement;
} Macro;
int remove_comments(char *line, char **clean, int *mode);
int store_macro(char *line, Macro **macros, int *count);
int find_macro(char *word, Macro *macros, int count);
int substitute_macro(char *line, Macro *macros, int count, char **output, int *size);
int header_inclusion(char *line, char **output, int *size, Macro **macros, int *count);
#endif