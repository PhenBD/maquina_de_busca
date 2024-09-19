#include "../headers/rank.h"

struct rank{
    String *name;           
    double value;     
};

struct ranking
{
    Rank **ranks;
    int size;
    int capacity;
};

Rank *rank_create(String *name, double value) {
    Rank *r = malloc(sizeof(Rank));
    r->name = name;
    r->value = value;
    return r;
}

String *rank_get_name(Rank *r){
    return r->name;
}

double rank_get_value(Rank *r){
    return r->value;
}

void rank_set_value(Rank *r, double value){
    r->value = value;
}

int rank_compare(const void *a, const void *b){
    Rank *rankA = *(Rank **)a;
    Rank *rankB = *(Rank **)b;
    if (rankA->value < rankB->value) return 1;
    if (rankA->value > rankB->value) return -1;
    if (rankA->value == rankB->value) return strcmp(strings_get(rankA->name), strings_get(rankB->name));
}

void rank_destroy(Rank *r){
    // strings_destroy(r->name);
    free(r);
}

Ranking *ranking_create(int capacity){
    Ranking *r = malloc(sizeof(Ranking));
    r->ranks = malloc(capacity * sizeof(Rank *));
    r->size = 0;
    r->capacity = capacity;
    return r;
}

void ranking_insert(Ranking *r, Rank *item){
    r->ranks[r->size] = item;
    r->size++;
}

Rank *ranking_get(Ranking *r, int i){
    return r->ranks[i];
}

int ranking_size(Ranking *r){
    return r->size;
}

void ranking_sort(Ranking *r){
    qsort(r->ranks, r->size, sizeof(Rank *), rank_compare);
}

void ranking_destroy(Ranking *r){
    for (int i = 0; i < r->size; i++)
    {
        rank_destroy(r->ranks[i]);
    }
    free(r->ranks);
    free(r);
}
