#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 100

typedef struct pilha {
    ITEM vet[TAM];
    int topo;
} TPilha;

void create(TPilha *p) {
    p->topo = -1;
}

void destroy(TPilha *p) {
    p->topo = -1;
}

int isfull(TPilha *p) {
    return p->topo == TAM;
}

int isempty(TPilha *p) {
    return p->topo == -1;
}

void push(TPilha *p, ITEM x) {
    if( isfull(p) ) {
        puts("overflow");
        abort();
    }
    p->topo++;
    p->vet[p->topo] = x;
}

ITEM pop(TPilha *p) {
    if( isempty(p) ) {
        puts("underflow");
        abort();
    }
    ITEM x = p->vet[p->topo];
    p->topo--;
    return x;
}

ITEM top(TPilha *p) {
    if( isempty(p) ) {
        puts("underflow");
        abort();
    }
    return p->vet[p->topo];
}

void inverte_palavras_frase(char frase[]) {
TPilha p;
    create(&p);
    int j = 0,i,tamf;
    tamf=0;
    for(i=0;frase[i]!='\0';i++)
    {
        tamf=tamf+1;
    }
    for(i=0;i<=tamf;i++) 
    {
        if(frase[i] != ' ' && frase[i] != '\0'){
            push(&p, frase[i]);
        } 
        else
        {
            while (!isempty(&p)) 
            {
                frase[j++]=pop(&p);
            }
            if(frase[i] == ' ') frase[j++] = ' ';
        }
    }
}

int main(void) {
    char frase[TAM];

    gets(frase);
    printf("original = %s\n", frase);
    inverte_palavras_frase(frase);
    printf("invertida = %s\n", frase);
    
    return 0;
}
