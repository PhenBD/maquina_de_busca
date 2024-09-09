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
    TST *graph = TST_create_graph(filename);

    TST_destroy(S, TST_id_destroy);
    TST_destroy(T, TST_foward_list_destroy);
    TST_destroy(graph, TST_in_out_destroy);

    return 0;
}
