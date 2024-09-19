#include "../headers/page_rank.h"

struct page_rank
{
    ForwardList *in, *out;
    double pr, pr_old;
};

Page_Rank *page_rank_create()
{
    Page_Rank *pr = (Page_Rank *)malloc(sizeof(Page_Rank));
    pr->in = forward_list_construct();
    pr->out = forward_list_construct();
    pr->pr = 0.0;

    return pr;
}

ForwardList *page_rank_get_in(Page_Rank *pr)
{
    return pr->in;
}

ForwardList *page_rank_get_out(Page_Rank *pr)
{
    return pr->out;
}

int page_rank_size_in(Page_Rank *pr)
{
    return forward_list_size(pr->in);
}

int page_rank_size_out(Page_Rank *pr)
{
    return forward_list_size(pr->out);
}

void page_rank_insert_in(Page_Rank *pr, char *page)
{
    forward_list_push_back(pr->in, strdup(page));
}

void page_rank_insert_out(Page_Rank *pr, char *page)
{
    forward_list_push_back(pr->out, strdup(page));
}

double page_rank_get_val(Page_Rank *pr)
{
    return pr->pr;
}

void page_rank_set_val(Page_Rank *pr, double val)
{
    pr->pr_old = pr->pr;
    pr->pr = val;
}

double page_rank_get_old_val(Page_Rank *pr)
{
    return pr->pr_old;
}

void page_rank_set_old_val(Page_Rank *pr, double val)
{
    pr->pr_old = val;
}

void page_rank_destroy(Page_Rank *pr)
{
    while (forward_list_size(pr->in) > 0)
    {
        free(forward_list_pop_front(pr->in));
    }
    forward_list_destroy(pr->in);
    
    while (forward_list_size(pr->out) > 0)
    {
        free(forward_list_pop_front(pr->out));
    }
    forward_list_destroy(pr->out);

    free(pr);
}
