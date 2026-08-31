#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alocarVetores(int qtd, int** ident){
    *ident = (int*)malloc(sizeof(int)*qtd);
    if (*ident == NULL)
    {
        printf("Memória insuficiente!\n");
        exit(1);
    }
}
void alocarMatrizes(int qtdequipe, int qtdetapas, int ***pontuacoes){
    *pontuacoes = (int**)malloc(sizeof(int*)*qtdequipe);
    if(*pontuacoes == NULL){
        printf("Memória insuficiente!\n");
        exit(1);
    }

}

void preenche_pontos(int qtde, int etapas, int** pontos, int *ident){
    printf("\n\n==Digite a pontuação das equipes==\n\n");
    for (int i = 0; i < qtde; i++)
    {
        printf("Equipe número %d\n", *(ident+i));
        *(pontos+i)=(int*)malloc(sizeof(int)*etapas);

        if(*(pontos+i) == NULL){
            printf("Memória insuficiente!\n");
            exit(1);
        }

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
    int quantidade_equipes, quantidade_etapas, opc;
    int* identeq;
    int** pontuacoes;
    printf("Insira a quantidade de equipes:\n");
    scanf(" %d", &quantidade_equipes);
    printf("Insira a quantidade de etapas:\n");
    scanf(" %d", &quantidade_etapas);
    alocarVetores(quantidade_equipes, &identeq);
    preenche_ident(quantidade_equipes, identeq);
    alocarMatrizes(quantidade_equipes, quantidade_etapas, &pontuacoes);
    pontuacoes = (int**)malloc(sizeof(int*)*quantidade_equipes);
    preenche_pontos(quantidade_equipes, quantidade_etapas, pontuacoes, identeq);

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Opcao 1\n");
        printf("2 - Opcao 2\n");
        printf("3 - Opcao 3\n");
        printf("4 - Opcao 4\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        scanf("%d", &opc);
        
        switch (opc)
        {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:

            break;
        case 4:

            break;
        case 0:
            exit(0);
            break;
        }
    } while (opc != 0);
    
    free(pontuacoes);
    free(identeq);

}
