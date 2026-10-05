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
void preenche_consulta(Consulta* c){

}


