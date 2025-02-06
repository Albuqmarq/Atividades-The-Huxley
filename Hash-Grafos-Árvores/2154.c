#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Nodo
{
    int valor;
    struct Nodo *prox;
} Nodo;

typedef struct TabelaHash
{
    int tamanho;
    int capacidade;
    Nodo **lista;
} TabelaHash;

int calcular_indice_hash(int valor, int capacidade)
{
    return valor % capacidade;
}

TabelaHash *criar_tabela_hash(int capacidade)
{
    int i;

    TabelaHash *tabela = malloc(sizeof(TabelaHash));

    tabela->capacidade = capacidade;
    tabela->tamanho = 0;

    tabela->lista = malloc(capacidade * sizeof(Nodo *));

    for (i = 0; i < capacidade; i++)
    {
        tabela->lista[i] = NULL;
    }

    return tabela;
}

void inserir_tabela(TabelaHash *tabela, int valor)
{
    int indice;

    indice = calcular_indice_hash(valor, tabela->capacidade);

    Nodo *novo_nodo = malloc(sizeof(Nodo));

    novo_nodo->valor = valor;
    novo_nodo->prox = NULL;

    if (tabela->lista[indice] != NULL)
    {
        Nodo *atual = tabela->lista[indice];
        Nodo *anterior = NULL;

        while ((atual != NULL) && (atual->valor < valor))
        {
            anterior = atual;
            atual = atual->prox;
        }

        if (anterior == NULL)
        {
            novo_nodo->prox = tabela->lista[indice];
            tabela->lista[indice] = novo_nodo;
        }
        else
        {
            anterior->prox = novo_nodo;
            novo_nodo->prox = atual;
        }
    }
    else
    {
        tabela->lista[indice] = novo_nodo;
    }

    tabela->tamanho++;
}

void remover_tabela(TabelaHash *tabela, int valor)
{
    int indice;

    indice = calcular_indice_hash(valor, tabela->capacidade);

    Nodo *atual = tabela->lista[indice];
    Nodo *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->valor == valor)
        {
            if (anterior != NULL)
            {
                anterior->prox = atual->prox;
            }
            else
            {
                tabela->lista[indice] = atual->prox;
            }

            free(atual);

            tabela->tamanho--;

            return;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

int buscar_tabela(TabelaHash *tabela, int valor, int *iteracoes)
{
    int indice, acessos;

    indice = calcular_indice_hash(valor, tabela->capacidade);
    Nodo *atual = tabela->lista[indice];

    acessos = 0;

    while (atual != NULL)
    {
        acessos++;

        if (atual->valor == valor)
        {
            *iteracoes = acessos;
            return 1;
        }

        atual = atual->prox;
    }

    *iteracoes = acessos;

    return 0;
}

void imprimir_tabela(TabelaHash *tabela)
{
    int i;

    printf("imprimindo tabela hash:\n");

    for (i = 0; i < tabela->capacidade; i++)
    {
        printf("[%d]:", i);

        Nodo *atual = tabela->lista[i];

        if (atual != NULL)
        {
            while (atual != NULL)
            {
                printf("%d=>", atual->valor);
                atual = atual->prox;
            }
            printf("\n");
        }
        else
        {
            printf("Lista vazia!\n");
        }
    }
}

int main()
{
    int capacidade, valor, iteracoes;
    
    scanf("%d", &capacidade);

    TabelaHash *tabela = criar_tabela_hash(capacidade);

    char comando;

    scanf(" %c", &comando);

    while (comando != 'f')
    {
        if (comando != 'i')
        {
            getchar();
            scanf("%d", &valor);
        }

        if (comando == 'a')
        {
            inserir_tabela(tabela, valor);
        }
        else if (comando == 'r')
        {
            remover_tabela(tabela, valor);
        }
        else if (comando == 'i')
        {
            imprimir_tabela(tabela);
        }
        else if (comando == 'p')
        {
            printf("BUSCA POR %d\n", valor);
            printf("numero de elementos da tabela hash: %d\n", tabela->tamanho);

            if (buscar_tabela(tabela, valor, &iteracoes))
            {
                printf("elemento %d encontrado!\n", valor);
            }
            else
            {
                printf("elemento nao encontrado!\n");
            }

            printf("numero de elementos acessados na tabela hash: %d\n", iteracoes);
        }

        scanf(" %c", &comando);
    }
    
    return 0;
}
