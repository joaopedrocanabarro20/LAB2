#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Curso curso;
typedef struct Aluno aluno;
typedef struct arv_curso arv_c;
typedef struct Lista lista_alunos;


arv_c* inicializa_arvore(void);
curso* cria_curso(int abb, const char* nome, const char* centro);
curso* busca_curso(arv_c* arvore, int codigo);
bool insere_curso(arv_c* arvore, curso* novo);
bool insere_rec(curso** atual, curso* novo);
void imprime_cursos(arv_c* arvore);
void imprime_cursos_rec(curso* atual);
aluno* cria_aluno(int matricula, const char* nome, int ano);