typedef struct{
    char crm[7];
    char nome[20];
    char especialidade[20];
    char telefone[13];
    medicos *prox;
}medicos;

typedef struct{
    char cpf[16];
    char nome[20];
    char especialidade[20];
    char telefone[13];
}pacientes;
