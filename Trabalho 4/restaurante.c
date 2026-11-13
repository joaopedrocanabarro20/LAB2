#include <stdio.h>
#include <stdlib.h>
#include "restaurante.h"
#include <stdbool.h>
#include <string.h>

struct mesa
{
    int identificacao;
    bool ocupado;
    int pessoas;
    int comanda;
    int pratos;
};

typedef struct pratos
{
    struct pratos *prox;
} Prato;

typedef struct pilha
{
    Prato *topo;
    int quantidade;
} Pilha;

struct fila
{
    struct fila *ini;
    struct fila *fim;
    struct fila *prox;
    int ident;
    int pessoas;
};

Mesa **inicializa_mesa(int l, int c)
{
    if (l <= 0 || c <= 0)
    {
        return NULL;
    }

    Mesa **mesas = malloc(sizeof(Mesa *) * l);
    if (mesas == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < l; i++)
    {
        mesas[i] = malloc(sizeof(Mesa) * c);
        if (mesas[i] == NULL)
        {
            libera_mesa(mesas, i);
            return NULL;
        }
    }

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            mesas[i][j].ocupado = false;
            mesas[i][j].pessoas = 0;
            mesas[i][j].comanda = 0;
            mesas[i][j].pratos = 4;
            mesas[i][j].identificacao = i * c + j + 1;
        }
    }
    return mesas;
}

void libera_mesa(Mesa **mesas, int l)
{
    if (mesas == NULL)
        return;
    for (int j = 0; j < l; j++)
    {
        free(mesas[j]);
    }
    free(mesas);
}

Pilha *inicializa_pilha_pratos(void)
{
    Pilha *p = malloc(sizeof(Pilha));

    if (p == NULL)
        return NULL;

    p->topo = NULL;
    p->quantidade = 0;

    return p;
}

void push_pratos(Pilha *pratos)
{
    if (pratos == NULL)
    {
        return;
    }
    Prato *novo_prato = malloc(sizeof(Prato));

    if (novo_prato == NULL)
    {
        return;
    }

    novo_prato->prox = pratos->topo;
    pratos->topo = novo_prato;
    pratos->quantidade++;
}

void repor_pratos(Pilha *p, int quantidade)
{
    if (quantidade <= 0)
    {
        return;
    }
    if (p == NULL)
    {
        return;
    }

    for (int i = 0; i < quantidade; i++)
    {
        push_pratos(p);
    }
    printf("Pratos na pilha: %d\n", p->quantidade);
}

static Mesa *mesa_livre(Mesa **mesas, int l, int c)
{
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (!mesas[i][j].ocupado)
            {
                return &mesas[i][j];
            }
        }
    }
    return NULL;
}

static void ocupa_mesa(Mesa *m, int n, Pilha *p)
{
    m->ocupado = true;
    m->pessoas = n;
    m->comanda = m->identificacao;

    while (m->pratos > n)
    {
        push_pratos(p);
        m->pratos--;
    }
    while (m->pratos < n && p->topo != NULL)
    {
        // falta funcao de pop
        m->pratos++;
    }
    printf("Mesa %d ocupada por %d pessoa(s).\n", m->identificacao, n);
}

void imprimir_pilha(Pilha* p)
{
    printf("Pratos na pilha: %d\n", p->quantidade);
}

void imprimir_mesa(Mesa** mesa, int l, int c, int id)
{
    if (id < 1 || id > l *c)
    {
        printf("Mesa inexistente.\n");
        return;
    }
    Mesa* m = &mesa[(id - 1) / c][(id-1) % c];
    if(m->ocupado)
    {
        printf("Mesa %d: ocupada, %d pessoa(s), comanda %d\n", m->identificacao, m->pessoas, m->comanda);

    }
    else
    {
        printf("Mesa %d: livre\n", m->identificacao);
    }
    
}