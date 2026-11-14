#include <stdio.h>
#include <stdlib.h>
#include "restaurante.h"
#include <stdbool.h>
#include <string.h>

struct mesa
{
    int identificacao;
    bool ocupado;
    int pessoas;
    int comanda;
    int pratos;
};

typedef struct pratos
{
    struct pratos *prox;
} Prato;

struct pilha
{
    Prato *topo;
    int quantidade;
};

typedef struct grupo
{
    int senha;
    int pessoas;
    struct grupo *prox;
} Grupo;

struct fila
{
    Grupo *ini;
    Grupo *fim;
    int proxima_senha;
};

// MESA

Mesa **inicializa_mesa(int l, int c)
{
    if (l <= 0 || c <= 0)
    {
        return NULL;
    }

    Mesa **mesas = malloc(sizeof(Mesa *) * l);
    if (mesas == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < l; i++)
    {
        mesas[i] = malloc(sizeof(Mesa) * c);
        if (mesas[i] == NULL)
        {
            libera_mesa(mesas, i);
            return NULL;
        }
    }

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            mesas[i][j].ocupado = false;
            mesas[i][j].pessoas = 0;
            mesas[i][j].comanda = 0;
            mesas[i][j].pratos = 4;
            mesas[i][j].identificacao = i * c + j + 1;
        }
    }
    return mesas;
}

void libera_mesa(Mesa **mesas, int l)
{
    if (mesas == NULL)
        return;
    for (int j = 0; j < l; j++)
    {
        free(mesas[j]);
    }
    free(mesas);
}

// PRATOS

Pilha *inicializa_pilha_pratos(void)
{
    Pilha *p = malloc(sizeof(Pilha));

    if (p == NULL)
        return NULL;

    p->topo = NULL;
    p->quantidade = 0;

    return p;
}

bool push_pratos(Pilha *pratos)
{
    if (pratos == NULL)
    {
        return false;
    }
    Prato *novo_prato = malloc(sizeof(Prato));

    if (novo_prato == NULL)
    {
        return false;
    }

    novo_prato->prox = pratos->topo;
    pratos->topo = novo_prato;
    pratos->quantidade++;
    return true;
}

bool pop_pratos(Pilha *pratos)
{
    if (pratos == NULL)
    {
        return false;
    }
    Prato *prato_free = pratos->topo;
    if (prato_free == NULL)
    {
        return false;
    }

    pratos->topo = prato_free->prox;
    free(prato_free);
    pratos->quantidade -= 1;

    return true;
}

void repor_pratos(Pilha *p, int quantidade)
{
    if (quantidade <= 0)
    {
        return;
    }
    if (p == NULL)
    {
        return;
    }
    int adicionados = 0;

    for (int i = 0; i < quantidade; i++)
    {
        if (!push_pratos(p))
        {
            break;
        }
        adicionados++;
    }
    printf("Pratos adicionados: %d\n", adicionados);
    printf("Total na pilha: %d\n", p->quantidade);
}

void imprimir_pilha(Pilha *p)
{
    printf("Pratos na pilha: %d\n", p->quantidade);
}

void libera_pilha(Pilha *p)
{
    if (p == NULL)
    {
        return;
    }

    Prato *pratos = p->topo;

    while (pratos != NULL)
    {
        Prato *prato_aux = pratos;
        pratos = pratos->prox;
        free(prato_aux);
    }
    free(p);
}

Fila *inicializa_fila(void)
{
    Fila *f = malloc(sizeof(Fila));

    if (f == NULL)
    {
        return NULL;
    }

    f->ini = NULL;
    f->fim = NULL;
    f->proxima_senha = 1;

    return f;
}

// imprimir mesa

void imprimir_mesa(Mesa **mesa, int l, int c, int id)
{
    if (id < 1 || id > l * c)
    {
        printf("Mesa inexistente.\n");
        return;
    }
    Mesa *m = &mesa[(id - 1) / c][(id - 1) % c];
    if (m->ocupado)
    {
        printf("Mesa %d: ocupada, %d pessoa(s), comanda %d\n", m->identificacao, m->pessoas, m->comanda);
    }
    else
    {
        printf("Mesa %d: livre\n", m->identificacao);
    }
}
void imprimir_todas_mesas(Mesa **mesas, int l, int c)
{
    if (l <= 0 || c <= 0)
    {
        printf("ERRO!\n");
        return;
    }
    if (mesas == NULL)
    {
        printf("Matriz de mesas inexistente.\n");
        return;
    }

    for (int i = 1; i <= l * c; i++)
    {
        imprimir_mesa(mesas, l, c, i);
    }
}
static Mesa *mesa_livre(Mesa **mesas, int l, int c)
{
    if (mesas == NULL || l <= 0 || c <= 0)
    {
        return NULL;
    }

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (!mesas[i][j].ocupado && mesas[i][j].pratos == 4)
            {
                return &mesas[i][j];
            }
        }
    }
    return NULL;
}

static bool ocupa_mesa(Mesa *m, int n, Pilha *p)
{
    if (m == NULL || p == NULL || n < 1 || n > 4)
    {
        return false;
    }

    if (m->ocupado || m->pratos != 4)
    {
        return false;
    }

    int excedentes = 4 - n;
    int adicionados = 0;

    for (int i = 0; i < excedentes; i++)
    {
        if (!push_pratos(p))
        {
            while (adicionados > 0)
            {
                pop_pratos(p);
                adicionados--;
            }

            return false;
        }

        adicionados++;
    }

    m->ocupado = true;
    m->pessoas = n;
    m->comanda = m->identificacao;
    m->pratos = n;

    printf("Mesa %d ocupada por %d pessoa(s).\n", m->identificacao, n);

    return true;
}

