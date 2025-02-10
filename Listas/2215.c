#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct l1
{
    int v;
    struct l1 *next;
};
struct l2
{
    int v;
    struct l2 *next;
};
struct l3
{
    int v;
    struct l3 *next;
};


int transf_num(char num)
{
    if(num=='0')
    {
        return 0;
    }
    else if(num=='1')
    {
        return 1;
    }
    else if(num=='2')
    {
        return 2;
    }
    else if(num=='3')
    {
        return 3;
    }
    else if(num=='4')
    {
        return 4;
    }
    else if(num=='5')
    {
        return 5;
    }
    else if(num=='6')
    {
        return 6;
    }
    else if(num=='7')
    {
        return 7;
    }
    else if(num=='8')
    {
        return 8;
    }
    else if(num=='9')
    {
        return 9;
    }
}


int nulo(struct l1 *LISTA)
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
void add1(struct l1 *LISTA,char l)
{
    int num=transf_num(l);
    struct l1 *novo=(struct l1 *) malloc(sizeof(struct l1));
    novo->v=num;
    if(nulo(LISTA))
    {
        LISTA->next=novo;
    }
    else
    {
        struct l1 *aux=LISTA->next;
        while(aux->next!=NULL)
        {
            aux=aux->next;
        }
        aux->next=novo;
    }
}

int nulo2(struct l2 *LISTA)
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

void add2(struct l2 *LISTA,char l){
    int num=transf_num(l);
    struct l2 *novo=(struct l2 *) malloc(sizeof(struct l2));
    novo->v=num;
    if(nulo2(LISTA)!=NULL)
    {
        LISTA->next=novo;
    }
    else
    {
        struct l2 *aux=LISTA->next;
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next=novo;
    }
}
void addinic(struct l3 *LISTA,int v)
{
    struct l3 *novo=(struct l3 *) malloc(sizeof(struct l3));
    struct l3 *old;
    novo->v=v;
    old=LISTA->next;
    LISTA->next=novo;
    novo->next=old;
}
void adicao(struct l1 *LISTA1,struct l2 *LISTA2,struct l3 *LISTA3)
{
    int resto=0;
    if(nulo(LISTA1)&&nulo2(LISTA2))
    {
        printf("Lista vazia!");
        return;
    }

    else if
    (nulo(LISTA1)!=NULL){
        while(LISTA2->next!=NULL){
        printf("%d ",(LISTA2->next)->v);
        LISTA2=LISTA2->next;
        }
        return;
    }

    else if
    (nulo2(LISTA2)!=NULL){
        while(LISTA1->next!=NULL){
        printf("%d ",(LISTA1->next)->v);
        LISTA1=LISTA1->next;
        }
        return;
    }

    else
    {
        int pausa=0,pausa2=0;
      
        struct l1 *aux1=LISTA1->next;
        struct l2 *aux2=LISTA2->next;
        aux1=LISTA1;
        aux2=LISTA2;
        while((aux1->next)!=NULL)
        {
            aux1=aux1->next;
            pausa++;
        }
        while((aux2->next)!=NULL)
        {
            aux2=aux2->next;
            pausa2++;
        }

        while(pausa!=0 || pausa2!=0 || resto!=0)
        {
            int gira1=pausa,gira2=pausa2;
          
            aux1=LISTA1;
            aux2=LISTA2;

            while(gira1!=0)
            {
            aux1=aux1->next;
            gira1--;
            }

            while(gira2!=0)
            {
            aux2=aux2->next;
            gira2--;
            }
            
            int soma;
            soma=(aux1->v+aux2->v);
            if(soma+resto>9){
                addinic(LISTA3,(soma+resto)%10);
                resto=(soma+resto)/10;
            }
            else if(soma+resto<=9)
            {
                addinic(LISTA3,soma+resto);
                resto=0;
            }
            if(pausa!=0)
            {
                pausa--;
            }
            if(pausa2!=0)
            {
                pausa2--;
            }           
        }
        while((LISTA3->next)->v==0)
        {
            LISTA3=LISTA3->next;
        }
        while(LISTA3->next!=NULL)
        {
            printf("%d ",(LISTA3->next)->v);
            LISTA3=LISTA3->next;
        } 
    }
}
int main()
{
    struct l1 *p1 = (struct l1 *) malloc(sizeof(struct l1));
    struct l2 *p2 = (struct l2 *) malloc(sizeof(struct l2));
    struct l3 *pf = (struct l3 *) malloc(sizeof(struct l3));
    char L1,L2; 
    
    scanf("%c",&L1);

    while(L1!='+')
    {
        add1(p1,L1);          
        scanf(" %c",&L1);
    }
    scanf(" %c",&L2);
    while(L2!='=')
    {
        add2(p2,L2);
        scanf(" %c",&L2);
    }
    adicao(p1,p2,pf);
    free(p1);
    free(p2);
    free(pf);
    return 0;
}
