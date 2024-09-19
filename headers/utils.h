#ifndef UTILS_H
#define UTILS_H

#include "forward_list.h"
#include "vector.h"
#include "tst.h"
#include "page_rank.h"
#include "rank.h"
#include <sys/types.h>
#include <math.h>

/**
 * @brief Destroy a TST node with an integer value
 * 
 * @param id 
 */
void TST_id_destroy(void *id);

/**
 * @brief Destroy a TST node with a ForwardList of String values
 * 
 * @param list 
 */
void TST_vector_string_destroy(void *list);

/**
 * @brief Destroy a TST node with a Page_Rank value
 * 
 * @param pr 
 */
void TST_page_rank_destroy(void *pr);

/**
 * @brief Count the number of lines in a file
 * 
 * @param filename 
 * @return number of lines 
 */
int count_lines(const char *filename);

/**
 * @brief List all pages in the index file
 * 
 * @param filename 
 * @return StringArray with all pages
 */
StringArray *list_index_pages(char *filename);

/**
 * @brief Create a TST with stop words from stopwords.txt
 * 
 * @param filename 
 * @return TST* 
 */
TST *TST_create_stop_words(char *filename);

/**
 * @brief Create a TST with words from all pages of the index
 * 
 * @param filename 
 * @param stop_words 
 * @param index 
 * @return TST* 
 */
TST *TST_create_words_table(char *filename, TST *stop_words, StringArray *index);

/**
 * @brief Create a TST with the page ranking
 * 
 * @param filename 
 * @param index 
 * @return TST* 
 */
TST *TST_create_pr(char *filename, StringArray *index);

/**
 * @brief Create a TST with the graph of pages from graph.txt
 * 
 * @param filename 
 * @param index 
 * @return TST* 
 */
TST *TST_create_graph(char *filename, StringArray *index);

/**
 * @brief Calculate the page ranking
 * 
 * @param graph
 * @param filename
 * @param index
 * @return TST* 
 */
TST *page_ranking(TST *graph, char *filename, StringArray *index);

/**
 * @brief Get the search words from a line
 * 
 * @param line 
 * @param T 
 * @return ForwardList* 
 */
ForwardList *get_search_words(char *line, TST *T);

/**
 * @brief Get the pages that contain all search words
 * 
 * @param search_words 
 * @param T 
 * @return ForwardList* 
 */
ForwardList *get_same_pages_from_search_words(ForwardList *search_words, TST *T);

/**
 * @brief Print the search words
 * 
 * @param search_words 
 */
void print_search_words(ForwardList *search_words);

/**
 * @brief Print the ranking of pages
 * 
 * @param ranking_pages 
 */
void print_ranking_pages(Ranking *ranking_pages);

#endif