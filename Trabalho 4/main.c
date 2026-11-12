#include <stdio.h>
#include <stdlib.h>
#include "restaurante.h"
#include <stdbool.h>
#include <string.h>

int main()
{
    int op;
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
        
        switch (op)
        {
            
        }
   
    }while (op != 0);    
}