#include "../headers/item.h"

struct item{
    int key;           // identificador do nó
    double value;     // valor associado ao nó
};

Item *item_create(int key, double value) {
    Item *t = malloc(sizeof(Item));
    t->key = key;
    t->value = value;
    
    return t;
}

int item_getKey(Item *i){
    return i->key;
}

double item_getValue(Item *i){
    return i->value;
}

void item_setValue(Item *i, double value){
    i->value = value;
}

int item_more(Item *a, Item *b){
    return a->value > b->value;
}

void item_exch(Item *a, Item *b){
    Item t = *a;
    *a = *b;
    *b = t;
}
