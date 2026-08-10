#include <stdio.h>
#define TAM 5

typedef struct
{
    int codigo;
    char nome[81];
    float peso;
    int altura;
    float IMC;
    char faixa[15];
} Pessoa;

void preenchevetor(Pessoa vetorp[]){
    float alturaconvertida;
    for (int i = 0; i < TAM; i++)
    {
        printf("Digite o seu código:\n");
        scanf("%d", &vetorp[i].codigo);
        getchar();//preciso usar isso porque scanf e fgets se conflitam
        printf("Digite o seu nome:\n");
        fgets(vetorp[i].nome, sizeof(vetorp[i].nome), stdin);
        printf("Digite seu peso(em kg):\n");
        scanf("%f", &vetorp[i].peso);
        printf("Digite sua altura(em cm):\n");
        scanf("%d", &vetorp[i].altura);
        alturaconvertida=((float)vetorp[i].altura/100);
        vetorp[i].IMC=vetorp[i].peso/(alturaconvertida*alturaconvertida);
        printf("%f\n", vetorp[i].IMC);
        verificafaixa(vetorp[i].IMC, vetorp[i].nome);
    }
    
}

int main(){
    Pessoa pessoas[TAM];
    preenchevetor(pessoas);
    
}