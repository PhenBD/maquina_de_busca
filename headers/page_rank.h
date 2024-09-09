#ifndef PAGE_RABK_H
#define PAGE_RABK_H

#include "forward_list.h"
#include <string.h>

typedef struct in_out In_Out;

In_Out *in_out_create();
void in_insert(In_Out *io, char *page);
void out_insert(In_Out *io, char *page);
void in_out_destroy(In_Out *io);

#endif