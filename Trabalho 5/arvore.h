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
