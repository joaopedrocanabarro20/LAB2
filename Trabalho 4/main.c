#include <stdio.h>
#include <stdlib.h>
#include "restaurante.h"
#include <stdbool.h>
#include <string.h>

int main()
{
    Mesa **mesas = NULL;
    Pilha *pilha = NULL; 
    Fila *fila = NULL;
    int l = 0, c = 0;
    int op, y;
    do
    {
        printf("\n1) Abrir restaurante\n");
        printf("2) Chegar clientes\n");
        printf("3) Finalizar refeicao / liberar mesa\n");
        printf("4) Desistir de esperar\n");
        printf("5) Repor pratos\n");
        printf("6) Imprimir\n");
        printf("0) Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        if(op >= 2 && op <= 6 && mesas == NULL)
        {
            printf("Abra o restaurante primeiro.\n");
            continue;
        }
        
        switch (op)
        {
            case 1:
                if (mesas != NULL)
                {
                    printf("Restaurante ja aberto.\n");
                    break;
                }
                printf("Linhas: ");
                scanf("%d", &l);
                printf("Colunas: ");
                scanf("%d", &c);
                printf("Pratos na pilha: ");
                scanf("%d", &y);

                mesas = inicializa_mesa(l, c);
                pilha = inicializa_pilha_pratos();

                
        }
   
    }while (op != 0);    
}