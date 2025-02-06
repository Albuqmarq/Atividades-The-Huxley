#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NODES 1000
#define MAX_CHARS 1000

typedef struct No
{
    int id;
    int grau_in;
    char rotulo[MAX_CHARS + 1];
    struct No *prox;
} No;

typedef struct Grafo
{
    int tam;
    No **adj;
} Grafo;

typedef int (*Verifica)(No *, int);

Grafo *criar_g()
{
    Grafo *g = malloc(sizeof(Grafo));
    g->adj = malloc(MAX_NODES * sizeof(No *));
    g->tam = MAX_NODES;

    for (int i = 0; i < MAX_NODES; i++)
    {
        g->adj[i] = NULL;
    }

    return g;
}
 
No *insere_ordenado(No *head, const char rotulo[MAX_CHARS + 1], int grau_in)
{
    No *novo = malloc(sizeof(No));
    novo->grau_in = grau_in;
    strcpy(novo->rotulo, rotulo);
    novo->prox = NULL;

    if (head == NULL)
    {
        return novo;
    }

    No *ant = NULL;
    No *atual = head;

    while ((atual != NULL) && (strcmp(atual->rotulo, rotulo) < 0))
    {
        ant = atual;
        atual = atual->prox;
    }

    if (ant != NULL)
    {
        ant->prox = novo;
        novo->prox = atual;
    }
    else
    {
        novo->prox = atual;
        head = novo;
    }

    return head;
}

No *remover_no(No *head, int id, Verifica v)
{
    if (head == NULL) return head;
    
    No *ant = NULL;
    No *atual = head;

    while ((atual != NULL) && (v(atual, id)))
    {
        ant = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        return head;
    }

    if (ant == NULL)
    {
        head = head->prox;
    }
    else
    {
        ant->prox = atual->prox;
    }

    return head;
}

int verifica_id(No *n, int id)
{
    return n->id != id;
}
 
int verifica_grau_in(No *n, int grau_in)
{
    return n->grau_in != grau_in;
}
 
void imprimir_lista(No *head)
{
    No *aux = head;

    while (aux != NULL)
    {
        printf("%s\n", aux->rotulo);
        aux = aux->prox;
    }
}

int busca_grau_in(No *head, const char rotulo[])
{
    No *aux = head;

    while (aux != NULL && (strcmp(aux->rotulo, rotulo) != 0))
    {
        aux = aux->prox;
    }

    return (aux != NULL) ? aux->grau_in : -1;
}

void busca_profundidade(Grafo *g, No *inicio, int tam)
{
    while (inicio != NULL)
    {
        int grau_in, i;
        No *ordenada = NULL;
        No *atual = inicio;

        while (atual != NULL)
        {
            grau_in = busca_grau_in(inicio, atual->rotulo);

            if (g->adj[grau_in] == NULL)
            {
                ordenada = insere_ordenado(ordenada, atual->rotulo, grau_in);
            }

            atual = atual->prox;
        }

        imprimir_lista(ordenada);
        atual = ordenada;

        while (atual != NULL)
        {
            for (i = 0; i < tam; i++)
            {
                g->adj[i] = remover_no(g->adj[i], atual->grau_in, verifica_id);
            }

            inicio = remover_no(inicio, atual->grau_in, verifica_grau_in);
            atual = atual->prox;
        }
    }
}

void adicionar_aresta(Grafo *g, int origem, int destino)
{
    No *novo = malloc(sizeof(No));
    novo->id = destino;
    novo->prox = g->adj[origem];
    g->adj[origem] = novo;
    novo->grau_in = 0;
}

int main()
{
    int n, tam, i, origem, destino;
    char rotulo_origem[100];
    char rotulo_destino[100];

    while (scanf("%d", &n) != EOF)
    {
        Grafo *g = criar_g();
        No *nodes = NULL;
        tam = 0;

        for (i = 0; i < n; i++)
        {
            scanf("%s %s", rotulo_origem, rotulo_destino);

            origem = busca_grau_in(nodes, rotulo_origem);

            if (origem == -1)
            {
                nodes = insere_ordenado(nodes, rotulo_origem, tam);
                origem = tam;
                tam++;
            }

            destino = busca_grau_in(nodes, rotulo_destino);

            if (destino == -1)
            {
                nodes = insere_ordenado(nodes, rotulo_destino, tam);
                destino = tam;
                tam++;
            }
            adicionar_aresta(g, origem, destino);
        }

        busca_profundidade(g, nodes, tam);
    }

    return 0;
}
