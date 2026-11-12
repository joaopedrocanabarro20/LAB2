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

typedef struct pratos {
    struct pratos* prox;
} Prato;

typedef struct pilha {
    Prato* topo;
    int quantidade;
} Pilha;

struct fila{
    struct fila* ini;
    struct fila* fim;
    struct fila* prox;
    int ident;
    int pessoas;
};

Mesa** inicializa_mesa(int l, int c){
    Mesa** mesas = malloc(sizeof(Mesa*)*l);
    if (mesas == NULL)
    {
        return NULL;
    }
    
    for (int i = 0; i < l; i++)
    {
        mesas[i] = malloc(sizeof(Mesa) * c);
        if (mesas[i] == NULL)
        {
            for (int i = 0; i < l; i++)
            {
                free(mesas[i]);
            }
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






