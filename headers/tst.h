#ifndef TST_H
#define TST_H

#include <stdlib.h>
#include <stdio.h>
#include "strings.h"
#include "forward_list.h"
#include "utils.h"
#include <sys/types.h>

#define Value void *

typedef struct node TST;

typedef void (*DestroyFunc)(void *);

TST *TST_create_node();
TST *TST_insert(TST *t, String *key , Value val);
Value TST_search(TST* t, String* key);
int TST_contains(TST *t, String *key);
TST *TST_create_stop_words(char *filename);
TST *TST_create_words_table(char *filename, TST *stop_words);
void TST_destroy(TST *t, DestroyFunc destroy);

#endif
