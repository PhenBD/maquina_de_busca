#include "../headers/page_rank.h"

struct page_rank
{
    Vector *in, *out;
    double pr, pr_old;
};

int strings_compare_vector_in_out(void *a, void *b) {
    String *s1 = (String *)a;
    String *s2 = (String *)b;
    return strings_compare(s1, s2);
}

void strings_destroy_vector_in_out(void *s) {
    strings_destroy((String *)s);
}

Page_Rank *page_rank_create()
{
    Page_Rank *pr = (Page_Rank *)malloc(sizeof(Page_Rank));
    pr->in = vector_construct(strings_compare_vector_in_out, strings_destroy_vector_in_out);
    pr->out = vector_construct(strings_compare_vector_in_out, strings_destroy_vector_in_out);
    pr->pr = 0.0;

    return pr;
}

Vector *page_rank_get_in(Page_Rank *pr)
{
    return pr->in;
}

Vector *page_rank_get_out(Page_Rank *pr)
{
    return pr->out;
}

int page_rank_size_in(Page_Rank *pr)
{
    return vector_size(pr->in);
}

int page_rank_size_out(Page_Rank *pr)
{
    return vector_size(pr->out);
}

void page_rank_insert_in(Page_Rank *pr, String *page)
{
    vector_push_back(pr->in, page);
}

void page_rank_insert_out(Page_Rank *pr, String *page)
{
    vector_push_back(pr->out, page);
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
    vector_destroy(pr->in);
    vector_destroy(pr->out);
    free(pr);
}
