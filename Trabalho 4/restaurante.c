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

struct pratos{
    bool limpo;
    struct pratos* prox;
};

struct fila
{
    struct fila* ini;
    struct fila* fim;
    struct fila* prox;
    int ident;
    int pessoas;
};

Mesa** inicializa_mesa(int l, int c){
    Mesa** mesas = malloc(sizeof(Mesa*)*l);
    for (int i = 0; i < l; i++)
    {
        Mesa* mesas = malloc(sizeof(Mesa)*c);
    }

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            mesas[i][j].ocupado = false;
            mesas[i][j].pessoas = 0;
            mesas[i][j].comanda = 0;
            mesas[i][j].pratos = 4;
        }
        
    } 
}




