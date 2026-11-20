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

curso* cria_curso(int abb, const char* nome, const char* centro){
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

bool insere_rec(curso** atual, curso* novo){
    if (*atual == NULL){
        *atual = novo;
        return true;
    }

    if(novo->ABB < (*atual)->ABB){
        return insere_rec(&(*atual)->esq, novo);
    }

    if(novo->ABB > (*atual)->ABB){
        return insere_rec(&(*atual)->dir, novo);
    }

    return false;
}

bool insere_curso(arv_c* arvore, curso* novo){
    if (novo == NULL || arvore == NULL){
        return false;
    }

    return insere_rec(&arvore->raiz, novo);
}
curso* busca_curso_rec(curso* c, int codigo){
    if (c == NULL)
    {
        return NULL;
    }
    if(c->ABB == codigo){
        return c;
    }
    if (c->ABB > codigo)
    {
        return busca_curso_rec(c->esq, codigo);    
    }
    else if(c->ABB < codigo){
        return busca_curso_rec(c->dir,codigo);
    }
    return NULL;
}
curso* busca_curso(arv_c* arvore, int codigo){
    if(arvore == NULL || arvore->raiz == NULL){
        return NULL;
    }
    return busca_curso_rec(arvore->raiz, codigo);
}
void imprime_cursos_rec(curso* atual){
    if (atual == NULL)
    {
        return;
    }
    imprime_cursos_rec(atual->esq);
    printf("Código: %d\n", atual->ABB);
    printf("Nome: %s\n", atual->nome);
    printf("Centro: %s\n\n", atual->centro);
    imprime_cursos_rec(atual->dir);
}
void imprime_cursos(arv_c* arvore){
    if (arvore == NULL )
    {
        printf("Arvore inexistente\n");
        return;
    }
    if (arvore->raiz == NULL)
    {
        printf("Arvore vazia\n");
        return;
    }
    imprime_cursos_rec(arvore->raiz);
}
aluno* cria_aluno(int matricula, const char* nome, int ano){
    aluno* a = malloc(sizeof(aluno));
    if(a == NULL){
        printf("Memória insuficiente\n");
        return NULL;
    }
    a->matricula = matricula;
    snprintf(a->nome, sizeof(a->nome), "%s", nome);
    a->ano_ingresso = ano;
    a->prox = NULL;
    return a;
}

bool insere_aluno(curso* c, aluno* novo){
    if(c == NULL || novo == NULL){
        return false;
    }

    aluno* atual = c->alunos.inicio;
    aluno* anterior = NULL;

    while(atual != NULL && atual->matricula < novo->matricula){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual != NULL && atual->matricula == novo->matricula){
        printf("Matricula repetida\n");
        return false;
    }

    novo->prox = atual;

    if(anterior == NULL){
        c->alunos.inicio = novo;
    }
    else{
        anterior->prox = novo;
    }

    return true;
}