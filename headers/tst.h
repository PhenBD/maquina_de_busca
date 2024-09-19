#ifndef TST_H
#define TST_H

#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

#define Value void *

typedef struct node TST;

typedef void (*DestroyFunc)(void *);

/**
 * @brief Create a TST node
 * 
 * @return TST* 
 */
TST *TST_create_node();

/**
 * @brief Insert a key-value pair into the TST
 * 
 * @param t TST node
 * @param key key
 * @param val value
 * @return TST* 
 */
TST *TST_insert(TST *t, String *key , Value val);

/**
 * @brief Search for a key in the TST
 * 
 * @param t TST node
 * @param key key
 * @return Value 
 */
Value TST_search(TST* t, String* key);

/**
 * @brief Search for a key in the TST, if found return 1, otherwise return 0
 * 
 * @param t TST node
 * @param key key
 * @return 1 or 0 
 */
int TST_contains(TST *t, String *key);

/**
 * @brief Destroy a TST node
 * 
 * @param t TST node
 * @param destroy function to destroy the value
 */
void TST_destroy(TST *t, DestroyFunc destroy);

#endif
