#ifndef PQ_H
#define PQ_H

#include <stdio.h>
#include <stdbool.h>
#include "item.h"

typedef struct pq PQ;

/**
 * Cria uma nova fila de prioridade.
 *
 * @param maxN O tamanho máximo da fila de prioridade.
 * @return Um ponteiro para a nova fila de prioridade.
 */
PQ *PQ_create(int maxN);

/**
 * Troca dois elementos na fila de prioridade.
 *
 * @param pq A fila de prioridade.
 * @param i O índice do primeiro elemento.
 * @param j O índice do segundo elemento.
 */
static void PQ_swap(PQ *pq, int i, int j);

/**
 * Corrige a ordem da fila de prioridade subindo o elemento na posição k.
 *
 * @param pq A fila de prioridade.
 * @param k O índice do elemento a ser corrigido.
 */
void PQ_fix_up(PQ *pq, int k);

/**
 * Corrige a ordem da fila de prioridade descendo o elemento na posição k.
 *
 * @param pq A fila de prioridade.
 * @param sz O tamanho atual da fila de prioridade.
 * @param k O índice do elemento a ser corrigido.
 */
void PQ_fix_down(PQ *pq, int sz, int k);

/**
 * Insere um novo item na fila de prioridade.
 *
 * @param pq A fila de prioridade.
 * @param v O item a ser inserido.
 */
void PQ_insert(PQ* pq, Item *v);

/**
 * Remove e retorna o item de menor prioridade da fila de prioridade.
 *
 * @param pq A fila de prioridade.
 * @return O item de menor prioridade.
 */
Item *PQ_delmax(PQ *pq);

/**
 * Retorna o item de menor prioridade da fila de prioridade sem removê-lo.
 *
 * @param pq A fila de prioridade.
 * @return O item de menor prioridade.
 */
Item *PQ_max(PQ *pq);

/**
 * Verifica se a fila de prioridade contém um item com a chave especificada.
 *
 * @param pq A fila de prioridade.
 * @param key A chave do item a ser verificado.
 * @return true se a fila de prioridade contém o item, false caso contrário.
 */
bool PQ_contains(PQ *pq, int key);

/**
 * Verifica se a fila de prioridade está vazia.
 *
 * @param pq A fila de prioridade.
 * @return true se a fila de prioridade está vazia, false caso contrário.
 */
bool PQ_empty(PQ *pq);

/**
 * Retorna o tamanho atual da fila de prioridade.
 *
 * @param pq A fila de prioridade.
 * @return O tamanho atual da fila de prioridade.
 */
int  PQ_size(PQ *pq);

/**
 * Libera a memória alocada para a fila de prioridade.
 *
 * @param pq A fila de prioridade a ser destruída.
 */
void PQ_destroy(PQ *pq);

#endif
