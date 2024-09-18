
#include "forward_list.h"

struct node
{
    data_type value;
    struct node *next;
};

struct forwardList
{
    Node *head;
    Node *last;
    int size;
};

struct listIterator
{
    Node *current;
};

Node *node_construct(data_type value, Node *next){
    Node *n = (Node *)malloc(sizeof(Node));
    n->value = value;
    n->next = next;

    return n;
}

void node_destroy(Node *n){
    free(n);
}

ForwardList *forward_list_construct(){
    ForwardList *list = (ForwardList *)malloc(sizeof(ForwardList));

    list->head = NULL;
    list->last = NULL;
    list->size = 0;

    return list;
}

int forward_list_size(ForwardList *l){
    return l->size;
}

data_type forward_list_find(ForwardList *l, void *key, int (*cmp_fn)(data_type data, void *key))
{
    Node *n = l->head;

    while (n != NULL)
    {
        if (!cmp_fn(n->value, key))
            return n->value;

        n = n->next;
    }

    return NULL;
}

void forward_list_push_front(ForwardList *l, data_type data){
    Node *novo = node_construct(data, l->head);

    if (l->size == 0)
    {
        l->last = l->head = novo;
    }
    else
    {
        l->head = novo;
    }

    l->size++;
}

void forward_list_push_back(ForwardList *l, data_type data){
    Node *novo = node_construct(data, NULL);
    
    if (l->last == NULL)
    {
        l->head = l->last = novo;
    }
    else
    {
        l->last = l->last->next = novo;
    }

    l->size++;
}

void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){
    Node *nAux = l->head;

    printf("[");
    while (nAux != NULL)
    {
        print_fn(nAux->value);

        if (nAux->next ==  NULL)
            break;
        
        printf(", ");

        nAux = nAux->next;
    }
    printf("]");
}

data_type forward_list_get(ForwardList *l, int i){
    Node *n = l->head;

    if (i < 0 || i > l->size)
    {
        printf("Indice invalido!\n");
        return (data_type)-1;
    }   
    
    for (int j = 0; j < i; j++)
    {
        n = n->next;
    }

    return n->value;
}

data_type forward_list_pop_front(ForwardList *l){
    if (l->head == NULL)
        exit(printf("Error: lista está vazia."));

    Node *n = l->head;

    l->head = l->head->next;

    data_type data = n->value;

    node_destroy(n);

    l->size--;

    if (l->size <= 1)
        l->last = l->head;

    return data;
}

ForwardList *forward_list_reverse(ForwardList *l){
    ForwardList *l2 = forward_list_construct();
    Node *n = l->head;
    
    for (int i = 0; i < forward_list_size(l); i++)
    {
        forward_list_push_front(l2, n->value);
        n = n->next;
    }

    return l2;
}

void forward_list_clear(ForwardList *l, void (*destroy_fn)(void *)){
    int size = l->size;
    if(destroy_fn == NULL) exit(printf("FORWARD LIST CLEAR ERROR: Cannot free items without destroy function\n")); 
    else for (int i = 0; i < size; i++) if(destroy_fn != NULL) destroy_fn((void *)forward_list_pop_front(l));
}

void forward_list_remove(ForwardList *l, data_type val){
    Node *n = l->head, *nAux = NULL;
    int cont = 0;

    for (int i = 0; i < forward_list_size(l); i++)
    {
        if (n == l->head)
        {
            if (n->value == val)
            {
                l->head = l->head->next;
                node_destroy(n);
                n = l->head;
                cont++;
            }
            else
            {
                nAux = n;
                n = n->next;
            }
        }
        else
        {
            if (n->value == val)
            {
                nAux->next = n->next;
                node_destroy(n);
                n = nAux->next;
                cont++;
            }
            else 
            {
                n = n->next;
                nAux = nAux->next;
            }
        }
    }

    l->size -= cont;
}

void forward_list_cat(ForwardList *l, ForwardList *m){
    Node *n = m->head;

    while (n)
    {
        forward_list_push_front(l, n->value);
        n = n->next;
    }
}

void forward_list_destroy(ForwardList *l){
    Node *next = l->head;

    while (next != NULL)
    {
        next = l->head->next;
        node_destroy(l->head);

        l->head = next;
    }

    free(l);
}

ListIterator *list_front_iterator(ForwardList *l){
    ListIterator *iterator = (ListIterator *)malloc(sizeof(ListIterator));

    iterator->current = l->head;

    return iterator;
}

ListIterator *list_back_iterator(ForwardList *l){
    ListIterator *iterator = (ListIterator *)malloc(sizeof(ListIterator));

    iterator->current = l->last;

    return iterator;
}

data_type list_iterator_next(ListIterator *it){
    data_type value = it->current->value;
    it->current = it->current->next;

    return value;
}

int list_iterator_is_over(ListIterator *it){
    // if (it->current == NULL)
    // {
    //     return 1;
    // }
    // else
    // {
    //     return 0;
    // }
    return (it->current == NULL) ? 1 : 0;
}

void list_iterator_destroy(ListIterator *it){
    free(it);
}