// FILA

static bool fila_vazia(Fila *f)
{
    return f == NULL || f->ini == NULL;
}

int enfileirar_grupo(Fila *f, int pessoas)
{
    if (f == NULL || pessoas <= 0)
    {
        return 0;
    }

    Grupo *novo = malloc(sizeof(Grupo));
    if (novo == NULL)
    {
        return 0;
    }

    novo->senha = f->proxima_senha++;
    novo->pessoas = pessoas;
    novo->prox = NULL;

    if (f->fim == NULL)
    {
        f->ini = novo;
    }
    else
    {
        f->fim->prox = novo;
    }
    f->fim = novo;

    return novo->senha;
}

void imprimir_fila(Fila *f)
{
    if (f == NULL)
    {
        printf("Fila inexistente.\n");
        return;
    }

    int grupos = 0, total = 0;

    for (Grupo *g = f->ini; g != NULL; g = g->prox)
    {
        printf("Grupo %d aguarda por %d lugar(es)\n", g->senha, g->pessoas);
        grupos++;
        total += g->pessoas;
    }

    if (grupos == 0)
    {
        printf("Fila de espera vazia.\n");
        return;
    }
    printf("%d grupo(s) na fila, %d pessoa(s) aguardando.\n", grupos, total);
}

void libera_fila(Fila *f)
{
    if (f == NULL)
    {
        return;
    }

    Grupo *g = f->ini;
    while (g != NULL)
    {
        Grupo *aux = g;
        g = g->prox;
        free(aux);
    }
    free(f);
}

void chegar_clientes(Mesa **mesas, int l, int c, Pilha *p, Fila *f, int pessoas)
{
    if (mesas == NULL || p == NULL || f == NULL)
    {
        printf("Restaurante nao inicializado.\n");
        return;
    }
    if (pessoas <= 0)
    {
        printf("Quantidade de pessoas invalida.\n");
        return;
    }

    int restante = pessoas;

    if (fila_vazia(f))
    {
        while (restante > 0)
        {
            Mesa *m = mesa_livre(mesas, l, c);
            if (m == NULL)
            {
                break;
            }

            int n = (restante > 4) ? 4 : restante;
            if (!ocupa_mesa(m, n, p))
            {
                break;
            }
            restante -= n;
        }
    }

    if (restante == 0)
    {
        printf("Grupo de %d pessoa(s) acomodado.\n", pessoas);
        return;
    }

    int senha = enfileirar_grupo(f, restante);
    if (senha == 0)
    {
        printf("Erro ao colocar o grupo na fila.\n");
        return;
    }

    if (restante < pessoas)
    {
        printf("%d pessoa(s) sentaram; %d aguardam na fila com a senha %d.\n",
               pessoas - restante, restante, senha);
    }
    else
    {
        printf("Sem mesas disponiveis. Grupo de %d pessoa(s) na fila com a senha %d.\n",
               restante, senha);
    }
}

static void chama_fila(Mesa **mesas, int l, int c, Pilha *p, Fila *f)
{
    while (!fila_vazia(f))
    {
        Mesa *m = mesa_livre(mesas, l, c);
        if (m == NULL)
        {
            return;
        }

        Grupo *g = f->ini;
        int n = (g->pessoas > 4) ? 4 : g->pessoas;

        printf("Chamando a senha %d da fila: ", g->senha);
        if (!ocupa_mesa(m, n, p))
        {
            return;
        }

        g->pessoas -= n;
        if (g->pessoas == 0)
        {
            f->ini = g->prox;
            if (f->ini == NULL)
            {
                f->fim = NULL;
            }
            free(g);
        }
        else
        {
            printf("A senha %d continua na fila aguardando %d lugar(es).\n", g->senha, g->pessoas);
        }
    }
}

void finalizar_refeicao(Mesa **mesas, int l, int c, Pilha *p, Fila *f, int id)
{
    if (mesas == NULL || p == NULL || f == NULL)
    {
        printf("Restaurante nao inicializado.\n");
        return;
    }
    if (id < 1 || id > l * c)
    {
        printf("Mesa inexistente.\n");
        return;
    }

    Mesa *m = &mesas[(id - 1) / c][(id - 1) % c];
    if (!m->ocupado)
    {
        printf("A mesa %d ja esta livre.\n", id);
        return;
    }

    m->ocupado = false;
    m->pessoas = 0;
    m->comanda = 0;
    printf("Mesa %d liberada.\n", id);

    int falta = 4 - m->pratos;
    if (p->quantidade >= falta)
    {
        for (int i = 0; i < falta; i++)
        {
            pop_pratos(p);
        }
        m->pratos = 4;
    }
    else
    {
        printf("Pratos insuficientes para arrumar a mesa %d.\n", id);
    }
    chama_fila(mesas, l, c, p, f);
}

void desistir(Fila *f, int senha)
{
    if (f == NULL)
    {
        printf("Fila inexistente.\n");
        return;
    }

    Grupo *ant = NULL;
    Grupo *g = f->ini;

    while (g != NULL && g->senha != senha)
    {
        ant = g;
        g = g->prox;
    }

    if (g == NULL)
    {
        printf("Senha %d nao encontrada na fila.\n", senha);
        return;
    }

    if (ant == NULL)
    {
        f->ini = g->prox;
    }
    else
    {
        ant->prox = g->prox;
    }
    if (g == f->fim)
    {
        f->fim = ant;
    }

    free(g);
    printf("Grupo da senha %d saiu da fila.\n", senha);
}