#include <stdio.h>
#include <stdlib.h>
#include "headers/utils.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
		exit(printf("ERROR: Missing arguments!\n"));

    char *filename = argv[1];
    StringArray *index = list_index_pages(filename);
    TST *S = TST_create_stop_words(filename);
    TST *T = TST_create_words_table(filename, S, index);
    TST *pr = TST_create_pr(filename, index);

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
                forward_list_push_back(search_words, s);
            }
            
            token = strtok(NULL, delimit);
        }

        TST *set = NULL;
        ForwardList *same_pages = forward_list_construct();

        for (int i = 0; i < forward_list_size(search_words); i++)
        {
            String *sw = forward_list_get(search_words, i);
            ForwardList *pages = TST_search(T, sw);

            for (int j = 0; j < forward_list_size(pages); j++)
            {
                int *count = (int *)malloc(sizeof(int));
                *count = 0;

                String *page = forward_list_get(pages, j);
                
                if (!TST_contains(set, page))
                {
                    *count = 1;
                    set = TST_insert(set, page, count);
                }
                else
                {
                    int *aux = TST_search(set, page);
                    *aux += 1;
                    free(count);
                }
            }
        }

        for (int j = 0; j < string_array_size(index); j++)
        { 
            String *page = string_array_get(index, j);
            if (TST_contains(set, page))
            {
                int *count = TST_search(set, page);
                
                if (*count == forward_list_size(search_words))
                {
                    forward_list_push_back(same_pages, page);
                }
            }
        }
        TST_destroy(set, TST_id_destroy);

        PQ *rank_pages = PQ_create(forward_list_size(same_pages));

        for (int i = 0; i < forward_list_size(same_pages); i++)
        {
            String *s = forward_list_get(same_pages, i);
            Page_Rank *pr_node = TST_search(pr, s);
            Item *item = item_create(i, page_rank_get_val(pr_node));
            PQ_insert(rank_pages, item);
        }

        printf("search:");
        while (forward_list_size(search_words) >= 0)
        {   
            if(forward_list_size(search_words) == 0) { printf("\n"); break; }

            String *search_word = forward_list_pop_front(search_words);
            
            if(forward_list_size(search_words) != 0)
                printf("%s ", strings_get_string(search_word));
            else{
                printf("%s\n", strings_get_string(search_word));
                strings_destroy(search_word);
                break;
            }

            strings_destroy(search_word);
        }

        printf("pages:");
        while (forward_list_size(same_pages) >= 0)
        {   
            if(forward_list_size(same_pages) == 0) { printf("\n"); break; }

            String *same_page = forward_list_pop_front(same_pages);
            
            if(forward_list_size(same_pages) != 0)
                printf("%s ", strings_get_string(same_page));
            else{
                printf("%s\n", strings_get_string(same_page));
                break;
            }
        }

        printf("pr:");
        while (PQ_size(rank_pages) >= 0)
        {
            if(PQ_size(rank_pages) == 0) { printf("\n"); break; }

            Item *item = PQ_delmax(rank_pages);
            
            if (PQ_size(rank_pages) != 0)
                printf("%.17lf ", item_getValue(item));
            else{
                printf("%.17lf\n", item_getValue(item));
                free(item);
                break;
            }
            free(item);
        }

        forward_list_destroy(search_words);
        forward_list_destroy(same_pages);
        PQ_destroy(rank_pages);
    }

    free(line);

    string_array_destroy(index);
    TST_destroy(S, TST_id_destroy);
    TST_destroy(T, TST_foward_list_string_destroy);
    TST_destroy(pr, TST_page_rank_destroy);

    return 0;
}
