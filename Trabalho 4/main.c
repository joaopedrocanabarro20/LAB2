#include <stdio.h>
#include <stdlib.h>
#include "restaurante.h"
#include <stdbool.h>
#include <string.h>

// Le um inteiro; em caso de entrada invalida limpa o buffer e retorna false.
static bool ler_int(const char *msg, int *valor)
{
    printf("%s", msg);
    if (scanf("%d", valor) == 1)
    {
        return true;
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
    printf("Entrada invalida.\n");
    return false;
}

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
        if (!ler_int("Opcao: ", &op))
        {
            if (feof(stdin))
            {
                break;
            }
            op = -1;
            continue;
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
            if (!ler_int("Linhas: ", &l) || !ler_int("Colunas: ", &c) ||
                !ler_int("Pratos na pilha: ", &y))
            {
                break;
            }

            mesas = inicializa_mesa(l, c);
            pilha = inicializa_pilha_pratos();
            fila = inicializa_fila();

            if (mesas == NULL || pilha == NULL || fila == NULL)
            {
                printf("Erro ao abrir o restaurante (linhas e colunas devem ser > 0).\n");
                libera_mesa(mesas, l);
                libera_pilha(pilha);
                libera_fila(fila);
                mesas = NULL;
                pilha = NULL;
                fila = NULL;
                l = c = 0;
                break;
            }
            repor_pratos(pilha, y);
            printf("Restaurante aberto com %d mesas.\n", l * c);
            break;

        case 2:
            if (ler_int("Quantidade de pessoas: ", &y))
            {
                chegar_clientes(mesas, l, c, pilha, fila, y);
            }
            break;

        case 3:
            if (ler_int("Numero da mesa: ", &y))
            {
                finalizar_refeicao(mesas, l, c, pilha, fila, y);
            }
            break;

        case 4:
            if (ler_int("Senha do grupo: ", &y))
            {
                desistir(fila, y);
            }
            break;

        case 5:
            if (ler_int("Quantidade de pratos: ", &y))
            {
                reabastecer_pratos(mesas, l, c, pilha, fila, y);
            }
            break;

        case 6:
        {
            int sub;
            printf("\n1) Uma mesa\n2) Todas as mesas\n3) Fila de espera\n4) Pilha de pratos\n");
            if (!ler_int("Opcao: ", &sub))
            {
                break;
            }
            switch (sub)
            {
            case 1:
                if (ler_int("Numero da mesa: ", &y))
                {
                    imprimir_mesa(mesas, l, c, y);
                }
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

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }

    } while (op != 0);

    libera_mesa(mesas, l);
    libera_pilha(pilha);
    libera_fila(fila);
    return 0;
}