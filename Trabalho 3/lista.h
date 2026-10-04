#include <stdio.h>
#include <stdbool.h>

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


void cadastroMedicos(Listamedicos* lista){
    medicos* med = lista->inicio; 
    if (lista->inicio = NULL)
    {
        
    }
    
}


