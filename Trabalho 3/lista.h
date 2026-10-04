#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct medicos{
    char crm[7];
    char nome[20];
    char especialidade[20];
    char telefone[13];
    struct medicos *prox;
}medicos;

typedef struct pacientes{
    char cpf[16];
    char nome[20];
    char telefone[13];
    struct pacientes *prox;
}pacientes;

typedef struct{
    int dia;
    int mes;
    int ano;
    int hora;
    int min;
}Data;


typedef struct Consulta
{
    pacientes* paciente;
    medicos *medico;
    Data data;
    char convenio[50];
    bool status;
    char descricao[500];
    struct Consulta *prox;
}Consulta;

typedef struct{
    medicos* inicio;
}Listamedicos;

typedef struct{
    pacientes* inicio;
}Listapacientes;

typedef struct{
    Consulta* inicio;
}Listaconsultas;

void preenchemed(medicos *medico){
    printf("Digite seu CRM: ");
    scanf("%s", medico->crm);
    printf("\nDigite seu nome: ");
    fgets(medico->nome, sizeof(medico->nome), stdin);
    printf("\nDigite sua especialidade: ");
    scanf("%s", medico->especialidade);
    printf("\nDigite seu telefone: ");
    scanf("%s", medico->telefone);
    medico->prox = NULL;
}

void cadastroMedicos(Listamedicos* lista){
    medicos* med = malloc(sizeof(medicos)); 
    if (med == NULL)
    {
        free(med);
        return ;
    }
    
    preenchemed(med);
    if (lista->inicio == NULL)
    {
        lista->inicio = med;
    }
    else{
        medicos* p = lista->inicio;
        while (p->prox != NULL)
        {
            if (strcmp(p->crm, med->crm) == 0)
            {
                free(med);
                return;
            }
            p=p->prox;
        }
        if (strcmp(p->crm, med->crm) == 0)
        {
            free(med);
            return;
        }
        p->prox = med;
    }
}


