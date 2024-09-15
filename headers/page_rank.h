#ifndef PAGE_RANK_H
#define PAGE_RANK_H

#include "forward_list.h"
#include "tst.h"
#include "pq.h"
#include <string.h>

typedef struct page_rank Page_Rank;

Page_Rank *page_rank_create();
ForwardList *page_rank_get_in(Page_Rank *pr);
ForwardList *page_rank_get_out(Page_Rank *pr);
int page_rank_size_in(Page_Rank *pr);
int page_rank_size_out(Page_Rank *pr);
void page_rank_insert_in(Page_Rank *pr, char *page);
void page_rank_insert_out(Page_Rank *pr, char *page);
double page_rank_get_val(Page_Rank *pr);
void page_rank_set_val(Page_Rank *pr, double val);
double page_rank_get_old_val(Page_Rank *pr);
void page_rank_set_old_val(Page_Rank *pr, double val);
void page_rank_destroy(Page_Rank *pr);

#endif