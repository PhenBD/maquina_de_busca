
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

static const int VECTOR_INIT_SIZE = 10;
static const int VECTOR_GROWTH_RATE = 2;

struct vector
{
    data_type *data;
    int size;
    int allocated;
    int (*ValueCompare_fn)(void *, void *);
    void (*ValueDestroy_fn)(void *);
};

Vector *vector_construct(int (*ValueCompare_fn)(void *, void *), void (*ValueDestroy_fn)(void *))
{
    Vector *v = (Vector *)calloc(1, sizeof(Vector));
    v->allocated = VECTOR_INIT_SIZE;
    v->size = 0;
    v->data = (data_type *)calloc(VECTOR_INIT_SIZE, sizeof(data_type));
    v->ValueCompare_fn = ValueCompare_fn;
    v->ValueDestroy_fn = ValueDestroy_fn;
    return v;
}

int vector_size(Vector *v)
{
    return v->size;
}

data_type vector_get(Vector *v, int i)
{
    if (i >= vector_size(v))
    {
        printf("Error: vector_get: invalid index %d for vector with size %d.\n", i, vector_size(v));
        exit(0);
    }

    return v->data[i];
}

void vector_set(Vector *v, int i, data_type val)
{
    if (i >= vector_size(v))
    {
        printf("Error: vector_set: invalid index %d for vector with size %d.\n", i, vector_size(v));
        exit(0);
    }

    v->data[i] = val;
}

void vector_push_back(Vector *v, data_type val)
{
    if (v->size >= v->allocated)
    {
        v->allocated *= VECTOR_GROWTH_RATE;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size++;
}

int vector_binary_search(Vector *v, data_type val)
{
    int left = 0;
    int right = v->size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (v->ValueCompare_fn(v->data[mid], val) == 0)
            return mid;
        else if (v->ValueCompare_fn(v->data[mid], val) > 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    return -1;
}

void vector_destroy(Vector *v)
{
    for (int i = 0; i < v->size; i++)
    {
        v->ValueDestroy_fn(v->data[i]);
    }
    free(v->data);
    free(v);
}
