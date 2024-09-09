#include "../headers/page_rank.h"

struct in_out
{
    ForwardList *in, *out;
};

In_Out *in_out_create()
{
    In_Out *io = (In_Out *)malloc(sizeof(In_Out));
    io->in = forward_list_construct();
    io->out = forward_list_construct();

    return io;
}

void in_insert(In_Out *io, char *page)
{
    forward_list_push_back(io->in, strdup(page));
}

void out_insert(In_Out *io, char *page)
{
    forward_list_push_back(io->out, strdup(page));
}

void in_out_destroy(In_Out *io)
{
    while (forward_list_size(io->in) > 0)
    {
        free(forward_list_pop_front(io->in));
    }
    forward_list_destroy(io->in);
    
    while (forward_list_size(io->out) > 0)
    {
        free(forward_list_pop_front(io->out));
    }
    forward_list_destroy(io->out);

    free(io);
}