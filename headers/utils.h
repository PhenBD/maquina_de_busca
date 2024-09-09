#ifndef UTILS_H
#define UTILS_H

#include "forward_list.h"
#include "tst.h"
#include <sys/types.h>

void TST_id_destroy(void *id);
void TST_foward_list_destroy(void *list);
int strings_compare(data_type data, void *key);
ForwardList *list_index_pages(char *filename);
TST *TST_create_stop_words(char *filename);
TST *TST_create_words_table(char *filename, TST *stop_words);

#endif