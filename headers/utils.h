#ifndef UTILS_H
#define UTILS_H

#include "forward_list.h"
#include "tst.h"
#include "page_rank.h"
#include <sys/types.h>
#include <math.h>

#define DEBUG_MODE

void TST_id_destroy(void *id);
void TST_foward_list_string_destroy(void *list);
void TST_page_rank_destroy(void *pr);
int count_lines(const char *filename);
StringArray *list_index_pages(char *filename);
TST *TST_create_stop_words(char *filename);
TST *TST_create_words_table(char *filename, TST *stop_words, StringArray *index);
TST *TST_create_pr(char *filename, StringArray *index);
TST *TST_create_graph(char *filename, StringArray *index);
TST *page_ranking(TST *graph, char *filename, StringArray *index);

#endif