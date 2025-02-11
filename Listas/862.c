#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct list
{
    char bit;
    struct list *next;
};

int nulo(struct list *LISTA)
{
    if(LISTA->next==NULL)
    {
        return 1;
    }
    else if(LISTA->next!=NULL)
    {
        return 0;
    }
}

void ordem(struct list *LISTA,int tam)
{
    int grp[tam],loc=0,rep=0,cola;
    struct list *t=LISTA->next;
    while(t!=NULL)
    {
        if(t->bit == '1')
        {
            rep=0;
            grp[loc]=rep;
            loc=loc+1;
            t=t->next;
        }
        else if (t->bit != '1')
        {
            rep++;
            grp[loc]=rep;
            loc=loc+1;
            t=t->next;
        }
    }
    cola=0;
    for(int i=0;i<tam;i++)
    {
        if(grp[cola]<grp[i])
        {
            cola=i;
        }
    }
    printf("%d %d",cola+1-grp[cola],cola);
    printf("\n");
}
void entra(struct list *LISTA,char num)
{
    struct list *new=(struct list *) malloc(sizeof(struct list));
    new->bit=num;
    if(nulo(LISTA))
    {
        LISTA->next=new;
    }
    else{
        struct list *t=LISTA->next;
        while(t->next!=NULL)
        {
            t=t->next;
        }
        t->next=new;
    }
}
int main()
{
    char bin[256];
    int tam,fim=1,n;
    
    struct list *p = (struct list *) malloc(sizeof(struct list));
    p->next=NULL;
    while(fim!=0)
    {
        scanf(" %s ",bin);
        tam=strlen(bin);
        if(tam==1){
            break;
        }
        else if(tam!=1)
        {
            for(int i=0;i<tam;i++)
            {
                entra(p,bin[i]);               
            }
            ordem(p,tam);    
        }
           n=tam;
           while(n!=0)
           {
                p=p->next;
                n--;  
           } 
    }
    free(p);
    return 0;
}
