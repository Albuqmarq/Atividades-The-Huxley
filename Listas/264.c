#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct list
{
    int valor;
    struct list *next;
};

void add(struct list *LISTA, int num)
{
    struct list *old=(struct list *) malloc(sizeof(struct list));

    struct list *new=(struct list *) malloc(sizeof(struct list));
        new->valor = num;
        old= LISTA->next;
        new->next = old;
        LISTA->next=new;
}

void printar(struct list *LISTA,int c)
{
    for(int i=0;i<c;i++)
    {
        printf("%d ",(LISTA->next)->valor);
        LISTA=LISTA->next;
    }
}

int main()
{
    struct list *ponteiro=(struct list *) malloc(sizeof(struct list));
    ponteiro->next=NULL;
    int n,c=0;
    while(scanf("%d",&n)!=EOF)
    {
        add(ponteiro,n);
        c++;
    }
    printar(ponteiro,c);

    free(ponteiro);
    
    return 0;
}
