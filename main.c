#include <stdio.h>
#include <stdlib.h>
#include "headers/tst.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
		exit(printf("ERROR: Missing arguments!\n"));

    char *filename = argv[1];
    TST *S = TST_create_stop_words(filename);
    TST *T = TST_create_words_table(filename, S);

    String *s = strings_create("reasons");
    if (TST_contains(T, s))
    {
        ForwardList *list = TST_search(T, s);
        for (int i = 0; i < forward_list_size(list); i++)
        {
            printf("%s %d\n", (char *)forward_list_get(list, i), i);
        }
    }
    strings_destroy(s);

    TST_destroy(S, TST_id_destroy);
    TST_destroy(T, TST_foward_list_destroy);
    return 0;
}
