#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int valor;
    struct nodo *proximo;
} nodo;

typedef struct grafo
{
    nodo **adjacencias;
    int qtd_vertices;
    int *predecessores;
    int *distancias;
} grafo;

typedef struct fila
{
    int *itens;
    int inicio;
    int fim;
    int tamanho;
    int capacidade;
} fila;

fila *criar_fila(int capacidade)
{
    fila *nova_fila = calloc(1, sizeof(fila));

    nova_fila->itens = calloc(capacidade, sizeof(int));
    nova_fila->tamanho = 0;
    nova_fila->capacidade = capacidade;
    nova_fila->inicio = 0;
    nova_fila->fim = 0;

    return nova_fila;
}

nodo *criar_nodo(int valor)
{
    nodo *novo_nodo = calloc(1, sizeof(nodo));

    novo_nodo->proximo = NULL;
    novo_nodo->valor = valor;

    return novo_nodo;
}

grafo *criar_grafo(int vertices)
{
    grafo *novo_grafo = calloc(1, sizeof(grafo));

    novo_grafo->distancias = calloc(vertices, sizeof(int));
    novo_grafo->predecessores = calloc(vertices, sizeof(int));
    novo_grafo->adjacencias = calloc(vertices, sizeof(nodo *));
    novo_grafo->qtd_vertices = vertices;

    for (int i = 0; i < vertices; i++)
    {
        novo_grafo->distancias[i] = 0;
        novo_grafo->predecessores[i] = 0;
        novo_grafo->adjacencias[i] = NULL;
    }

    return novo_grafo;
}

int fila_vazia(fila *f)
{
    return (f->tamanho == 0);
}

void enfileirar(fila *f, int valor)
{
    f->itens[f->fim] = valor;
    f->tamanho++;
    f->fim++;
}

int desenfileirar(fila *f)
{
    int valor = f->itens[f->inicio];
    f->tamanho--;
    f->inicio = ((f->inicio + 1) % f->capacidade);

    return valor;
}

void adicionar_aresta(grafo *g, int inicio, int destino)
{
    nodo *novo_nodo = criar_nodo(destino);

    if (g->adjacencias[inicio] == NULL || destino <= g->adjacencias[inicio]->valor)
    {
        novo_nodo->proximo = g->adjacencias[inicio];
        g->adjacencias[inicio] = novo_nodo;
        return;
    }

    nodo *atual = g->adjacencias[inicio];
    nodo *anterior = NULL;

    while (atual && destino > atual->valor)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    novo_nodo->proximo = atual;
    anterior->proximo = novo_nodo;
}

void busca_largura(grafo *g, int inicio)
{
    int qtd_vertices = g->qtd_vertices;

    fila *f = criar_fila(qtd_vertices);

    for (int i = 0; i < qtd_vertices; i++)
    {
        g->predecessores[i] = -1;
        g->distancias[i] = -1;
    }

    g->distancias[inicio] = 0;
    enfileirar(f, inicio);

    while (!fila_vazia(f))
    {
        int atual = desenfileirar(f);

        printf("Iniciando busca em largura a partir de %d\n", atual);

        nodo *adjacente = g->adjacencias[atual];

        while (adjacente != NULL)
        {
            int adj = adjacente->valor;

            if (g->distancias[adj] == -1)
            {
                g->distancias[adj] = g->distancias[atual] + 1;
                g->predecessores[adj] = atual;
                enfileirar(f, adj);
            }

            adjacente = adjacente->proximo;
        }
    }
    printf("\n");

    free(f->itens);
    free(f);
}

void imprimir_caminho(int pred[], int inicio, int fim)
{
    if (inicio == fim)
    {
        printf("%d", inicio);
    }
    else
    {
        imprimir_caminho(pred, inicio, pred[fim]);
        printf(" => %d", fim);
    }
}

int main()
{
    int qtd_vertices, qtd_arestas, qtd_testes, x, vertice_x, vertice_y, vertice_inicial, vertice_final;
    scanf("%d %d %d", &qtd_vertices, &qtd_arestas, &qtd_testes);
    grafo *g = criar_grafo(qtd_vertices);

    for (x = 1; x <= qtd_arestas; x++)
    {
        scanf("%d %d", &vertice_x, &vertice_y);
        adicionar_aresta(g, vertice_x, vertice_y);
    }

    for (int teste = 1; teste <= qtd_testes; teste++)
    {
        scanf("%d %d", &vertice_inicial, &vertice_final);

        puts("");
        puts("--------");
        puts("");
        printf("Caso de Teste #%d - BFS(%d)\n", teste, vertice_inicial);
        puts("");

        busca_largura(g, vertice_inicial);

        for (x = 0; x < qtd_vertices; x++)
        {
            if (g->distancias[x] == -1)
            {
                printf("%d | - | -\n", x);
            }
            else if (g->distancias[x] == 0)
            {
                printf("%d | %d | -\n", x, g->distancias[x]);
            }
            else
            {
                printf("%d | %d | %d\n", x, g->distancias[x], g->predecessores[x]);
            }
        }

        if (g->distancias[vertice_final] == -1)
        {
            printf("\nSem caminho entre %d e %d\n", vertice_inicial, vertice_final);
        }
        else
        {
            puts("");
            printf("Caminho entre %d e %d: ", vertice_inicial, vertice_final);
            imprimir_caminho(g->predecessores, vertice_inicial, vertice_final);
            puts("");
        }
    }

    printf("\n");
    printf("--------\n");

    return 0;
}
