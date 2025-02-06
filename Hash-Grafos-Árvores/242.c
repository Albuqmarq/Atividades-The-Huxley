#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node{
    int value;
    struct node *prox;
} node;

typedef struct hash_table{
    int tam;
    node **buckets;
} hash_table;

void print_hash_table(hash_table *ht){
    for (int i = 0; i < ht->tam; i++){

        printf("%d", i);

        node *current=ht->buckets[i];

        while (current!=NULL){
            printf(" -> %d",current->value);

            current=current->prox;
        }

        printf(" -> \\\n");
    }

    printf("\n");
}

node *maisumnalista(node *ponta, int value){

    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = value;
    new_node->prox = NULL;

	 if(ponta!=NULL){
    node *current=ponta;
    while(current->prox != NULL){
        current = current->prox;
	}
    current->prox = new_node;

    return ponta;
	}
    else if (ponta==NULL){
		return new_node;
	}

	
}
hash_table *create_hash_table(int tam){

    hash_table *ht = (hash_table *) malloc(sizeof(hash_table));

    ht->buckets=(node **) malloc(tam * sizeof(node *));

    ht->tam=tam;
	int i;

    for (i=0; i<tam;i++){

        ht->buckets[i]=NULL;
	}

    return ht;
}



void colocanaHT(hash_table *ht, int v){
	int index;

    index = v % ht->tam;

    ht->buckets[index]=maisumnalista(ht->buckets[index], v);
}



void arruma(){

    int a;
	int b;
	int i;

    scanf("%d %d",&a,&b);

    hash_table *ht =create_hash_table(a);

    for (i = 0; i<b; i++){
        int n;
        scanf("%d", &n);

        colocanaHT(ht, n);
    }

    print_hash_table(ht);
}

int main(){
    int a;

    scanf("%d", &a);

    while(a--){
        arruma();
	}

    return 0;
}
