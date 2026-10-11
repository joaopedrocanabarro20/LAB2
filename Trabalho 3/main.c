#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void exibir_menu(void) {
    printf("\n");
    printf("+==============================================================+\n");
    printf("|              SISTEMA DE GERENCIAMENTO DE CONSULTAS           |\n");
    printf("+==============================================================+\n");
    printf("|  CADASTROS                                                   |\n");
    printf("|    [1]  Cadastrar medico                                     |\n");
    printf("|    [2]  Listar medicos                                       |\n");
    printf("|    [3]  Cadastrar paciente                                   |\n");
    printf("|    [4]  Listar pacientes                                     |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|  CONSULTAS                                                   |\n");
    printf("|    [5]  Agendar consulta                                     |\n");
    printf("|    [6]  Desmarcar consulta                                   |\n");
    printf("|    [7]  Listar consultas                                     |\n");
    printf("|    [13] Realizar consulta                                    |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|  RELATORIOS                                                  |\n");
    printf("|    [8]  R1 - Consultas agendadas em um dia                   |\n");
    printf("|    [9]  R2 - Consultas realizadas por paciente               |\n");
    printf("|    [10] R3 - Descricao de uma consulta                       |\n");
    printf("|    [11] R4 - Pacientes por especialidade, mes e ano          |\n");
    printf("|    [12] R5 - Pacientes atendidos por cada medico             |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|    [0]  Sair                                                 |\n");
    printf("+==============================================================+\n");
    printf("  Escolha uma opcao: ");
}

int main(){
    Listamedicos * listaMedicos = criar_lista_medicos();
    Listapacientes * listaPacientes = criar_lista_pacientes();
    Listaconsultas * listaConsultas = criar_lista_consultas();

    if (listaMedicos == NULL || listaPacientes == NULL || listaConsultas == NULL){
    printf("Erro ao criar as listas.\n");

    liberar_lista_consultas(listaConsultas);
    liberar_lista_pacientes(listaPacientes);
    liberar_lista_medicos(listaMedicos);

    return 1;
}

    int opcao;

    do {
        exibir_menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                cadastroMedicos(listaMedicos);
                break;
            case 2:
                ListarMedicos(listaMedicos);
                break;
            case 3:
                cadastro_pacientes(listaPacientes);
                break;
            case 4:
                Listarpaciente(listaPacientes);
                break;
            case 5:
                agenda_consultas(listaConsultas, listaPacientes, listaMedicos);
                break;
            case 6: {
                printf("Digite o CPF do paciente:\n ");
                char cpf[15];
                scanf("%14s", cpf);
                printf("Digite a data da consulta (dia mes ano hora minuto): \n");
                int dia, mes, ano, hora, min;
                scanf("%d %d %d %d %d", &dia, &mes, &ano, &hora, &min);
                desmarca_consultas(listaConsultas, cpf, dia, mes, ano, hora, min);
                break;
            }
            case 7:
                listar_consultas(listaConsultas);
                break;
            case 8: {
                printf("Digite o dia da consulta:\n");
                int dia, mes, ano;
                scanf("%d %d %d", &dia, &mes, &ano);
                relatorio1(listaConsultas, dia, mes, ano);
                break;
            }
            case 9: {
                char cpf[15];

                printf("Digite o CPF do paciente:\n");
                limpar_buffer();
                ler_linha(cpf, sizeof(cpf));
                relatorio2(listaConsultas, cpf);
                break;
            }
            case 10:{
                char cpf[15];
                int dia, mes, ano, hora, min;

                printf("Digite o CPF do paciente:\n");
                limpar_buffer();
                ler_linha(cpf, sizeof(cpf));

                printf("Digite dia, mes, ano, hora e minuto:\n");
                scanf("%d %d %d %d %d", &dia, &mes, &ano, &hora, &min);

                relatorio3(listaConsultas, cpf, dia, mes, ano, hora, min);
                break;
            }
            case 11: {
                char especialidade[60];
                int mes;
                printf("Digite a especialidade do medico:\n");
                limpar_buffer();
                ler_linha(especialidade, sizeof(especialidade));

                printf("Digite o mes (1-12):\n");
                scanf("%d", &mes);

                if (mes >= 1 && mes <= 12){
                    printf("Digite o ano:\n");
                    int ano;
                    scanf("%d", &ano);
                    relatorio4(listaConsultas, especialidade, mes, ano);
                }
                else{
                    printf("Mes invalido!\n");
                }

                break;
            }
            case 12:
                getchar();
                relatorio5(listaConsultas, listaMedicos);
                break;
            case 13: {
                printf("Digite o CPF do paciente:\n ");
                char cpf[15];
                scanf("%s", cpf);
                printf("Digite a data da consulta (dia mes ano hora minuto): \n");
                int dia, mes, ano, hora, min;
                scanf("%d %d %d %d %d", &dia, &mes, &ano, &hora, &min);
                consultar(listaConsultas, cpf, dia, mes, ano, hora, min);
                break;
            }
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }while(opcao != 0);


    liberar_lista_consultas(listaConsultas);
    liberar_lista_pacientes(listaPacientes);
    liberar_lista_medicos(listaMedicos);

    return 0;   
}