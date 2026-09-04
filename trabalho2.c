#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int calcula_totais(int **pontuacoes, int qtd_et, int i){
    int total=0;
    for (int j=0; j<qtd_et; j++){
        total+=pontuacoes[i][j];
    }
    return total;
}
float calcula_media(int **pontuacoes, int qtd_et, int i){
    int total = calcula_totais(pontuacoes, qtd_et, i);
    return (float)total/qtd_et;
}
void Exibir_classificacao_final(int *identeq, int **pontuacoes, int qtd_eq, int qtd_et){
    
}
void tabelageral(int *identeq, int **pontuacoes, int qtd_eq, int qtd_et){
    printf("|EQUIPE(S)|");
    for (int i=0; i<qtd_et; i++){
        printf("|ETAPA %d|", i+1);
    }
    printf("|TOTAL|");
    printf("|MEDIA|\n");
    for(int i=0; i<qtd_eq; i++){
       printf("|   %d   |", identeq[i]);
       for(int j=0; j<qtd_et; j++){
        printf("|   %d   |", pontuacoes[i][j]);
       }
       printf("|  %d  |", calcula_totais(pontuacoes, qtd_et, i ));
       printf("| %.3f |\n", calcula_media(pontuacoes, qtd_et, i));
    }
}
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

void cadastro_pontuacoes(int qtde, int etapas, int** pontos, int *ident){
    printf("\n\n==Digite a pontuação das equipes==\n\n");
    for (int i = 0; i < qtde; i++)
    {
        printf("Equipe número %d\n", *(ident+i));
        alocarVetores(etapas, &pontos[i]);
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
    int quantidade_equipes, quantidade_etapas, opc, verifica=0;
    int* identeq;
    int** pontuacoes;
    
    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar Identificação e pontuação das equipes\n");
        printf("2 - Exibir Tabela Geral\n");
        printf("3 - Exibir Classificação Final\n");
        printf("4 - Opcao 4\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        scanf("%d", &opc);
        
        switch (opc)
        {
        case 1:

            if(verifica==0){
            printf("Insira a quantidade de equipes:\n");
            scanf(" %d", &quantidade_equipes);
            printf("Insira a quantidade de etapas:\n");
            scanf(" %d", &quantidade_etapas);
            alocarVetores(quantidade_equipes, &identeq);
            alocarMatrizes(quantidade_equipes, quantidade_etapas, &pontuacoes);
            preenche_ident(quantidade_equipes, identeq);
            cadastro_pontuacoes(quantidade_equipes, quantidade_etapas, pontuacoes, identeq);

            verifica++;
            }
            else{
                printf("Você ja preencheu !!\n");
                sleep(3); //pesquisei sobre essa função, basicamente ela espera um pouco para aparecer o menu dnv
            }
            break;
        case 2:

        if (verifica == 0)
        {
            printf("Você precisa preencher !!\n");
            sleep(3);
        }
        else{
            tabelageral(identeq, pontuacoes, quantidade_equipes, quantidade_etapas);
            sleep(5);
        }
            break;
        case 3:
        Exibir_classificacao_final(identeq, pontuacoes, quantidade_equipes, quantidade_etapas);
            break;
        case 4:

            break;
        case 0:
            break;
        }
    } while (opc != 0);
    

    for (int i = 0; i < quantidade_equipes; i++)
    {
        free(pontuacoes[i]);
    }

    free(pontuacoes);
    free(identeq);
    

}
