#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define TAM 100
struct p{
    int loc;
    int array[TAM];
};


void pop(struct p *PILHA)
{
    if(PILHA->loc==-1){
        printf("underflow");
        return;
    }
    PILHA->loc--;
    int i;
    for(i=PILHA->loc;i>-1;i--)
    {
        if(i==0)
        {
            printf("%d",PILHA->array[i]);
        }
        else if(i!=0){
            printf("%d ",PILHA->array[i]);
        }
    }
    printf("\n");
}

void push(struct p *PILHA,int value)
{
    if(PILHA->loc>TAM)
    {
        printf("overflow");
        return;
    }
    PILHA->loc++;
    PILHA->array[PILHA->loc]=value;
    int i;
    for(i=PILHA->loc;i>-1;i--)
    {
        if(i==0)
        {
            printf("%d",PILHA->array[i]);
        }
        else if (i!=0)
        {
            printf("%d ",PILHA->array[i]);
        }
    }
    printf("\n");
}


int main()
{
    struct p tower;
    tower.loc=-1;
    struct p *pont=&tower;
    char word[256];
    int value;
    value=0;
    scanf("%s",word);
    while(word[0]!='F')
    {

        if(word[0]=='E')
        {
            scanf("%d",&value);
            push(pont,value);
            scanf("%s",word);
        }

        else if(word[0]=='D')
        {
            pop(pont);
            scanf("%s",word);
        }
    }
    return 0;
}
