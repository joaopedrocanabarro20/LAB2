#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preenche_pontos(int qtde, int etapas, int** pontos){

    for (int i = 0; i < qtde; i++)
    {
        for (int j = 0; j < etapas; j++)
        {
            scanf("%d", &pontos[i][j]);
        }
        
    }
    
}

void preenche_ident(int qtd, int* identeq){
    printf("Digite o codigo de identificação das %d equipes\n", qtd);
    for (int i = 0; i < qtd; i++)
    {
        scanf("%d", &*(identeq+i));
    }
}

int main(){
    int quantidade_equipes, quantidade_etapas;
    int* identeq;
    int** pontuacoes;
    printf("Insira a quantidade de equipes:\n");
    scanf(" %d", &quantidade_equipes);
    printf("Insira a quantidade de etapas:\n");
    scanf(" %d", &quantidade_etapas);
    identeq = (int*)malloc(sizeof(int)*quantidade_equipes);
    preenche_ident(quantidade_equipes, identeq);
    pontuacoes=(int**)malloc(sizeof(int*)*quantidade_equipes*quantidade_etapas);
    preenche_pontos(quantidade_equipes, quantidade_etapas, pontuacoes);
}
//corrigir o malloc