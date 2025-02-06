#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct nodo
{

    int valor;
  
    struct nodo *filho_direito;

    struct nodo *filho_esquerdo;
} nodo;

void encontrar_maximos_por_nivel(int *maximos, nodo *ponto_raiz, int nivel_atual);

void encontrar_minimos_por_nivel(int *minimos, nodo *ponto_raiz, int nivel_atual);


void encontrar_minimos_por_nivel(int *minimos, nodo *ponto_raiz, int nivel_atual){
    if (ponto_raiz == NULL) {
        return;}
    
    if (ponto_raiz->valor < minimos[nivel_atual]){ minimos[nivel_atual] = ponto_raiz->valor;
    }
    encontrar_minimos_por_nivel(minimos, ponto_raiz->filho_esquerdo, (nivel_atual + 1));

    encontrar_minimos_por_nivel(minimos, ponto_raiz->filho_direito, (nivel_atual + 1));
}

void encontrar_maximos_por_nivel(int *maximos, nodo *ponto_raiz, int nivel_atual){
    if (ponto_raiz == NULL) {
        return;
    }
    
    if (ponto_raiz->valor > maximos[nivel_atual]){

    maximos[nivel_atual] = ponto_raiz->valor;}

    encontrar_maximos_por_nivel(maximos, ponto_raiz->filho_esquerdo, (nivel_atual + 1));

    encontrar_maximos_por_nivel(maximos, ponto_raiz->filho_direito, (nivel_atual + 1));
}
 
int calcular_profundidade_maxima(nodo *ponto_raiz){
    int profundidade_esquerda, profundidade_direita;

    if (ponto_raiz == NULL){ return 0;
    }
    profundidade_esquerda = calcular_profundidade_maxima(ponto_raiz->filho_esquerdo);

    profundidade_direita = calcular_profundidade_maxima(ponto_raiz->filho_direito);
        
    if (profundidade_esquerda > profundidade_direita){
        return (profundidade_esquerda + 1);
    }
    else if (profundidade_esquerda <= profundidade_direita) {
        return (profundidade_direita + 1);
    }
}

void main(void)
{
    int indice;
    int quantidade_nos, entrada_valor;
    int indice_esquerda, indice_direita;
    int nivel_profundidade;
    int *maximos, *minimos = 0;
    nodo *ponto_raiz, **arvore_nos = 0;
   
    scanf("%d", &quantidade_nos);

    arvore_nos = malloc(quantidade_nos * sizeof(nodo *));

    for (indice = 0; indice < quantidade_nos; indice++)
    {
        arvore_nos[indice] = malloc(sizeof(nodo));
    }

    ponto_raiz = arvore_nos[0];

    for (indice = 0; indice < quantidade_nos; indice++)
    {
        scanf("%d%d%d", &entrada_valor, &indice_esquerda, &indice_direita);

        arvore_nos[indice]->valor = entrada_valor;

        if (indice_esquerda != -1)
        {
            arvore_nos[indice]->filho_esquerdo = arvore_nos[indice_esquerda];
        }
        else if(indice_esquerda == -1)
        {
            arvore_nos[indice]->filho_esquerdo = NULL;
        }

        if (indice_direita != -1)
        {
            arvore_nos[indice]->filho_direito = arvore_nos[indice_direita];
        }
        else if(indice_direita == -1)
        {
            arvore_nos[indice]->filho_direito = NULL;
        }
    }
 
    nivel_profundidade = calcular_profundidade_maxima(ponto_raiz);

    maximos = malloc(nivel_profundidade * sizeof(int));
    minimos = malloc(nivel_profundidade * sizeof(int));
    
    for (indice = 0; indice < nivel_profundidade; indice++)
    {
        maximos[indice] = INT_MIN;
        minimos[indice] = INT_MAX;
    }

    encontrar_maximos_por_nivel(maximos, ponto_raiz, 0);
    encontrar_minimos_por_nivel(minimos, ponto_raiz, 0);

    for (indice = 0; indice < nivel_profundidade; indice++)
    {
        printf("Nivel %d: ", (indice + 1));
        printf ("Maior = %d, ", maximos[indice]);
        printf ("Menor = %d\n", minimos[indice]);
    }

    return;
}
