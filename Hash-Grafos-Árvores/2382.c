#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArvoreBinaria
{
    int valor;
    struct ArvoreBinaria *direita;
    struct ArvoreBinaria *esquerda;

} ArvoreBinaria;

typedef struct Nodo
{
    int valor;
    int esquerda;
    int direita;
    struct Nodo *proximo;
} Nodo;

typedef struct NodoSimples
{
    int valor;
    struct NodoSimples *proximo;
} NodoSimples;

NodoSimples *inserir_nodo_simples(NodoSimples *cabeca, int valor)
{
    NodoSimples *novo_nodo = calloc(1, sizeof(NodoSimples));
    novo_nodo->valor = valor;
    novo_nodo->proximo = NULL;

    if (cabeca == NULL)
        return novo_nodo;
    else
    {
        NodoSimples *atual = cabeca;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = novo_nodo;
        return cabeca;
    }
}

Nodo *inserir_nodo(ArvoreBinaria *arvore, Nodo *cabeca)
{
    Nodo *novo_nodo = calloc(1, sizeof(Nodo));
    novo_nodo->valor = arvore->valor;

    if (arvore->esquerda != NULL)
    {
        novo_nodo->esquerda = arvore->esquerda->valor;
    }
    else
    {
        novo_nodo->esquerda = -1;
    }

    if (arvore->direita != NULL)
    {
        novo_nodo->direita = arvore->direita->valor;
    }
    else
    {
        novo_nodo->direita = -1;
    }

    novo_nodo->proximo = NULL;

    if (cabeca == NULL)
    {
        return novo_nodo;
    }
    else
    {
        Nodo *atual = cabeca;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = novo_nodo;
        return cabeca;
    }
}

Nodo *construir_lista_nodos(ArvoreBinaria *arvore, Nodo *lista)
{
    if (arvore != NULL)
    {
        lista = inserir_nodo(arvore, lista);
        construir_lista_nodos(arvore->esquerda, lista);
        construir_lista_nodos(arvore->direita, lista);
    }
    return lista;
}

NodoSimples *verificar_filhos(Nodo *cabeca, int *n_nos_completos, NodoSimples *cabeca_simples)
{
    if (cabeca == NULL)
    {
        return cabeca_simples;
    }

    if ((cabeca->esquerda >= 0 && cabeca->direita >= 0) || (cabeca->esquerda == -1 && cabeca->direita == -1))
    {
        (*n_nos_completos)++;
        verificar_filhos(cabeca->proximo, n_nos_completos, cabeca_simples);
    }
    else if ((cabeca->esquerda == -1 && cabeca->direita >= 0) || (cabeca->direita == -1 && cabeca->esquerda >= 0))
    {
        cabeca_simples = inserir_nodo_simples(cabeca_simples, cabeca->valor);
        verificar_filhos(cabeca->proximo, n_nos_completos, cabeca_simples);
    }
}

ArvoreBinaria *criar_arvore_binaria(int valor, ArvoreBinaria *esquerda, ArvoreBinaria *direita)
{
    ArvoreBinaria *nova_arvore = malloc(sizeof(ArvoreBinaria));
    nova_arvore->valor = valor;
    nova_arvore->direita = direita;
    nova_arvore->esquerda = esquerda;
    return nova_arvore;
}

ArvoreBinaria *construir_arvore(char entrada[], int *posicao, int *n_nos)
{
    int i, valor_numero;
    if (entrada[*posicao] == '(' && entrada[*posicao + 1] == ')')
    {
        *posicao += 2;
        return NULL;
    }
    else if (entrada[*posicao] == '(')
    {
        *posicao += 1;
    }

    char numeros[100000];
    i = 0;
    while (entrada[*posicao] != '(' && entrada[*posicao] != ')')
    {
        if (entrada[*posicao] == ' ')
            (*posicao)++;
        else
        {
            numeros[i] = entrada[*posicao];
            *posicao += 1;
            i++;
        }
    }

    numeros[i] = '\0';
    valor_numero = atoi(numeros);

    ArvoreBinaria *raiz = criar_arvore_binaria(valor_numero, NULL, NULL);
    (*n_nos)++;

    raiz->esquerda = construir_arvore(entrada, posicao, n_nos);
    raiz->direita = construir_arvore(entrada, posicao, n_nos);

    if (entrada[*posicao] == ')')
    {
        *posicao += 1;
    }

    return raiz;
}

void imprimir_arvore(ArvoreBinaria *raiz)
{
    if (raiz != NULL)
    {
        printf("(%d", raiz->valor);
    }
    else
    {
        printf("()");
    }

    if (raiz != NULL)
    {
        imprimir_arvore(raiz->esquerda);
        imprimir_arvore(raiz->direita);
        printf(")");
    }
}

void imprimir_nos_faltando(NodoSimples *cabeca)
{
    NodoSimples *atual = cabeca;

    while (atual != NULL)
    {
        if ((atual->valor == 8) && (atual->proximo != NULL) && (atual->proximo->valor == 7))
        {
            printf(" %d %d", atual->proximo->valor, atual->valor);
            atual = atual->proximo->proximo;
        }
        else
        {
            printf(" %d", atual->valor);
            atual = atual->proximo;
        }
    }

    printf("\n");
}

int main()
{
    int posicao, i, j, n_nos, n_nos_completos;
    char entrada[100000];

    fgets(entrada, 1000, stdin);
    posicao = strlen(entrada);

    char entrada_limpa[1000];
    j = 0;
    for (i = 0; i < posicao; i++)
    {
        if (entrada[i] != ' ')
        {
            entrada_limpa[j] = entrada[i];
            j++;
        }
    }

    i = 0;
    n_nos = 0;
    ArvoreBinaria *raiz = construir_arvore(entrada_limpa, &i, &n_nos);

    Nodo *lista_nodos = NULL;
    lista_nodos = construir_lista_nodos(raiz, lista_nodos);

    n_nos_completos = 0;
    NodoSimples *nos_faltando = NULL;
    nos_faltando = verificar_filhos(lista_nodos, &n_nos_completos, nos_faltando);

    if (n_nos_completos == n_nos)
    {
        printf("completa\n");
        printf("total de nos: %d\n", n_nos);
    }
    else
    {
        printf("nao completa\n");
        printf("nos com um filho:");
        imprimir_nos_faltando(nos_faltando);
    }

    return 0;
}
