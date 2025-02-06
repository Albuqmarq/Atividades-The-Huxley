#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Nodo
{
    int valor;
    struct Nodo *proximo;
} Nodo;

typedef struct TabelaHash
{
    int capacidade;
    Nodo **buckets;
    int qtd_itens;
    int *tamanho_bucket;
} TabelaHash;

int calcular_indice(int valor, int capacidade)
{
    return valor % capacidade;
}

TabelaHash *criar_tabela_hash(int capacidade)
{
    TabelaHash *tabela = calloc(1, sizeof(TabelaHash));

    tabela->capacidade = capacidade;
    tabela->qtd_itens = 0;
    tabela->buckets = calloc(capacidade, sizeof(Nodo*));
    tabela->tamanho_bucket = calloc(capacidade, sizeof(int));

    for (int i = 0; i < capacidade; i++)
    {
        tabela->buckets[i] = NULL;
        tabela->tamanho_bucket[i] = 0;
    }

    return tabela;
}

int verificar_existencia(TabelaHash *tabela, int valor, int *contador_acessos)
{
    int indice = calcular_indice(valor, tabela->capacidade);
    Nodo *atual = tabela->buckets[indice];

    while (atual != NULL)
    {
        (*contador_acessos)++;

        if (atual->valor == valor)
        {
            return 1;
        }

        atual = atual->proximo;
    }

    return 0;
}

int inserir_item(TabelaHash *tabela, int valor, int *contador_acessos)
{
    int indice = calcular_indice(valor, tabela->capacidade);

    if (verificar_existencia(tabela, valor, contador_acessos))
    {
        return 0;
    }

    Nodo *novo_nodo = calloc(1, sizeof(Nodo));
    novo_nodo->valor = valor;
    novo_nodo->proximo = tabela->buckets[indice];
    tabela->buckets[indice] = novo_nodo;

    tabela->tamanho_bucket[indice]++;
    tabela->qtd_itens++;

    return 1;
}

int remover_item(TabelaHash *tabela, int valor, int *contador_acessos)
{
    int indice = calcular_indice(valor, tabela->capacidade);
    Nodo *atual = tabela->buckets[indice];
    Nodo *anterior = NULL;

    while (atual != NULL && atual->valor != valor)
    {
        (*contador_acessos)++;
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL && atual->valor == valor)
    {
        (*contador_acessos)++;

        if (anterior)
        {
            anterior->proximo = atual->proximo;
        }
        else
        {
            tabela->buckets[indice] = atual->proximo;
        }

        tabela->qtd_itens--;
        tabela->tamanho_bucket[indice]--;
        free(atual);
        return 1;
    }

    return 0;
}

TabelaHash *reorganizar_tabela(TabelaHash *tabela_antiga, int nova_capacidade)
{
    TabelaHash *nova_tabela = criar_tabela_hash(nova_capacidade);
    int contador_acessos = 0;

    for (int i = 0; i < tabela_antiga->capacidade; i++)
    {
        Nodo *atual = tabela_antiga->buckets[i];

        while (atual != NULL)
        {
            inserir_item(nova_tabela, atual->valor, &contador_acessos);
            atual = atual->proximo;
        }
    }

    return nova_tabela;
}

int encontrar_maior_bucket(int *array_tamanho, int tamanho)
{
    int maior = INT_MIN;

    for (int i = 0; i < tamanho; i++)
    {
        if (array_tamanho[i] > maior)
        {
            maior = array_tamanho[i];
        }
    }

    return maior;
}

void remover_nova_linha(char *str)
{
    int pos = strcspn(str, "\n");
    str[pos] = '\0';
}

int main()
{
    int i, capacidade_inicial = 7, valor, acessos;
    double fator_carga;

    TabelaHash *tabela = criar_tabela_hash(capacidade_inicial);
    char comando[5];

    for (i = 0; scanf("%s", comando) != EOF; i++)
    {
        acessos = 0;
        remover_nova_linha(comando);

        if (comando[0] == 'A')
        {
            scanf("%d", &valor);
            int sucesso = inserir_item(tabela, valor, &acessos);

            fator_carga = (double) tabela->qtd_itens / tabela->capacidade;
            if (fator_carga >= 0.75)
            {
                tabela = reorganizar_tabela(tabela, 2 * tabela->capacidade - 1);
            }

            printf("%d %d %d\n", i, sucesso, acessos);
        }
        else if (comando[0] == 'D')
        {
            scanf("%d", &valor);
            int sucesso = remover_item(tabela, valor, &acessos);
            printf("%d %d %d\n", i, sucesso, acessos);
        }
        else if (comando[0] == 'H')
        {
            scanf("%d", &valor);
            int sucesso = verificar_existencia(tabela, valor, &acessos);
            printf("%d %d %d\n", i, sucesso, acessos);
        }
        else if (comando[0] == 'P')
        {
            printf("%d %d %d %d\n", i, tabela->capacidade, tabela->qtd_itens, encontrar_maior_bucket(tabela->tamanho_bucket, tabela->capacidade));
        }
    }

    return 0;
}
