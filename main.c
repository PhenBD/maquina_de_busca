#include <stdio.h>
#include <stdlib.h>
#include "headers/utils.h"
#include "headers/rank.h"
#include <time.h>

int main(int argc, char *argv[])
{
    clock_t start = clock();
    if(argc < 2)
		exit(printf("ERROR: Missing arguments!\n"));
    char *filename = argv[1];

    StringArray *index = list_index_pages(filename);
    printf("Index size: %d\n", string_array_size(index));
    TST *S = TST_create_stop_words(filename);
    printf("Stop words done.\n");
    TST *T = TST_create_words_table(filename, S, index);
    printf("Words table done.\n");
    TST *pr = TST_create_pr(filename, index);
    printf("Page rank done.\n");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
        ForwardList *search_words = get_search_words(line, T);

        ForwardList *same_pages = get_same_pages_from_search_words(search_words, T);

        Ranking *ranking_pages = ranking_create(forward_list_size(same_pages));

        for (int i = 0; i < forward_list_size(same_pages); i++)
        {
            String *s = forward_list_get(same_pages, i);
            Page_Rank *pr_node = TST_search(pr, s); 
            ranking_insert(ranking_pages, rank_create(s, page_rank_get_val(pr_node)));
        }
        ranking_sort(ranking_pages);

        print_search_words(search_words);
        print_ranking_pages(ranking_pages);

        ranking_destroy(ranking_pages);
        forward_list_destroy(search_words);
        forward_list_destroy(same_pages);
    }
    free(line);

    string_array_destroy(index);
    TST_destroy(S, TST_id_destroy);
    TST_destroy(T, TST_vector_string_destroy);
    TST_destroy(pr, TST_page_rank_destroy);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f\n", time_spent);
    return 0;
}
