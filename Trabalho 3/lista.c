#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"


//--------- Códigos para manipulação de médicos ---------//

Listamedicos *criar_lista_medicos() {
    Listamedicos *lista = malloc(sizeof(Listamedicos));
    if (lista == NULL) {
        return NULL;
    }
    lista->inicio = NULL;
    return lista;
}

void preenchemed(medicos *medico)
{
    printf("Digite seu CRM: ");
    scanf("%6s", medico->crm);
    limpar_buffer();

    printf("Digite seu nome: ");
    ler_linha(medico->nome, sizeof(medico->nome));

    printf("Digite sua especialidade: ");
    ler_linha(medico->especialidade, sizeof(medico->especialidade));

    printf("Digite seu telefone: ");
    scanf("%12s", medico->telefone);
    limpar_buffer();

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

//---------------------------//----------------------------//

//--------- Códigos para manipulação de pacientes ---------//

Listapacientes *criar_lista_pacientes() {
    Listapacientes *lista = malloc(sizeof(Listapacientes));
    if (lista == NULL) {
        return NULL;
    }
    lista->inicio = NULL;
    return lista;
}

void preenchepaciente(pacientes *p)
{
    limpar_buffer();

    printf("Digite seu nome: ");
    ler_linha(p->nome, sizeof(p->nome));

    printf("Digite seu CPF: ");
    scanf("%14s", p->cpf);

    printf("Digite seu telefone: ");
    scanf("%12s", p->telefone);
    limpar_buffer();

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

//---------------------------//----------------------------//

//--------- Códigos para buscar e verificar médicos e pacientes ---------//


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
            return true;
        }
        p = p->prox;
    }
    return false;
}

//---------------------------//----------------------------//

//--------- Códigos para manipulação de consultas ---------//

Listaconsultas *criar_lista_consultas() {
    Listaconsultas *lista = malloc(sizeof(Listaconsultas));
    if (lista == NULL) {
        return NULL;
    }
    lista->inicio = NULL;
    return lista;
}

void agenda_consultas(Listaconsultas* listac, Listapacientes* listap, Listamedicos* listam){
    Consulta *c = malloc(sizeof(Consulta));
    if (c == NULL){
        printf("Erro ao alocar memoria para a consulta.\n");
        return;
    }
    c->medico = NULL;
    c->paciente = NULL;
    preenche_consulta(c, listap, listam);

    if (c->medico == NULL || c->paciente == NULL)
    {
        free(c);
        return;
    }
    
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
    if(verificamedico_ocupado(listac, c) || verifica_repeticao(listac, c->paciente->cpf, c->data.dia, c->data.mes, c->data.ano, c->data.hora, c->data.min)){
        free(c);
        return;
    }
    Consulta *p = listac->inicio;
    if (p == NULL)
    {
        listac->inicio = c;
        c->prox = NULL;
        c->ant = NULL;
    }
    else{
        while (p->prox != NULL)
        {
            p = p->prox;
        }
        p->prox = c;
        c->ant = p;
        c->prox = NULL;
    }
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
    printf("Digite seu convenio: ");
    limpar_buffer();
    ler_linha(c->convenio, sizeof(c->convenio));

    c->status = true;
    c->descricao[0] = '\0';
}

