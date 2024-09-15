#ifndef UTILS_H
#define UTILS_H

#include "forward_list.h"
#include "tst.h"
#include "page_rank.h"
#include <sys/types.h>
#include <math.h>

void TST_id_destroy(void *id);
void TST_foward_list_destroy(void *list);
void TST_page_rank_destroy(void *pr);
int strings_compare(data_type data, void *key);
ForwardList *list_index_pages(char *filename);
TST *TST_create_stop_words(char *filename);
TST *TST_create_words_table(char *filename, TST *stop_words);
TST *TST_create_pr(char *filename);
PQ *page_ranking(TST *pr, TST *T, ForwardList *search_words, char *filename);

#endif