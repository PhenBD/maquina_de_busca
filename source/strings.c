#include "../headers/strings.h"

struct string
{
    char *c;
    int len;
};

struct string_array
{
    String **array;
    int len;
};

String *strings_create(char *c)
{
    String *s = (String *)malloc(sizeof(String));
    s->c = strdup(c);
    s->len = strlen(c);

    return s;
}

char *strings_get_string(String *s)
{
    return s->c;
}

char strings_get_char(String *s, int i)
{
    if (i >= s->len)
    {
        return '\0';
    }
    return s->c[i];
}

int strings_get_len(String *s)
{
    return s->len;
}

void strings_destroy(String *s)
{
    free(s->c);
    free(s);
}

String *strings_to_lower(String *s){
    for(int i = 0; s->c[i]; i++){
        s->c[i] = tolower(s->c[i]);
    }

    return s;
}

int strings_compare(void *a, void *b)
{
    String *s1 = (String *)a;
    String *s2 = (String *)b;

    return strcmp(s1->c, s2->c);
}

StringArray *string_array_create(int size)
{
    StringArray *sa = (StringArray *)malloc(sizeof(StringArray));
    sa->array = (String **)malloc(size * sizeof(String *));
    sa->len = 0;

    return sa;
}

void string_array_push_back(StringArray *sa, String *s)
{
    sa->array[sa->len] = s;
    sa->len++;
}

String *string_array_get(StringArray *sa, int i)
{
    return sa->array[i];
}

int string_array_size(StringArray *sa)
{
    return sa->len;
}

void string_array_destroy(StringArray *sa)
{
    for (int i = 0; i < sa->len; i++)
    {
        strings_destroy(sa->array[i]);
    }
    free(sa->array);
    free(sa);
}