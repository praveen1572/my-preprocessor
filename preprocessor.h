#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stdio.h>

extern char *macro[100];
extern char *body[100];
extern int count;

int remove_comments(char *line,char **clean,int *mode);
int store_macro(char *line);
int substitute_macro(char *line,FILE *out);
int header_inclusion(char *line,FILE *out);

#endif