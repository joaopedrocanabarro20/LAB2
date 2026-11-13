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

 struct pilha
{
    Prato *topo;
    int quantidade;
};

typedef struct grupo
{
    int senha;
    int pessoas;
    struct grupo* prox;
}Grupo;

struct fila
{
    Grupo* ini;
    Grupo* fim;
    int proxima_senha;
};

//MESA 

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

//PRATOS

Pilha *inicializa_pilha_pratos(void)
{
    Pilha *p = malloc(sizeof(Pilha));

    if (p == NULL)
        return NULL;

    p->topo = NULL;
    p->quantidade = 0;

    return p;
}

bool push_pratos(Pilha *pratos)
{
    if (pratos == NULL)
    {
        return false;
    }
    Prato *novo_prato = malloc(sizeof(Prato));

    if (novo_prato == NULL)
    {
        return false;
    }

    novo_prato->prox = pratos->topo;
    pratos->topo = novo_prato;
    pratos->quantidade++;
    return true;
}

bool pop_pratos(Pilha* pratos){
    if (pratos == NULL)
    {
        return false;
    }
    Prato* prato_free = pratos->topo;
    if (prato_free == NULL)
    {
        return false;
    }
    
    pratos->topo = prato_free->prox;
    free(prato_free);
    pratos->quantidade -= 1;

    return true;
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
    int adicionados = 0;


    for (int i = 0; i < quantidade; i++)
    {
        if (!push_pratos(p))
        {
            break;
        }
        adicionados++;

    }
    printf("Pratos adicionados: %d\n", adicionados);
    printf("Total na pilha: %d\n", p->quantidade);
}



void imprimir_pilha(Pilha* p)
{
    printf("Pratos na pilha: %d\n", p->quantidade);
}

void libera_pilha(Pilha* p)
{
    if (p == NULL)
    {
        return;
    }
    
    Prato* pratos = p->topo;

    while (pratos != NULL)
    {
        Prato* prato_aux = pratos;
        pratos=pratos->prox;
        free(prato_aux);
    }
    free(p);
}

Fila* inicializa_fila(void)
{
    Fila* f = malloc(sizeof(Fila));

    if (f == NULL)
    {
        return NULL;
    }

    f->ini = NULL;
    f->fim = NULL;
    f->proxima_senha = 1;

    return f;
}


//imprimir mesa

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
void imprimir_todas_mesas(Mesa** mesas, int l, int c){
    if (l <= 0 || c <= 0)
    {
        printf("ERRO!\n");
        return;
    }
    if(mesas == NULL)
    {
        printf("Matriz de mesas inexistente.\n");
        return;
    }
    
    for (int i = 1; i <= l*c; i++)
    {
        imprimir_mesa(mesas, l, c, i);
    }
}
static Mesa* mesa_livre(Mesa** mesas, int l, int c)
{
    if (mesas == NULL || l <= 0 || c <= 0)
    {
        return NULL;
    }

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (!mesas[i][j].ocupado && mesas[i][j].pratos == 4)
            {
                return &mesas[i][j];
            }
        }
    }
    return NULL;
}
    
static bool ocupa_mesa(Mesa* m, int n, Pilha* p)
{
    if (m == NULL || p == NULL || n < 1 || n > 4)
    {
        return false;
    }

    if (m->ocupado || m->pratos != 4)
    {
        return false;
    }

    int excedentes = 4 - n;
    int adicionados = 0;

    for (int i = 0; i < excedentes; i++)
    {
        if (!push_pratos(p))
        {
            while (adicionados > 0)
            {
                pop_pratos(p);
                adicionados--;
            }

            return false;
        }

        adicionados++;
    }

    m->ocupado = true;
    m->pessoas = n;
    m->comanda = m->identificacao;
    m->pratos = n;

    printf("Mesa %d ocupada por %d pessoa(s).\n", m->identificacao, n);

    return true;
}