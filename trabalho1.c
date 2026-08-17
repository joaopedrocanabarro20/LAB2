#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 15

typedef struct
{
    int codigo;
    char nome[81];
    float peso;
    int altura;
    float IMC;
    char faixa[15];
} Pessoa;

int verificafaixa(float imc){
    if (imc < 18.5)
    {
        return 0;
    }
    else if (imc >= 18.5 && imc < 24.9)
    {
        return 1;
    }
    else if (imc >= 24.9 && imc < 30.0)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

void preenchevetor(Pessoa vetorp[]) {
    float alturaconvertida;
    int n;
    for (int i = 0; i < TAM; i++)
    {
        
        printf("\nDigite o seu código:\n");
        
        scanf("%d", &vetorp[i].codigo);
        
        getchar();//preciso usar isso porque scanf e fgets se conflitam
        
        printf("Digite o seu nome:\n");
        
        fgets(vetorp[i].nome, sizeof(vetorp[i].nome), stdin);

        vetorp[i].nome[strcspn(vetorp[i].nome, "\n")] = '\0';
        
        printf("Digite seu peso(em kg):\n");
        
        scanf("%f", &vetorp[i].peso);
        
        printf("Digite sua altura(em cm):\n");
        
        scanf("%d", &vetorp[i].altura);
        
        alturaconvertida=((float)vetorp[i].altura/100);
        
        vetorp[i].IMC=vetorp[i].peso/(alturaconvertida*alturaconvertida);
        
        printf("%f\n", vetorp[i].IMC);

        n = verificafaixa(vetorp[i].IMC);
        switch(n) {
            case 0:
                strcpy(vetorp[i].faixa, "Magreza");
                break;
            case 1: 
                strcpy(vetorp[i].faixa, "Normal");
                break;
            case 2:
                strcpy(vetorp[i].faixa, "Sobrepeso");
                break;
            case 3:
                strcpy(vetorp[i].faixa, "Obesidade");
                break;

        }
    }
}

void mostradados(Pessoa *vet) {
    for(int i=0; i<TAM; i++) {
        printf("\nInformações de: %d\n", vet[i].codigo);
        printf("Nome: %s\n", vet[i].nome);
        printf("Peso: %.2fkg\n", vet[i].peso);
        printf("Altura: %dcm\n", vet[i].altura);
        printf("IMC: %.4fkg/m2\n", vet[i].IMC);
        printf("Faixa: %s\n", vet[i].faixa);
    }
}

void mostranomesob(Pessoa vet[]){
    printf("Estão em sobrepeso:\n");
    for(int i=0; i<TAM; i++){
        if(vet[i].IMC>=24.9 && vet[i].IMC<30.0){
            printf("%s\n", vet[i].nome);
        }
    }
    
}

void mostraobeso(Pessoa vet[]){
    printf("\nCódigo de pessoas que estão com obesidade:\n");
    for (int i=0;i<TAM; i++){
        if(vet[i].IMC>=30.0){
            printf("-%d\n",vet[i].codigo);
        }
    }
}

float mediapesos(Pessoa vet[]){
    float soma=0;
    for (int i=0; i<TAM; i++){
        soma+=vet[i].peso;
    }
    float media = soma/(float)TAM;
    return media;
}

void acimamedia(Pessoa vet[]){
    int qtd=0;
    float media;
    media = mediapesos(vet);
    for (int i=0; i<TAM; i++){
        if(vet[i].peso>media){
            qtd++;
        }
    }
    printf("\n%d pessoas estao acima da media de pesos", qtd);
}
void notnormal(Pessoa vet[]){
    int qntd=0;
    for (int i = 0; i < TAM; i++)
    {
        if (vet[i].IMC < 18.5 || vet[i].IMC >= 24.9)
        {
            qntd++;
        }
    }
    printf("Quantidade de pessoas fora da faixa normal de peso: %d\n", qntd);
}
void mediacomnome(Pessoa vet[]){
    float media;
    media=mediapesos(vet);
    for (int i = 0; i < TAM; i++)
    {
        if ( (vet[i].IMC>=18.5 && vet[i].IMC<24.9) && (vet[i].peso<media))
        {
            printf("%s\n", vet[i].nome);
        }
    }
}
void maiorimc(Pessoa vet[]){
    int i=0;
    float maior;
    maior=vet[i].IMC;
    printf("\nNome da(s) pessoa(s) com maior IMC:\n");
    for (int i = 1; i < TAM; i++)
    {
        if (vet[i].IMC>=maior)
        {
            maior=vet[i].IMC;
        }
    }
    for (int i = 0; i < TAM; i++)
    {
        if (vet[i].IMC==maior)
        {
            printf("\n%s", vet[i].nome);
        }
        
    }
}
void codigomenor(Pessoa vet[]){
    int i=0;
    float menor;
    menor=vet[i].IMC;
    printf("codigo das pessoas que tiveram o menor IMC:\n");
    for (int i = 1; i < TAM; i++)
    {
        if (vet[i].IMC<menor)
        {
            menor=vet[i].IMC;
        }
    }
    for (int i = 0; i < TAM; i++)
    {
        if (vet[i].IMC==menor)
        {
            printf("%d\n", vet[i].codigo);
        }
    }
    
}
int main(){
    int opc;

    float media;
    Pessoa pessoas[TAM];
    preenchevetor(pessoas);
    do {
    printf("\n\n\n=========================================================\n");

    printf("\n|| Qual relatório você deseja acessar?\n"
           "|| 1) os dados de todas as pessoas do vetor;\n"
           "|| 2) o nome das pessoas que estão com sobrepeso;\n"
           "|| 3) o código das pessoas que estão com obesidade;\n"
           "|| 4) o valor médio dos pesos;\n"
           "|| 5) a quantidade de pessoas que tem peso acima do valor médio dos pesos;\n"
           "|| 6) a quantidade de pessoas que não estão na faixa normal de peso;\n"
           "|| 7) o nome das pessoas que tem peso normal e que pesam menos do que o valor médio dos pesos;\n"
           "|| 8) o nome da(s) pessoa(s) que obteve (obtiveram) o maior IMC;\n"
           "|| 9) o código da(s) pessoa (s) que obteve (obtiveram) o menor IMC;\n"
           "|| 10) SAIR;\n");

    printf("\n=========================================================\n");

    scanf("%d", &opc);

    switch(opc) {
        case 1:
            mostradados(pessoas);
            break;

        case 2:
            mostranomesob(pessoas);
            break;

        case 3:
            mostraobeso(pessoas);
            break;

        case 4:
            media = mediapesos(pessoas);
            printf("Média dos pesos: %.2f\n", media);
            break;

        case 5:
            acimamedia(pessoas);
            break;

        case 6:
            notnormal(pessoas);
            break;

        case 7:
            mediacomnome(pessoas);
            break;

        case 8:
            maiorimc(pessoas);
            break;

        case 9:
            codigomenor(pessoas);
            break;

        case 10:
            exit(0);
    }

} while (opc != 10);
}