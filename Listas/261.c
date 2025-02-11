#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct l1{
    int valor;
    struct l1 *next;
};

struct l2{
    int valor;
    struct l2 *next;
};

int nulo(struct l1 *LISTA){
    if(LISTA->next == NULL){
        return 1;
    }
        
    else{
        return 0;
    }
}
void adicional1(struct l1 *LISTA,int a)
{
    struct l1 *new=(struct l1 *) malloc(sizeof(struct l1));
    new->valor=a;
    if(nulo(LISTA))
    {
        LISTA->next=new;
    }
    else
    {
        struct l1 *temp=LISTA->next;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=new;
    }
}
int nulo2(struct l2 *LISTA)
{
    if(LISTA->next == NULL)
    {
        return 1;
    }
        
    else if(LISTA->next != NULL)
    {
        return 0;
    }
}

void adicional2(struct l2 *LISTA,int a)
{
    struct l2 *new=(struct l2 *) malloc(sizeof(struct l2));
    new->valor=a;
    if(nulo2(LISTA))
    {
        LISTA->next=new;
    }
    else
    {
        struct l2 *temp=LISTA->next;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=new;
    }
}
int sub(struct l1 *L1, struct l2 *L2, int t1, int t2)
{
    struct l1 *temp;
    for(int i=0;i<t2;i++){
        L2=L2->next;
        temp=L1->next;
        for(int j=0;j<t1;j++)
        {
            if(j==t1-1)
            {
                if(L2->valor==temp->valor)
                {
                    j=t1;
                }
                else if (L2->valor!=temp->valor)
                {
                    return 0;
                }
            }
            else
            {
                if(L2->valor==temp->valor)
                {
                    j=t1;
                }
                else if(L2->valor!=temp->valor)
                {
                    temp=temp->next;  
                }  
            }
        }
    }
    return 1;
}


int main()
{
    int t1,t2,v1,v2;
    struct l1 *p1=(struct l1 *) malloc(sizeof(struct l1));
    struct l2 *p2=(struct l2 *) malloc(sizeof(struct l2));

    scanf("%d",&t1);

    for(int i=0;i<t1;i++)
    {
        scanf(" %d ",&v1);
        adicional1(p1,v1);
    }

    scanf("%d",&t2);

    for(int i=0;i<t2;i++)
    {
        scanf("%d",&v2);
        adicional2( p2 , v2 );
    }

    printf("%d\n",sub(p1,p2,t1,t2));
    free(p1);
    free(p2);
    return 0;
}
