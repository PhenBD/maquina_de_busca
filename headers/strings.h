#ifndef STRINGS_H
#define STRINGS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct string String;
typedef struct string_array StringArray;

String *strings_create(char *c);
char *strings_get_string(String *s);
char strings_get_char(String *s, int i);
int strings_get_len(String *s);
void strings_destroy(String *s);
String *strings_to_lower(String *s);
int strings_compare(void *a, void *b);

StringArray *string_array_create(int size);
void string_array_push_back(StringArray *sa, String *s);
String *string_array_get(StringArray *sa, int i);
int string_array_size(StringArray *sa);
void string_array_destroy(StringArray *sa);

#endif