#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preenche_pontos(int qtde, int etapas, int** pontos, int *ident){
    printf("\n\n==Digite a pontução das equipes==\n\n");
    for (int i = 0; i < qtde; i++)
    {
        printf("Equipe numero %d:\n", *(ident+i));
        *(pontos+i)=(int*)malloc(sizeof(int)*etapas);
        for (int j = 0; j < etapas; j++)
        {
            printf("Etapa %d: ", j+1);
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
    pontuacoes = (int**)malloc(sizeof(int*)*quantidade_equipes);
    preenche_pontos(quantidade_equipes, quantidade_etapas, pontuacoes, identeq);
    free(pontuacoes);
    free(identeq);

}
//corrigir o malloc