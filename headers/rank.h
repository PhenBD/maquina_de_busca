#ifndef RANK_H
#define RANK_H

#include <stdlib.h>
#include "strings.h"

typedef struct rank Rank;

typedef struct ranking Ranking;

// Rank

/**
 * @brief Create a Rank object
 * 
 * @param name name associated with the rank
 * @param value value of the rank
 */
Rank *rank_create(String *name, double value);

/**
 * @brief Get the name of the rank
 * 
 * @param r rank object
 * @return name of the rank
 */
String *rank_get_name(Rank *r);

/**
 * @brief Get the value of the rank
 * 
 * @param r rank object
 * @return value of the rank
 */
double rank_get_value(Rank *r);

/**
 * @brief Set the value of the rank
 * 
 * @param r rank object
 * @param value value of the rank
 */
void rank_set_value(Rank *r, double value);

/**
 * @brief Compare two ranks by the highest value first, then by name alphabetically
 * 
 * @param a rank A
 * @param b rank B
 * @return 1, -1 or strcmp(name A, name B)
 */
int rank_compare(const void *a, const void *b);

/**
 * @brief Destroy a rank object
 * 
 * @param r rank object
 */
void rank_destroy(Rank *r);

// Ranking

/**
 * @brief Create a Ranking object
 * 
 * @param capacity capacity of the ranking
 * @return Ranking object
 */
Ranking *ranking_create(int capacity);

/**
 * @brief Insert a rank into the ranking
 * 
 * @param r ranking object
 * @param item rank object
 */
void ranking_insert(Ranking *r, Rank *item);

/**
 * @brief Get the rank at the i-th position
 * 
 * @param r ranking object
 * @param i position
 * @return rank object
 */
Rank *ranking_get(Ranking *r, int i);

/**
 * @brief Get the size of the ranking
 * 
 * @param r ranking object
 * @return size of the ranking
 */
int ranking_size(Ranking *r);

/**
 * @brief Sort the ranking by the highest value first, then by name alphabetically
 * 
 * @param r ranking object
 */
void ranking_sort(Ranking *r);

/**
 * @brief Destroy a ranking object
 * 
 * @param r ranking object
 */
void ranking_destroy(Ranking *r);

#endif
