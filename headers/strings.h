#ifndef STRINGS_H
#define STRINGS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct string String;

String *strings_create(char *c);
char *strings_get_string(String *s);
char strings_get_char(String *s, int i);
int strings_get_len(String *s);
void strings_destroy(String *s);
String *strings_to_lower(String *s);

#endif