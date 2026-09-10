#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



void alocarVetores(int qtd, int** ident);
void alocarVetoresFloat(int qtd, float** media);
void alocarMatrizes(int qtdequipe, int qtdetapas, int ***pontuacoes);
int calcula_totais(int **pontuacoes, int qtd_et, int i);
float calcula_media(int total, int qtd_et);
void Exibir_classificacao_final(int *identeq, int qtd_eq, int* total, float* media, int qtd_et, int** pontuacoes);
void tabelageral(int *identeq, int **pontuacoes, int qtd_eq, int qtd_et, int* total, float* media);
void cadastro_pontuacoes(int qtde, int etapas, int** pontos, int *ident, int* total, float* media);
void preenche_ident(int qtd, int* identeq);
void exibir_desempenhoetapas(int quantidade_etapas, int quantidade_equipes, int** pontuacoes, int* identeq, float* media_etapas);



int calcula_totais(int **pontuacoes, int qtd_et, int i){
    int total=0;
    for (int j=0; j<qtd_et; j++){
        total+=pontuacoes[i][j];
    }
    return total;
}
float calcula_media(int total, int qtd_et){
    return (float)total/qtd_et;
}

void exibir_desempenhoetapas(int qtd_et, int qtd_eq, int** pontos, int *identeq, float* media_etapas){
    int* indices;
    alocarVetores(qtd_eq, &indices);
    for (int i = 0; i < qtd_et; i++)
    {
        printf("\nETAPA %d:\n", i+1);

        for(int k = 0; k < qtd_eq; k++){
            indices[k] = k;
        }

        for(int j = 0; j < qtd_eq - 1; j++){
            for(int k = 0; k < qtd_eq - j - 1; k++){
                if(pontos[indices[k]][i] < pontos[indices[k+1]][i]){
                    int temp = indices[k];
                    indices[k] = indices[k+1];
                    indices[k+1] = temp;
                }
            }
        }
        int idx_primeiro = indices[0];
        int idx_ultimo = indices[qtd_eq-1];
        printf("- Primeiro Lugar: Equipe %d (%d pontos)\n", identeq[idx_primeiro], pontos[idx_primeiro][i]);
        printf("- Ultimo Lugar: Equipe %d (%d pontos)\n", identeq[idx_ultimo], pontos[idx_ultimo][i]);
        printf("- Media da Etapa: %.2f pontos\n", media_etapas[i]);

    }    
    free(indices);
    }
    
void Exibir_classificacao_final(int *identeq, int qtd_eq, int* total, float* media, int qtd_et, int** pontuacoes){
    int* indices;
    alocarVetores(qtd_eq, &indices);
    for (int i = 0; i < qtd_eq; i++){
        indices[i] = i;
    }

    for(int i=0; i<qtd_eq-1; i++){
        for(int j=0; j<qtd_eq-i-1; j++){
            if(total[indices[j]] < total[indices[j+1]]) {
                int temp = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp;
            }
        }
    }

    printf("\n+----------+----------+");
    for (int i = 0; i < qtd_et; i++){
        printf("----------+");
    }
    printf("----------+----------+\n");

    printf("| POSICAO  | EQUIPE(S) |");
    for (int i = 0; i < qtd_et; i++){
        printf("  ETAPA %d |", i+1);
    }
    printf("  TOTAL   |  MEDIA   |\n");

    printf("+----------+----------+");
    for (int i = 0; i < qtd_et; i++){
        printf("----------+");
    }
    printf("----------+----------+\n");

    for (int i = 0; i < qtd_eq; i++){
       int idx = indices[i]; 
       
       printf("|   %2dº    |   %6d |", i + 1, identeq[idx]);
       
       for(int j = 0; j < qtd_et; j++){
           printf("   %4d   |", pontuacoes[idx][j]);
       }

       printf("   %4d   |", total[idx]);
       printf("  %6.2f  |\n", media[idx]);
    }

    printf("+----------+----------+");
    for (int i = 0; i < qtd_et; i++){
        printf("----------+");
    }
    printf("----------+----------+\n");


    free(indices);
}
void tabelageral(int *identeq, int **pontuacoes, int qtd_eq, int qtd_et, int* total, float* media){
    printf("\n+----------+");
    for (int i=0; i<qtd_et; i++){
        printf("----------+");
    }
    printf("----------+----------+\n");

    printf("| EQUIPE(S) |");
    for (int i=0; i<qtd_et; i++){
        printf("  ETAPA %d |", i+1);
    }
    printf("  TOTAL   |  MEDIA   |\n");

    printf("+----------+");
    for (int i=0; i<qtd_et; i++){
        printf("----------+");
    }
    printf("----------+----------+\n");

    for(int i=0; i<qtd_eq; i++){
       printf("|   %6d |", identeq[i]);
       for(int j=0; j<qtd_et; j++){
        printf("   %4d   |", pontuacoes[i][j]);
       }
       printf("   %4d   |", total[i]);
       printf("  %6.2f  |\n", media[i]);
    }

    printf("+----------+");
    for (int i=0; i<qtd_et; i++){
        printf("----------+");
    }
    printf("----------+----------+\n");
}
void alocarVetores(int qtd, int** ident){
    *ident = (int*)malloc(sizeof(int)*qtd);
    if (*ident == NULL)
    {
        printf("Memória insuficiente!\n");
        exit(1);
    }
}
void alocarVetoresFloat(int qtd, float** media){
    *media = (float*)malloc(sizeof(float)*qtd);
    if (*media == NULL)
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
    for(int i = 0; i < qtdequipe; i++){
        (*pontuacoes)[i] = (int*)malloc(sizeof(int)*qtdetapas);
        if((*pontuacoes)[i] == NULL){
            printf("Memória insuficiente!\n");
            exit(1);
        }
    }

}