bool verifica_repeticao(Listaconsultas *listac, char cpf[], int dia, int mes, int ano, int hora, int min){
    Consulta *p = listac->inicio;

    while (p != NULL)
    {
        if (p->status == true &&
            p->paciente != NULL &&
            strcmp(cpf, p->paciente->cpf) == 0 &&
            p->data.dia == dia &&
            p->data.mes == mes &&
            p->data.ano == ano &&
            p->data.hora == hora &&
            p->data.min == min)
        {
            printf("Consulta ja agendada!\n");
            return true;
        }

        p = p->prox;
    }

    return false;
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


void desmarca_consultas(Listaconsultas *listac, char cpf[], int dia, int mes, int ano, int hora, int min){
    Consulta *p = listac->inicio;
    bool realizada = false;

    while (p != NULL){
        if (p->paciente != NULL && strcmp(cpf, p->paciente->cpf) == 0 && p->data.dia == dia && p->data.mes == mes && p->data.ano == ano && p->data.hora == hora && p->data.min == min){
            if (p->status == false){
                realizada = true;
                p = p->prox;
                continue;
            }

            if (p->ant != NULL){
                p->ant->prox = p->prox;
            }
            else{
                listac->inicio = p->prox;
            }
            if (p->prox != NULL){
                p->prox->ant = p->ant;
            }

            free(p);
            printf("Consulta desmarcada com sucesso!\n");
            return;
        }
 
        p = p->prox;
    }

    if (realizada)
    {
        printf("Essa consulta ja foi realizada e nao pode ser desmarcada.\n");
    }
    else
    {
        printf("Consulta nao encontrada!\n");
    }
}

void consultar(Listaconsultas *listac, char cpf[], int dia, int mes, int ano, int hora, int min){
    Consulta *p = listac->inicio;
    bool realizada = false;
    while (p != NULL){
        if (p->paciente != NULL && strcmp(cpf, p->paciente->cpf) == 0 && p->data.dia == dia && p->data.mes == mes && p->data.ano == ano && p->data.hora == hora && p->data.min == min){
            
            if (p->status == false){
                realizada = true;
                p = p->prox;
                continue;
            }
            printf("Digite a descricao da consulta: ");
            limpar_buffer();
            ler_linha(p->descricao, sizeof(p->descricao));

            p->status = false;

            printf("Consulta registrada como realizada!\n");
            return;
        }

        p = p->prox;
    }

    if (realizada)
    {
        printf("Essa consulta ja foi realizada.\n");
    }
    else
    {
        printf("Consulta nao encontrada!\n");
    }
}

void listar_consultas(Listaconsultas * listac){
    Consulta *p = listac->inicio;
    while(p!= NULL){
        printf("Paciente: %s\n", p->paciente->nome);
        printf("Médico: %s\n", p->medico->nome);
        printf("Data: %d/%d/%d\n", p->data.dia, p->data.mes, p->data.ano);
        printf("Hora: %d:%d\n", p->data.hora, p->data.min);
        printf("Convênio: %s\n", p->convenio);
        if(p->status == true){
            printf("Status: Agendada\n");
        }
        else{
            printf("Status: Realizada\n");
            printf("Descrição: %s\n", p->descricao);
        }
        printf("----------------\n");
        p = p->prox;
    }
}

//---------------------------//----------------------------//
//--------- Códigos para relatórios ---------//

void relatorio1(Listaconsultas *listac, int dia, int mes, int ano)
{
    Consulta *p = listac->inicio;
    bool encontrou = false;

    printf("Consultas agendadas em %02d/%02d/%d:\n", dia, mes, ano);

    while (p != NULL)
    {
        if (p->status == true &&
            p->data.dia == dia &&
            p->data.mes == mes &&
            p->data.ano == ano)
        {
            printf("Paciente: %s\n", p->paciente->nome);
            printf("Medico: %s\n", p->medico->nome);
            printf("Horario: %02d:%02d\n", p->data.hora, p->data.min);
            printf("Convenio: %s\n", p->convenio);
            printf("----------------\n");

            encontrou = true;
        }

        p = p->prox;
    }

    if (!encontrou)
    {
        printf("Nenhuma consulta agendada nessa data.\n");
    }
}

void relatorio2(Listaconsultas *listac, char nome[])
{
    Consulta *p = listac->inicio;
    bool encontrou = false;

    printf("Consultas realizadas por %s:\n", nome);

    while (p != NULL)
    {
        if (p->status == false && p->paciente != NULL && strcmp(p->paciente->nome, nome) == 0)
        {
            printf("Medico: %s\n", p->medico->nome);
            printf("Data: %02d/%02d/%d\n", p->data.dia, p->data.mes, p->data.ano);
            printf("Horario: %02d:%02d\n", p->data.hora, p->data.min);
            printf("Descricao: %s\n", p->descricao);
            printf("----------------\n");

            encontrou = true;
        }

        p = p->prox;
    }
    if (!encontrou)
    {
        printf("Nenhuma consulta realizada encontrada para esse paciente.\n");
    }
}

void relatorio3(Listaconsultas * listac, char nome[], int dia, int mes, int ano, int hora, int min){
    Consulta *p = listac->inicio;
    printf("Descrição da consulta do paciente %s no dia %d/%d/%d às %d:%d:\n", nome, dia, mes, ano, hora, min);
    while(p!= NULL){
        if(strcmp(p->paciente->nome, nome) == 0 && p->data.dia == dia && p->data.mes == mes && p->data.ano == ano && p->data.hora == hora && p->data.min == min){
            if(p->status == true){
                printf("A consulta ainda não foi realizada. Status: Agendada\n");
            }
            else{
                printf("Descrição: %s\n", p->descricao);
            }
            printf("----------------\n");
        }
        p = p->prox;
    }
}

void relatorio4(Listaconsultas *listac, char especialidade[], int mes){
    Consulta *p = listac->inicio;
    bool encontrou = false;
    printf("Pacientes atendidos na especialidade %s no mes %d:\n",  especialidade, mes);

    while (p != NULL){
        if (p->status == false && p->medico != NULL &&  p->paciente != NULL && strcmp(p->medico->especialidade, especialidade) == 0 && p->data.mes == mes){
            bool repetido = false;
            Consulta *q = listac->inicio;

            while (q != p){
                if (q->status == false && q->paciente == p->paciente && q->medico != NULL && strcmp(q->medico->especialidade, especialidade) == 0 && q->data.mes == mes){
                    repetido = true;
                    break;
                }

                q = q->prox;
            }

            if (!repetido)
            {
                printf("Paciente: %s\n", p->paciente->nome);
                encontrou = true;
            }
        }

        p = p->prox;
    }

    if (!encontrou)
    {
        printf("Nenhum paciente encontrado nesse mes e especialidade.\n");
    }
}

void relatorio5(Listaconsultas *listac, Listamedicos *listam){
    medicos *m = listam->inicio;

    if(m == NULL){
        printf("Nenhum medico cadastrado.\n");
        return;
    }

    while(m != NULL){
        Consulta *p = listac->inicio;
        bool encontrou = false;

        printf("\nPacientes atendidos pelo medico %s:\n", m->nome);

        while(p != NULL){
            if (p->status == false && p->medico == m && p->paciente != NULL){
                bool repetido = false;
                Consulta *q = listac->inicio;

                while(q != p){
                    if(q->status == false && q->medico == m && q->paciente == p->paciente){
                        repetido = true;
                        break;
                    }
                    q = q->prox;
                }

                if(!repetido){
                    printf("Paciente: %s\n", p->paciente->nome);
                    encontrou = true;
                }
            }

            p = p->prox;
        }

        if (!encontrou)
        {
            printf("Nenhum atendimento realizado por esse medico.\n");
        }
        m = m->prox;
    }
}
void limpar_buffer(void){
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {}
}
void ler_linha(char texto[], size_t tamanho){
    if (fgets(texto, tamanho, stdin) == NULL)
    {
        texto[0] = '\0';
        return;
    }

    if (strchr(texto, '\n') == NULL)
    {
        limpar_buffer();
    }

    texto[strcspn(texto, "\n")] = '\0';
}
void liberar_lista_medicos(Listamedicos *lista){
    if(lista == NULL){
        return;
    }
    medicos *p = lista->inicio;

    while(p != NULL){
        medicos *prox = p->prox;
        free(p);
        p = prox;
    }

    free(lista);
}

void liberar_lista_pacientes(Listapacientes *lista){
    if(lista == NULL){
        return;
    }

    pacientes *p = lista->inicio;

    while(p != NULL){
        pacientes *prox = p->prox;
        free(p);
        p = prox;
    }

    free(lista);
}

void liberar_lista_consultas(Listaconsultas *lista){
    if(lista == NULL){
        return;
    }
    Consulta *p = lista->inicio;

    while(p != NULL){
        Consulta *prox = p->prox;
        free(p);
        p = prox;
    }

    free(lista);
}