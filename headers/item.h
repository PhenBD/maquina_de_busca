#ifndef ITEM_H
#define ITEM_H

#include <stdlib.h>

typedef struct item Item;

/**
 * Cria um novo item com a chave e valor fornecidos.
 *
 * @param key A chave do item.
 * @param value O valor do item.
 * @return Um ponteiro para o novo item criado.
 */
Item *item_create(int key, double value);

/**
 * Obtém a chave do item fornecido.
 *
 * @param i O item do qual se deseja obter a chave.
 * @return A chave do item.
 */
int item_getKey(Item *i);

/**
 * Obtém o valor do item fornecido.
 *
 * @param i O item do qual se deseja obter o valor.
 * @return O valor do item.
 */
double item_getValue(Item *i);

/**
 * Define o valor do item fornecido.
 *
 * @param i O item para o qual se deseja definir o valor.
 * @param value O novo valor do item.
 */
void item_setValue(Item *i, double value);

/**
 * Compara dois itens e retorna 1 se o valor do primeiro item for maior que o valor do segundo item, caso contrário retorna 0.
 *
 * @param a O primeiro item a ser comparado.
 * @param b O segundo item a ser comparado.
 * @return 1 se o valor do primeiro item for maior que o valor do segundo item, 0 caso contrário.
 */
int item_more(Item *a, Item *b);

/**
 * Troca os valores de dois itens.
 *
 * @param a O primeiro item.
 * @param b O segundo item.
 */
void item_exch(Item *a, Item *b);

#endif
