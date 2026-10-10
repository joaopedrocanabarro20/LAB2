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
    char cpf[15];
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
    struct Consulta *ant;
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
Listamedicos *criar_lista_medicos();
void preenchemed(medicos *medico);
void cadastroMedicos(Listamedicos* lista);
void ListarMedicos(Listamedicos *lista);

//Pacientes
Listapacientes *criar_lista_pacientes();
void preenchepaciente(pacientes* p);
void cadastro_pacientes(Listapacientes* listap);
void Listarpaciente(Listapacientes *lista);

//Consultas
Listaconsultas *criar_lista_consultas();
void preenche_consulta(Consulta* c, Listapacientes* listap, Listamedicos* listam);
void preenche_data(Data *data);
void agenda_consultas(Listaconsultas* listac, Listapacientes* listap, Listamedicos* listam);
void desmarca_consultas(Listaconsultas * listac, char cpf[], int dia, int mes, int ano, int hora, int min);
void consultar(Listaconsultas * listac, char cpf[], int dia, int mes, int ano, int hora, int min);
bool verifica_repeticao(Listaconsultas * listac, char cpf[], int dia, int mes, int ano, int hora, int min);
void listar_consultas(Listaconsultas * listac);

//Buscas
pacientes* buscacpf(Listapacientes* lista, char cpf[]);
medicos* buscacrm(Listamedicos* lista, char crm[]);

//verificação
bool verificamedico_ocupado(Listaconsultas* lista, Consulta* c);

//Relatórios
void relatorio1(Listaconsultas * listac, int dia, int mes, int ano);
void relatorio2(Listaconsultas * listac, char nome[]);
void relatorio3(Listaconsultas * listac, char nome[], int dia, int mes, int ano, int hora, int min);
void relatorio4(Listaconsultas * listac, char especialidade[], int mes);
void relatorio5(Listaconsultas * listac, Listamedicos * listam);