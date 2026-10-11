============================================================
UNIVERSIDADE FEDERAL DE SANTA MARIA (UFSM)
Curso: Ciencia da Computacao
Disciplina: Laboratorio de Programacao II
Trabalho 4 - Sistema de agendamento de consultas de uma clinica medica
Autores: Stephan Coelho Parode
         Joao Pedro de Brito Canabarro
============================================================

1. ARQUIVOS ENTREGUES
---------------------
- main.c   : menu de opcoes e laco principal do programa.
- lista.h  : definicao das structs e prototipos das funcoes.
- lista.c  : implementacao das listas encadeadas, cadastros,
             consultas, buscas, relatorios e funcoes auxiliares.
- readme.txt : este arquivo.

Para compilar (Code::Blocks ou gcc): incluir main.c e lista.c
no mesmo projeto. Exemplo: gcc main.c lista.c -o clinica


2. ESTRUTURAS DE DADOS
----------------------
Todos os dados sao armazenados em listas encadeadas, com structs
alocadas dinamicamente (malloc) e sem uso de variaveis globais.

- Medicos   : lista simplesmente encadeada (CRM, nome,
              especialidade, telefone).
- Pacientes : lista simplesmente encadeada (CPF, nome, telefone).
- Consultas : lista duplamente encadeada (paciente, medico, data,
              horario, convenio, status e descricao textual).

A consulta NAO replica dados de medicos e pacientes: ela guarda
apenas ponteiros para os registros ja cadastrados (restricao 6).
O status e um flag booleano: true = "agendada", false = "executada".
Toda a memoria e liberada ao sair do programa.


3. O QUE FOI IMPLEMENTADO
-------------------------
Menu de opcoes (main.c):
  [1]  Cadastrar medico
  [2]  Listar medicos
  [3]  Cadastrar paciente
  [4]  Listar pacientes
  [5]  Agendar consulta
  [6]  Desmarcar consulta
  [7]  Listar consultas
  [13] Realizar (executar) consulta
  [8]  R1 - Consultas agendadas em um dia
  [9]  R2 - Consultas realizadas por um paciente
  [10] R3 - Descricao textual de uma consulta
  [11] R4 - Pacientes por especialidade, mes e ano
  [12] R5 - Pacientes atendidos por cada medico
  [0]  Sair

Cadastros:
- Inclusao e listagem de medicos e de pacientes.
- Nao ha duplicidade: se o CRM (medico) ou o CPF (paciente) ja
  existir, o novo cadastro e descartado.

Consultas:
- Agendamento: exige medico (CRM) e paciente (CPF) previamente
  cadastrados (restricao 5). Sao informados data, horario e
  convenio. A consulta nasce com status "agendada".
- Restricao 1: horarios apenas de 30 em 30 minutos (minutos 0 ou
  30), entre 8h-12h e 14h-18h (ultimo horario: 11:30 e 17:30).
  Nao permite duas consultas agendadas do mesmo medico no mesmo
  dia e horario.
- Restricao 2: o mesmo paciente nao pode ter duas consultas
  agendadas no mesmo dia e horario, mesmo com medicos diferentes.
- Desmarcar (restricao 4): informando CPF do paciente e data/
  horario; a consulta e removida da lista (o horario fica livre).
  Consultas ja realizadas nao podem ser desmarcadas.
- Realizar consulta: exige agendamento previo; o usuario digita a
  descricao textual (exames, medicamentos, observacoes -
  restricao 3) e o status muda para "executada".
- Listagem de todas as consultas, com status e descricao (quando
  executada).

Relatorios:
- R1: consultas agendadas em um dia informado.
- R2: consultas ja realizadas por um paciente (informado pelo CPF).
- R3: descricao textual de uma consulta (CPF do paciente + data/horario).
- R4: nomes dos pacientes (sem repeticao) que consultaram com
  medicos de uma especialidade em um mes e ano informados.
- R5: para cada medico, nomes (sem repeticao) dos pacientes que
  ja consultaram com ele.

Requisitos gerais atendidos: codigo dividido em arquivos e
funcoes com passagem de parametros, sem variaveis globais, structs
alocadas dinamicamente e menu de opcoes.


4. OBSERVACOES
--------------
- Os dados nao sao gravados em arquivo: ao encerrar o programa,
  todos os cadastros e consultas sao perdidos (nao exigido no
  enunciado).
