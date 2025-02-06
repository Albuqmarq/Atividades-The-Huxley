#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvore
{
    int valor;
    struct arvore *direita;
    struct arvore *esquerda;
    struct arvore *pai;

} arvore;

arvore *inicializa_nulo()
{
    return NULL;
}

arvore *criar_arvore(int valor, arvore *esquerda, arvore *direita, arvore *pai)
{
    arvore *nova_arvore = malloc(sizeof(arvore));
    nova_arvore->valor = valor;
    nova_arvore->direita = direita;
    nova_arvore->esquerda = esquerda;
    nova_arvore->pai = pai;
    return nova_arvore;
}

int busca_valor(arvore *raiz, int valor_desejado, arvore **no_atual)
{
    *no_atual = raiz;

    if (raiz == NULL)
        return 0;

    if (raiz->valor == valor_desejado)
        return 1;

    return busca_valor(raiz->esquerda, valor_desejado, no_atual) || busca_valor(raiz->direita, valor_desejado, no_atual);
}

arvore *verificar_nulo(arvore *raiz, int valor_desejado, arvore **no_atual)
{
    if (busca_valor(raiz, valor_desejado, no_atual) == 1)
    {
        return raiz;
    }
    else
    {
        return NULL;
    }
}

arvore *construir_arvore(char expressao[], int *indice, arvore *pai)
{
    int i, valor;
    char buffer[100000];

    if ((expressao[*indice] == '(') && (expressao[*indice + 1] == ')'))
    {
        *indice += 2;
        return NULL;
    }
    else if (expressao[*indice] == '(')
    {
        *indice += 1;
    }

    i = 0;
    while (expressao[*indice] != '(' && expressao[*indice] != ')')
    {
        if (expressao[*indice] == ' ')
            (*indice)++;
        else
        {
            buffer[i++] = expressao[*indice];
            (*indice)++;
        }
    }

    buffer[i] = '\0';
    valor = atoi(buffer);

    arvore *raiz = criar_arvore(valor, NULL, NULL, pai);

    raiz->esquerda = construir_arvore(expressao, indice, raiz);
    raiz->direita = construir_arvore(expressao, indice, raiz);

    if (expressao[*indice] == ')')
    {
        (*indice)++;
    }

    return raiz;
}

void imprimir_arvore(arvore *raiz)
{
    if (raiz != NULL)
    {
        printf("(%d", raiz->valor);
        imprimir_arvore(raiz->esquerda);
        imprimir_arvore(raiz->direita);
        printf(")");
    }
    else
    {
        printf("()");
    }
}

int main()
{
    char expressao[100000];
    fgets(expressao, 1000, stdin);

    int tamanho_expressao = strlen(expressao);
    char expressao_limpa[100000];
    int i = 0, j = 0;

    for (i = 0; i < tamanho_expressao; i++)
    {
        if (expressao[i] != ' ')
        {
            expressao_limpa[j++] = expressao[i];
        }
    }

    i = 0;
    arvore *raiz = construir_arvore(expressao_limpa, &i, NULL);

    while (1)
    {
        char linha_auxiliar[1000];
        fgets(linha_auxiliar, 1000, stdin);
        int tamanho_linha = strlen(linha_auxiliar);

        if (tamanho_linha <= 3)
        {
            break;
        }

        char linha_limpa[1000];
        j = 0;

        for (i = 0; i < tamanho_linha; i++)
        {
            if (linha_auxiliar[i] != ' ')
            {
                linha_limpa[j++] = linha_auxiliar[i];
            }
        }

        int k = 0;
        arvore *nova_raiz = construir_arvore(linha_limpa, &k, NULL);

        int valor_novo = nova_raiz->valor;

        if (valor_novo != raiz->valor)
        {
            arvore *no_atual = NULL;
            arvore *verificacao_nulo = verificar_nulo(raiz, valor_novo, &no_atual);

            arvore *pai_atual;
            if ((no_atual->pai->esquerda) == no_atual)
            {
                pai_atual = no_atual->pai->esquerda;
                no_atual->pai->esquerda = nova_raiz;
                nova_raiz->pai = pai_atual;
            }
            else if ((no_atual->pai->direita) == no_atual)
            {
                pai_atual = no_atual->pai->direita;
                no_atual->pai->direita = nova_raiz;
                nova_raiz->pai = pai_atual;
            }
            else if (no_atual == NULL)
            {
                raiz = nova_raiz;
                imprimir_arvore(raiz);
            }
        }
        else
        {
            raiz = nova_raiz;
        }
    }

    imprimir_arvore(raiz);
    printf("\n");

    return 0;
}
