#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"


void preenchemed(medicos *medico){
    printf("Digite seu CRM: ");
    scanf("%s", medico->crm);
    printf("\nDigite seu nome: ");
    getchar();    
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

void ListarMedicos(Listamedicos *lista){
    medicos* m = lista->inicio;
    while (m != NULL)
    {
    printf("CRM: %s\n", m->crm);
    printf("Nome: %s\n", m->nome);
    printf("Especialidade: %s\n", m->especialidade);
    printf("Telefone: %s\n", m->telefone);
    printf("----------------\n");
    m = m->prox;
    }
}
void preenchepaciente(pacientes* p){
    printf("Digite seu nome: ");
    getchar();
    fgets(p->nome, sizeof(p->nome), stdin);
    printf("\nDigite seu CPF: ");
    scanf("%s", p->cpf);
    printf("Digite seu telefone: ");
    scanf("%s", p->telefone);
    p->prox = NULL;
}
void cadastro_pacientes(Listapacientes* listap){
    pacientes* pac = malloc(sizeof(pacientes));
    if (pac == NULL)
    {
        return ;
    }
    
    preenchepaciente(pac);
    if (listap->inicio == NULL)
    {
        listap->inicio = pac;
    }
    else{
        pacientes* p = listap->inicio;
        while (p->prox != NULL)
        {
            if (strcmp(p->cpf, pac->cpf) == 0)
            {
                free(pac);
                return;
            }
            p=p->prox;
        }
        if (strcmp(p->cpf, pac->cpf) == 0)
        {
            free(pac);
            return;
        }
        p->prox = pac;
    }
}
void Listarpaciente(Listapacientes *lista){
    pacientes* p = lista->inicio;
    while (p != NULL)
    {
    printf("\n----------------\n");
    printf("CPF: %s\n", p->cpf);
    printf("Nome: %s\n", p->nome);
    printf("Telefone: %s\n", p->telefone);
    printf("----------------\n");
    p = p->prox;
    }
}
pacientes* buscacpf(Listapacientes* lista, char cpf[]){
    pacientes* p = lista->inicio;
    while (p != NULL && strcmp(p->cpf, cpf) != 0)
    {
        p=p->prox;
    }
    if (p == NULL)
    {
        return NULL;
    }
    
    return p;
}
medicos* buscacrm(Listamedicos* lista, char crm[]){
    medicos* m = lista->inicio;
    while (m != NULL && strcmp(m->crm, crm) != 0)
    {
        m=m->prox;
    }
    if (m == NULL)
    {
        return NULL;
    }
    
    return m;
}
bool verificamedico_ocupado(Listaconsultas* lista, Consulta* c){
    Consulta* p = lista->inicio;
    
    while(p != NULL){
        if (p->status == true && p->medico == c->medico && p->data.dia == c->data.dia && p->data.mes == c->data.mes && p->data.ano == c->data.ano && p->data.hora == c->data.hora && p->data.min == c->data.min)
        {
            printf("O médico já possui uma consulta nesse horário!\n");
            free(c);
            return;
        }

    }
}
void agenda_consultas(Listaconsultas* listac, Listapacientes* listap, Listamedicos* listam){
    Consulta* c = malloc(sizeof(Consulta));
    preenche_consulta(c, listap, listam);
    
    if (c->data.min != 0 && c->data.min != 30)
    {
        printf("Horário inválido!\n");
        free(c);
        return;
    }
    if ((c->data.hora < 8 || c->data.hora > 11) && (c->data.hora < 14 || c->data.hora > 17))
    {
    printf("Horário inválido!\n");
    free(c);
    return;
    } 
    verifica_ocupado(listac, c);
}
void preenche_consulta(Consulta* c, Listapacientes* listap, Listamedicos* listam){
    char crm[7];
    char cpf[15];
    printf("\nDigite o crm do médico que desejas: ");
    scanf("%s", crm);
    medicos* medico = buscacrm(listam, crm);
    if (medico == NULL)
    {
        printf("não Encontrado\n");
        return;
    }
    else{
        c->medico = medico;
    }
    printf("\nDigite seu CPF: ");
    scanf("%s", cpf);
    pacientes* paciente = buscacpf(listap, cpf);
    if (paciente == NULL)
    {
        printf("Não encontrado\n");
        return;
    }
    else{
        c->paciente = paciente;
    }

    preenche_data(&c->data);
    printf("\nDigite seu Convênio: ");
    getchar();
    fgets(c->convenio, sizeof(c->convenio), stdin);
    c->status = true; //true = agendado

}

void preenche_data(Data *data){
    printf("Digite o dia: ");
    scanf("%d", &data->dia);
    printf("Digite o mes: ");
    scanf("%d", &data->mes);
    printf("Digite o ano: ");
    scanf("%d", &data->ano);
    printf("Digite a hora: ");
    scanf("%d", &data->hora);
    printf("Digite os minutos: ");
    scanf("%d", &data->min);
}
