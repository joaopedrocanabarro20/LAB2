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
static Mesa *mesa_livre(Mesa **mesas, int l, int c);
static bool ocupa_mesa(Mesa *m, int n, Pilha *p);

// PRATOS
Pilha *inicializa_pilha_pratos(void);
bool push_pratos(Pilha *pratos);
bool pop_pratos(Pilha* pratos);
void repor_pratos(Pilha *p, int quantidade);
void imprimir_pilha(Pilha *p);
void libera_pilha(Pilha *p);
// FILA
Fila* inicializa_fila(void);
void liberar_fila(Fila *f);