#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct mesa Mesa;
typedef struct pilha Pilha;
typedef struct fila Fila;

// MESAS
void libera_mesa(Mesa **mesas, int l);
Mesa **inicializa_mesa(int l, int c);
void imprimir_mesa(Mesa **mesa, int l, int c, int id);
void imprimir_todas_mesas(Mesa **mesas, int l, int c);

// PRATOS
Pilha *inicializa_pilha_pratos(void);
bool push_pratos(Pilha *pratos);
bool pop_pratos(Pilha *pratos);
void repor_pratos(Pilha *p, int quantidade);
void imprimir_pilha(Pilha *p);
void libera_pilha(Pilha *p);

// FILA
Fila *inicializa_fila(void);
int enfileirar_grupo(Fila *f, int pessoas);
void imprimir_fila(Fila *f);
void libera_fila(Fila *f);

// CLIENTES
void chegar_clientes(Mesa **mesas, int l, int c, Pilha *p, Fila *f, int pessoas);
void finalizar_refeicao(Mesa **mesas, int l, int c, Pilha *p, Fila *f, int id);
void desistir(Fila *f, int senha);
#endif