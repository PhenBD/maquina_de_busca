#ifndef UTILS_H
#define UTILS_H

#include "forward_list.h"
#include "tst.h"
#include "page_rank.h"
#include <sys/types.h>

void TST_id_destroy(void *id);
void TST_foward_list_destroy(void *list);
void TST_in_out_destroy(void *io);
int strings_compare(data_type data, void *key);
ForwardList *list_index_pages(char *filename);
TST *TST_create_stop_words(char *filename);
TST *TST_create_words_table(char *filename, TST *stop_words);
TST *TST_create_graph(char *filename);

#endif