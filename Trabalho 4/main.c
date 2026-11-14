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
        if (scanf("%d", &op) != 1)
        {
            break;
        }

        if (op >= 2 && op <= 6 && mesas == NULL)
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
            fila = inicializa_fila();

            if (mesas == NULL || pilha == NULL || fila == NULL)
            {
                printf("Erro ao abrir o restaurante.\n");
                libera_mesa(mesas, l);
                libera_pilha(pilha);
                libera_fila(fila);
                return 1;
            }
            repor_pratos(pilha, y);
            printf("Restaurante aberto com %d mesas.\n", l * c);
            break;

        case 2:
            printf("Quantidade de pessoas: ");
            scanf("%d", &y);
            chegar_clientes(mesas, l, c, pilha, fila, y);
            break;

        case 3:
            printf("Numero da mesa: ");
            scanf("%d", &y);
            finalizar_refeicao(mesas, l, c, pilha, fila, y);
            break;

        case 4:
            printf("Senha do grupo: ");
            scanf("%d", &y);
            desistir(fila, y);
            break;

        case 5:
            printf("Quantidade de pratos: ");
            scanf("%d", &y);
            repor_pratos(pilha, y);
            break;

        case 6:
        {
            int sub;
            printf("\n1) Uma mesa\n2) Todas as mesas\n3) Fila de espera\n4) Pilha de pratos\nOpcao: ");
            scanf("%d", &sub);
            switch (sub)
            {
            case 1:
                printf("Numero da mesa: ");
                scanf("%d", &y);
                imprimir_mesa(mesas, l, c, y);
                break;
            case 2:
                imprimir_todas_mesas(mesas, l, c);
                break;
            case 3:
                imprimir_fila(fila);
                break;
            case 4:
                imprimir_pilha(pilha);
                break;
            default:
                printf("Opcao invalida.\n");
            }
            break;
        }
        }

    } while (op != 0);

    libera_mesa(mesas, l);
    libera_pilha(pilha);
    libera_fila(fila);
    return 0;
}