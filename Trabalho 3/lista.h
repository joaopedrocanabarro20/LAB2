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
    long int cpf;
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

//Médicos
void preenchemed(medicos *medico);
void cadastroMedicos(Listamedicos* lista);
void ListarMedicos(Listamedicos *lista);

//Pacientes
void preenchepaciente(pacientes* p);
void cadastro_pacientes(Listapacientes* listap);
void Listarpaciente(Listapacientes *lista);

//Consultas
void preenche_consulta(Consulta* c);

//Buscas
pacientes* buscacpf(Listapacientes* lista, char cpf[]);