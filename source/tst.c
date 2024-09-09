#include "../headers/tst.h"

struct node 
{
    Value *val;
    unsigned char c;
    TST *l, *m, *r;
};

TST *TST_create_node() {
    TST *t = (TST *)malloc(sizeof(TST));
    t->val = NULL;
    t->l = t->m = t->r = NULL;
    return t;
}

TST *rec_insert(TST *t, String *key, Value val, int d) {
    unsigned char c = strings_get_char(key, d);
    if (t == NULL) { t = TST_create_node(); t->c = c;}
    if      (c < t->c) { t->l = rec_insert(t->l, key, val, d); }
    else if (c > t->c) { t->r = rec_insert(t->r, key, val, d); }
    else if (d < strings_get_len(key) - 1) {
        t->m = rec_insert(t->m, key, val, d+1);
    } else { t->val = val;  }
    return t;
}

TST *TST_insert(TST *t, String *key , Value val) {
    return rec_insert(t, key, val, 0);
}

TST* rec_search(TST* t, String* key, int d) {
    if (t == NULL) { return NULL; }
    unsigned char c = strings_get_char(key, d);
    if      (c < t->c) { return rec_search(t->l, key, d); }
    else if (c > t->c) { return rec_search(t->r, key, d); }
    else if (d < strings_get_len(key) - 1) {
        return rec_search(t->m, key, d+1);
    } else { return t; }
}

Value TST_search(TST* t, String* key) {
    t = rec_search(t, key, 0);
    if (t == NULL) { return NULL; }
    else { return t->val; }
}

int TST_contains(TST *t, String *key) {
    return TST_search(t, key) != NULL;
}

void TST_destroy(TST *t, DestroyFunc destroy) {
    if (t == NULL) { return; }

    TST_destroy(t->l, destroy);
    TST_destroy(t->m, destroy);
    TST_destroy(t->r, destroy);
    
    
    if (t->val != NULL) { destroy(t->val); }
    
    free(t);
}


