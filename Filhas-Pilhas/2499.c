#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define TAM 100
struct p{
    int posicao;
    int array[TAM];
};

void imprimir(struct p *Pl)
{
    int i;
    for(i=Pl->posicao;i>-1;i--){
        if(i==0){
            printf("%d",Pl->array[i]);
        }
        else if (i !=0 ){
            printf("%d ",Pl->array[i]);
        }
    }
    printf("\n");
}

void pop(struct p *Pl)
{
    if(Pl->posicao==-1)
    {
        printf("underflow");
        return;
    }
    Pl->posicao--;
}

void push(struct p *Pl,int value)
{
    if(Pl->posicao>TAM)
    {
        printf("overflow");
        return;
    }
    Pl->posicao++;

    Pl->array[Pl->posicao]=value;
}



int main()
{
    struct p tower;
    tower.posicao=-1;
    struct p *pntr=&tower;
    char word[256];
    int value;
    value=0;
    scanf("%s",word);

    while(word[0]!='F')
    {

        if(word[0]=='E')
        {
            scanf("%d",&value);
            push(pntr,value);
            scanf("%s",word);
        }

        else if(word[0]=='D')
        {
            pop(pntr);
            scanf("%s",word);
        }

        else if (word[0]=='I')
        {
            imprimir(pntr);
            scanf("%s",word);
        }
    }
    return 0;
}
