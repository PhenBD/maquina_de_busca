#ifndef UTILS_H
#define UTILS_H

#include "forward_list.h"
#include "strings.h"
#include <stdlib.h>
#include <sys/types.h>

void TST_id_destroy(void *id);
void TST_foward_list_destroy(void *list);
int strings_compare(data_type data, void *key);
ForwardList *list_index_pages(char *filename);

#endif