#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void preenche_ident(int qtd, int* identeq){
    for (int i = 0; i < qtd; i++)
    {
        /* code */
    }
    
}

int main(){
    int quantidade_equipes, quantidade_etapas;
    int* identeq;
    printf("Insira a quantidade de equipes:\n");
    scanf(" %d", &quantidade_equipes);
    printf("Insira a quantidade de etaps:\n");
    scanf(" %d", &quantidade_etapas);
    identeq = (int*)malloc(sizeof(int)*quantidade_equipes);
    preenche_ident(quantidade_equipes, identeq);
}