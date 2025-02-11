#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct list
{
    int n;
    struct list *next;
};
void ordem(struct list *LISTA,int c)
{
    int aux;
    struct list *comeco=(struct list *) malloc(sizeof(struct list));
    
    for(c;c>=1;c--)
    {
        comeco=LISTA->next;
        for(int j=0;j<c-1;j++)
        {
            if(comeco->n>(comeco->next)->n)
            {
                aux= comeco->n;
                comeco->n = (comeco->next)->n;
                (comeco->next)->n = aux;
                comeco=comeco->next;
            }
            else{
                comeco=comeco->next;
            }
        }
    }
}

int nulo(struct list *LISTA)
{
    if(LISTA->next)
    {
        return 1;
    }
        
    else
    {
        return 0;
    }
}

void add(struct list *LISTA,int a)
{
    struct list *new= (struct list *) malloc(sizeof(struct list));
    new->n=a;
    if(nulo(LISTA)==NULL)
    {
        LISTA->next=new;
    }
    else
    {
        struct list *provisorio=LISTA->next;
        while(provisorio->next!=NULL){
            provisorio=provisorio->next;
        }
        provisorio->next=new;
    }
}

int main()
{
    int a, ord=0;
    struct list *aponta = (struct list *) malloc(sizeof(struct list));
    aponta->next=NULL;
    while(scanf("%d",&a)!=EOF)
    {
        add(aponta,a);

        ord=ord+1;
    }
    ordem(aponta,ord);
    while(ord!=0)
    {
        printf("%d ",(aponta->next)->n);
        aponta=aponta->next;
        ord = ord-1;  
    }
    

    free(aponta);

    return 0;       
    }
