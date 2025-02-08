#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _deque deque_t;
typedef struct _node   node_t;

//Guarda um ponteiro pro node anterior, para o proximo node e o valor guardado
struct _node {
	node_t *prev;
  	node_t *next;
  	int    value;
};

//Guarda um ponteiro para o primeiro node, um ponteiro para o ultimo node, e o tamanho do deque
struct _deque {
  	node_t *front;
  	node_t  *rear;
  	int      size;
};

//Cria um node que guarda os valores que s�o enfileirados no deque
node_t*  node_new     (int value);

//Cria um deque dinamicamente e retorna seu endere�o de memoria
deque_t* construct    ();
//Libera a mem�ria do conte�do e do pr�prio deque
void     destruct     (deque_t *deque);

//Retorna o tamanho do deque
int      size         (deque_t *deque);
//Retorna verdadeiro se o deque esta vazio, caso contr�rio, retorna falso
bool     empty        (deque_t *deque);

//Retorna o valor da frente da lista, retorna int_min quando a lista estiver vazia
int      front        (deque_t *deque);
//Retorna o valor do fim da lista, retorna int_min quando a lista estiver vazia
int      rear         (deque_t *deque);

//Cria um n� que guarda um valor e o adiciona ao fim do deque
void     enqueue_rear (deque_t *deque, int value);
//Cria um n� que guarda um valor e o adiciona ao inicio do deque
void     enqueue_front(deque_t *deque, int value);
//Retira o valor do final caso n�o esteja vazia
void     dequeue_rear (deque_t *deque);
//Retira o valor da frente caso n�o esteja vazia
void     dequeue_front(deque_t *deque);
//Limpa o conteudo do deque(deixa ele vazio)
void     erase        (deque_t *deque);

//Imprime o deque em uma unica linha, com os elementos separados por um espa�o,
//terminando com um \n, lembrando de respeitar os conceitos de fila.
void     print        (deque_t *deque);

int main() {
 	int i, num;
  	scanf("%d", &num);
  
  	deque_t* deque = construct();
  
  	int vector[num];
  	for(i = 0; i < num; ++i)
      	scanf("%d", &vector[i]);
  
  	for(i = 0; i < num; ++i)
      	enqueue_rear(deque, vector[i]);
  
 	printf("%d\n", front(deque));
  	printf("%d\n", rear (deque));
  
  	if(!empty(deque))
  		printf("The size of the deque %d\n", size(deque));
  	else
       	printf("The deque is empty\n");
  	
    scanf("%d", &num);
    for(i = 0; i < num; ++i)
       enqueue_front(deque, i);
  	print(deque);
    dequeue_front(deque);
    print(deque);
    dequeue_rear (deque);
    print(deque);
    
  	erase(deque);
  	for(i = 0; i < 3; ++i)
  		enqueue_rear(deque, i);
  		
  	print(deque);
    destruct(deque);
       
	return 0;
}






node_t *node_new(int valor){
    struct _node *novalor = (struct _node*)malloc(sizeof(struct _node));
    
    novalor->prev=NULL; 

    novalor->value=valor;

    novalor->next=NULL;

    return novalor;
}

deque_t *construct(){
    struct _deque *b = (struct _deque*)malloc(sizeof(struct _deque));
    
    b->rear =NULL;

    b->front = NULL;

    b->size = 0;

    return b;
}

void erase(deque_t *deque){
    while(deque->front!=NULL){

        node_t *t = deque->front;

        deque->front = deque->front->next;

        free(t);
    }
    deque->size=0;

    deque->rear=NULL;
    
}

void destruct(deque_t *deque){

    erase(deque);

    free(deque);

}

int size(deque_t *deque){

    return deque->size;

}

bool empty(deque_t *deque){
    if(deque->size == 0) return 1;
    
    else if (deque->size!=0) return 0;
    
}

int front(deque_t *deque){
    if(empty(deque)){
        return -1;
    } 
    else if(empty(deque)==NULL){
        return deque->front->value;
    }
}

int rear(deque_t *deque){
    if(empty(deque)){
        return -1;
    } 
    else if(empty(deque)==NULL){
        return deque->rear->value;
    }
}

void enqueue_rear(deque_t *deque, int valor){
    node_t *newvalue = node_new(valor);
    if(empty(deque)){
        deque->front=newvalue;
        deque->rear=newvalue;
    }
    else if (empty(deque)==NULL){
        deque->rear->next=newvalue;
        newvalue->prev=deque->rear;
        deque->rear=newvalue;
    }
    deque->size++;
}

void enqueue_front(deque_t *deque, int valor){
    node_t *newvalue = node_new(valor);
    if(empty(deque)){
        deque->front=newvalue;
        deque->rear=newvalue;
    }

    else if (empty(deque)==NULL){
        deque->front->prev=newvalue;

        newvalue->next=deque->front;

        deque->front=newvalue;
    }
    deque->size++;
}

void dequeue_rear(deque_t *deque){
    if(empty(deque)){
        return;
    } 
    node_t *t = deque->rear;
    deque->rear = deque->rear->prev;

    if(deque->rear!=NULL){

        deque->rear->next = NULL;
    } 
    else if(deque->rear==NULL){ 

        deque->front = NULL;
    }
    deque->size--;
}

void dequeue_front(deque_t *deque){
    if(empty(deque)!=NULL){
        return;
    } 
    node_t *t = deque->front;
    deque->front = deque->front->next;

    if(deque->front!=NULL){
        deque->front->prev = NULL;
    } 
    else if (deque->front==NULL){
        deque->rear = NULL;
    } 

    deque->size--;
}

void print(deque_t *deque){

    node_t *t=deque->front;

    while(t!=NULL)
    {

        if(t->next==NULL)
        {
            printf("%d\n", t->value);
        }

        else if(t->next!=NULL)
        {
            printf("%d ",t->value);
        } 
        t=t->next;
    }
}
