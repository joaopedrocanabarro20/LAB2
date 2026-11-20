#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"



struct Aluno
{
    int matricula;
    char nome[50];
    int ano_ingresso;
    aluno* prox;
};

struct Lista{
    aluno* inicio;  
};

struct Curso
{
    int ABB;
    char centro[50];
    char nome[50];

    lista_alunos alunos;

    curso* esq;
    curso* dir;
};

struct arv_curso{
    curso* raiz;
};


arv_c* inicializa_arvore(void){
    arv_c* arvore = malloc(sizeof(arv_c));
    if (arvore == NULL)
    {
        printf("Erro de alocação\n");
        return NULL;
    }
    arvore->raiz = NULL;
    return arvore;
}

curso* cria_curso(int abb, char* nome, char* centro){
    curso* c = malloc(sizeof(curso));
    if (c == NULL)
    {
        return NULL;
    }
    c->alunos.inicio = NULL;
    c->ABB = abb;
    snprintf(c->nome, sizeof(c->nome), "%s", nome);
    snprintf(c->centro, sizeof(c->centro), "%s", centro);
    c->esq = NULL;
    c->dir = NULL;
    return c;
}