void cadastro_pontuacoes(int qtde, int etapas, int** pontos, int *ident, int* total, float* media){
    printf("\n\n==Digite a pontuação das equipes==\n\n");
    for (int i = 0; i < qtde; i++)
    {
        printf("Equipe número %d\n", *(ident+i));
        for (int j = 0; j < etapas; j++)
        {
            printf("Etapa %d: ", j+1);
            scanf("%d", &pontos[i][j]);
        }
        total[i]=calcula_totais(pontos, etapas, i);
        media[i]=calcula_media(total[i], etapas);
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
    int quantidade_equipes=0, quantidade_etapas=0, opc, verifica=0;
    int* identeq = NULL ;
    int** pontuacoes = NULL;
    int *total = NULL;
    float *media =NULL;
    float *media_etapas=NULL;
    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar Identificação e pontuação das equipes\n");
        printf("2 - Exibir Tabela Geral\n");
        printf("3 - Exibir Classificação Final\n");
        printf("4 - Exibir Desempenho por etapa\n");
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
            alocarVetores(quantidade_equipes, &total);
            alocarVetoresFloat(quantidade_equipes, &media);
            alocarVetoresFloat(quantidade_etapas, &media_etapas);
            alocarMatrizes(quantidade_equipes, quantidade_etapas, &pontuacoes);
            preenche_ident(quantidade_equipes, identeq);
            cadastro_pontuacoes(quantidade_equipes, quantidade_etapas, pontuacoes, identeq, total, media);

            for (int i = 0; i < quantidade_etapas; i++)
            {
                int soma=0;
                for (int j = 0; j < quantidade_equipes; j++)
                {
                    soma+=pontuacoes[j][i];
                }
                media_etapas[i]=(float)soma/quantidade_equipes;
            }

            verifica++;
            }
            else{
                printf("Você ja preencheu !!\n");
                sleep(1); 
            }
            break;
        case 2:

        if (verifica == 0)
        {
            printf("Você precisa preencher !!\n");
            sleep(1);
        }
        else{
            tabelageral(identeq, pontuacoes, quantidade_equipes, quantidade_etapas, total, media);
            sleep(3);
        }
            break;
        case 3:
            if (verifica == 0){
                printf("Você precisa preencher primeiro!\n");
            }
            else{
                Exibir_classificacao_final(identeq, quantidade_equipes, total, media, quantidade_etapas, pontuacoes);
            }           
            break;
        case 4:
            if (verifica == 0)
            {
                printf("Você precisa preencher primeiro!\n");
            }
            else{
                exibir_desempenhoetapas(quantidade_etapas, quantidade_equipes, pontuacoes, identeq, media_etapas);
            }
            break;
        case 0:
            printf("Tchau Tchau\n");
            break;
        default:
            printf("Opção Inválida!!!\n");
        }
    } while (opc != 0);
    

    for (int i = 0; i < quantidade_equipes; i++)
    {
        free(pontuacoes[i]);
    }

    free(pontuacoes);
    free(identeq);
    free(total);
    free(media);
    free(media_etapas);
}