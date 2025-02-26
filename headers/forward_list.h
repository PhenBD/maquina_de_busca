
#ifndef _MY_FORWARD_LIST_H_
#define _MY_FORWARD_LIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef void *data_type;

typedef struct node Node;

Node *node_construct(data_type value, Node *next);
void node_destroy(Node *n);

typedef struct forwardList ForwardList;

/**
 * @brief Construct a new Linked List:: Linked List object
 *  Allocates memory for a new linked list and returns a pointer to it.
 * @return ForwardList*
 * Pointer to the newly allocated linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the linked list using forward_list_destroy().
 *
 */
ForwardList *forward_list_construct();

/**
 * @brief Returns the size of the linked list.
 *  Returns the number of nodes in the linked list.
 * @param l
 * Pointer to the linked list.
 * @return int
 * Number of nodes in the linked list.
 *
 */
int forward_list_size(ForwardList *l);

/**
 * @brief f an element in the linked list.
 * @param l
 * Pointer to the linked list.
 * @param void *key
 * Search key
 * @param int (*cmp_fn)(data_type data, void *key)
 * Pointer to the function to compare data values with the key.
 * @return data_type
 */
data_type forward_list_find(ForwardList *l, void *key, int (*cmp_fn)(data_type data, void *key));

/**
 * @brief Pushes a new node to the front of the linked list.
 *  Allocates memory for a new node and inserts it at the front of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param data
 * Pointer to the data to be stored in the new node.
 *
 */
void forward_list_push_front(ForwardList *l, data_type data);

/**
 * @brief Pushes a new node to the back of the linked list.
 *
 * @param l
 * Pointer to the linked list.
 * @param data
 * data to be stored in the new node.
 */
void forward_list_push_back(ForwardList *l, data_type data);

/**
 * @brief Print the elements of the linked list.
 *  Print the elements of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param print_fn
 * Pointer to the function to print data_type values.
 *
 */
void forward_list_print(ForwardList *l, void (*print_fn)(data_type));

/**
 * @brief Returns the data stored in the node at the given index.
 * @param l
 * Pointer to the linked list.
 * @param i
 * Index of the node.
 * @return data_type
 * Data stored in the node at the given index.
 *
 */
data_type forward_list_get(ForwardList *l, int i);

/**
 * @brief Remove the first node of the linked list and returns its data.
 * @param l
 * Pointer to the linked list.
 * @return data_type
 * Pointer to the data stored in the first node of the linked list that was removed.
 *
 */
data_type forward_list_pop_front(ForwardList *l);

/**
 * @brief Create a new list given by the reverse of the given list.
 * @param l
 * Pointer to the linked list.
 * @return ForwardList*
 * Pointer to the newly allocated linked list.
 */
ForwardList *forward_list_reverse(ForwardList *l);

/**
 * @brief Removes all nodes from the linked list.
 * Removes all nodes from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the data stored in the nodes.
 */
void forward_list_clear(ForwardList *l, void (*destroy_fn)(void *));

/**
 * @brief Removes all nodes with the given value from the linked list.
 * Removes all nodes with the given value from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @param val
 * Value to be removed from the linked list.
 */
void forward_list_remove(ForwardList *l, data_type val);


/**
 * @brief Adds all nodes from the given list to the end of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param m
 * Pointer to the linked list to be added to the end of the linked list.
 */
void forward_list_cat(ForwardList *l, ForwardList *m);

/**
 * @brief Destroys the linked list.
 *  Frees the memory allocated for the linked list and all its nodes.
 * @param l
 * Pointer to the linked list.
 *
 */
void forward_list_destroy(ForwardList *l);

typedef struct listIterator ListIterator;

// cria um iterador para percorrer a lista do início para o final.
ListIterator *list_front_iterator(ForwardList *l);

// cria um iterador para percorrer a lista do final para o início.
ListIterator *list_back_iterator(ForwardList *l);

// retorna o elemento do nó atual e move o iterador para o próximo nó.
data_type list_iterator_next(ListIterator *it);

// verifica se o iterador chegou ao final da lista
int list_iterator_is_over(ListIterator *it);

// libera a memória alocada para o iterador
void list_iterator_destroy(ListIterator *it);

#endif