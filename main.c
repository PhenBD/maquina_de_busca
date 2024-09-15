#include <stdio.h>
#include <stdlib.h>
#include "headers/utils.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
		exit(printf("ERROR: Missing arguments!\n"));

    char *filename = argv[1];
    TST *S = TST_create_stop_words(filename);
    TST *T = TST_create_words_table(filename, S);
    TST *pr = TST_create_pr(filename);

    char *line = NULL;
    char delimit[] = " \t\n";

    size_t len = 0;
    ssize_t read;

    ForwardList *search_words = forward_list_construct();

    while ((read = getline(&line, &len, stdin)) != -1) {
        char *token = strtok(line, delimit);
        while (token != NULL) {
            if (token == NULL) { continue; }

            String *s = strings_create(token);
            strings_to_lower(s);
            
            if (!TST_contains(S, s))
            {
                forward_list_push_back(search_words, s);
            }
            
            token = strtok(NULL, delimit);
        }

        PQ *rank_pages = page_ranking(pr, T, search_words, filename);
        
        while (!PQ_empty(rank_pages))
        {
            Item *item = PQ_delmax(rank_pages);
            printf("%d %f\n", item_getKey(item), item_getValue(item));
            free(item);
        }

        PQ_destroy(rank_pages);
    }
    free(line);
    forward_list_destroy(search_words);
    TST_destroy(S, TST_id_destroy);
    TST_destroy(T, TST_foward_list_destroy);
    TST_destroy(pr, TST_page_rank_destroy);

    return 0;
}
