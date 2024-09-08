#include "../headers/strings.h"

struct string
{
    char *c;
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