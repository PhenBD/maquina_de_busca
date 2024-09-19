#ifndef PAGE_RANK_H
#define PAGE_RANK_H

#include "vector.h"
#include "tst.h"
#include "strings.h"

typedef struct page_rank Page_Rank;

/**
 * @brief Construct a new Page Rank object
 * 
 * @return Pointer to the newly allocated page rank.
 */
Page_Rank *page_rank_create();

/**
 * @brief Get the list of pages that point to the page.
 * 
 * @param pr Pointer to the page rank.
 * @return Pointer to the list of pages that point to the page.
 */
Vector *page_rank_get_in(Page_Rank *pr);

/**
 * @brief Retrieves the outgoing links of a page rank.
 * 
 * @param pr Pointer to the page rank.
 * @return Pointer to a Vector containing the outgoing links.
 */
Vector *page_rank_get_out(Page_Rank *pr);

/**
 * @brief Gets the number of incoming links to a page.
 * 
 * @param pr Pointer to the page rank.
 * @return Number of incoming links.
 */
int page_rank_size_in(Page_Rank *pr);

/** 
 * @brief Gets the number of outgoing links from a page.
 * 
 * @param pr Pointer to the page rank.
 * @return Number of outgoing links.
 */
int page_rank_size_out(Page_Rank *pr);

/** 
 * @brief Inserts an incoming link to a page.
 * 
 * @param pr Pointer to the page rank.
 * @param page Pointer to the name of page to be inserted.
 */
void page_rank_insert_in(Page_Rank *pr, String *page);

/**
 * @brief Inserts an outgoing link from a page rank.
 * 
 * @param pr Pointer to the page rank.
 * @param page Pointer to the name of page to be inserted.
 */
void page_rank_insert_out(Page_Rank *pr, String *page);

/**
 * @brief Retrieves the current value of the page rank.
 * 
 * @param pr Pointer to the page rank.
 * @return Current value of the page rank.
 */
double page_rank_get_val(Page_Rank *pr);

/**
 * @brief Sets the current value of the page rank.
 * 
 * @param pr Pointer to the page rank.
 * @param val New value to be set.
 */
void page_rank_set_val(Page_Rank *pr, double val);

/**
 * @brief Retrieves the old value of the page rank.
 * 
 * @param pr Pointer to the page rank.
 * @return Old value of the page rank.
 */
double page_rank_get_old_val(Page_Rank *pr);

/**
 * @brief Sets the old value of the page rank.
 * 
 * @param pr Pointer to the page rank.
 * @param val New old value to be set.
 */
void page_rank_set_old_val(Page_Rank *pr, double val);

/**
 * @brief Destroys the page rank and frees associated memory.
 * 
 * @param pr Pointer to the page rank to be destroyed.
 */
void page_rank_destroy(Page_Rank *pr);

#endif