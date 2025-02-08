#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TAM 5
struct no {
	int i;
	struct no *prox;
};

struct stack {
	struct no *lista;
	struct stack *prox;
};

void printar (struct no *num){
	while(num != NULL)
	{
        if(num->prox==NULL){
			printf("%d\n",num->i);
		}
		else if (num->prox != NULL){
			printf("%d ",num->i);
		}
		num=num->prox;
	}
}

struct stack *PUSH (struct stack *ponta, struct no *lista){

	struct stack *novaponta = (struct stack *) malloc(sizeof(struct stack));
	
	novaponta->lista=lista;

	novaponta->prox=ponta;
	
	return novaponta;
}



struct stack *POP (struct stack *novaponta){
	
    if(novaponta!=NULL){
	
	struct stack *ponta=novaponta;

	novaponta=novaponta->prox;

	ponta->prox=NULL;

	printar(ponta->lista);

	free(ponta);

	return novaponta;
    }
    else if (novaponta == NULL){
		printf("EMPTY STACK\n");
		return NULL;
	}
}


struct no *add (struct no *cabeca, int i){
	struct no *novono=(struct no *) malloc (sizeof(struct no));
	novono->i=i;	
	
	if (cabeca!=NULL){
		struct no *atual=cabeca;
		
		while(atual->prox != NULL){
			atual = atual->prox;
        }
		atual->prox = novono;
	}
    else if (cabeca==NULL){
		cabeca=novono;
	}
	return cabeca;
}

struct no *newlist (struct no *cabeca){
	int i;
	char string;

	scanf("%d%c", &i, &string);	
	
	cabeca = add(cabeca, i);
	
	if (string == ' '){
        newlist(cabeca);
    }
	
	return cabeca;
}

void funcao(struct stack *ponta){
	char palavra[TAM];
    struct no *num;
	if(scanf("%s",palavra)!=EOF)
	{
		if (palavra[1] =='U'){
			num=newlist(NULL);
			ponta=PUSH(ponta, num);
		}
		else if (palavra[1]=='O'){
			ponta=POP(ponta);
		}
		return funcao(ponta);
	}
}

int main (){

	funcao(NULL);
    
	return 0;
}
