#include <stdio.h>
#include <stdlib.h>
#include "headers/utils.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
		exit(printf("ERROR: Missing arguments!\n"));

    char *filename = argv[1];
    ForwardList *pages = list_index_pages(filename);
    TST *S = TST_create_stop_words(filename);
    TST *T = TST_create_words_table(filename, S);
    TST *pr = TST_create_pr(filename);

    char *line = NULL;
    char delimit[] = " \t\n";

    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
        ForwardList *search_words = forward_list_construct();

        char *token = strtok(line, delimit);
        while (token != NULL) {
            if (token == NULL) { continue; }

            String *s = strings_create(token);
            strings_to_lower(s);
            
            if (TST_contains(T, s))
            {
                // printf("word: %s\n", strings_get_string(s));
                forward_list_push_back(search_words, s);
            }
            
            token = strtok(NULL, delimit);
            strings_destroy(s);
        }

        ForwardList *same_pages = forward_list_construct();

        for (int i = 0; i < forward_list_size(search_words); i++)
        {
            String *s = forward_list_get(search_words, i);
            // printf("word: %s\n", strings_get_string(s));

            ForwardList *pages = TST_search(T, s);

            TST *set = NULL;

            int *id = (int *)malloc(sizeof(int));
            *id = 0;

            for (int j = 0; j < forward_list_size(pages); j++)
            {
                char *page = forward_list_get(pages, j);
                String *s = strings_create(page);
                
                if (!TST_contains(set, s))
                {
                    set = TST_insert(set, s, id);
                    *id += 1;
                }
                else
                {
                    forward_list_push_back(same_pages, s);
                }
            }
            
            TST_destroy(set, TST_id_destroy);
        }

        PQ *rank_pages = PQ_create(forward_list_size(same_pages));

        for (int i = 0; i < forward_list_size(same_pages); i++)
        {
            String *s = forward_list_get(same_pages, i);
            Page_Rank *pr_node = TST_search(pr, s);
            Item *item = item_create(i, page_rank_get_val(pr_node));
            PQ_insert(rank_pages, item);
        }

        while (!PQ_empty(rank_pages))
        {
            Item *item = PQ_delmax(rank_pages);
            printf("%d %f\n", item_getKey(item), item_getValue(item));
            free(item);
        }

        while (forward_list_size(search_words) > 0)
        {
            strings_destroy(forward_list_pop_front(search_words));
        }
        forward_list_destroy(search_words);
        PQ_destroy(rank_pages);
    }

    free(line);
    while (forward_list_size(pages) > 0)
    {
        free(forward_list_pop_front(pages));
    }
    forward_list_destroy(pages);
    TST_destroy(S, TST_id_destroy);
    TST_destroy(T, TST_foward_list_destroy);
    TST_destroy(pr, TST_page_rank_destroy);

    return 0;
}
