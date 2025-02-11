#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct list
{
    char d;
    int num;
    struct list *next;
};
void printar(struct list *LISTA)
{
    while(LISTA->next!=NULL){
        printf("%c %d\n",(LISTA->next)->d,(LISTA->next)->num);
        LISTA=LISTA->next;
    }
}

void obter(struct list *LISTA,char l,int rep)
{
    struct list *old=(struct list *) malloc(sizeof(struct list));
    struct list *new=(struct list *) malloc(sizeof(struct list));
    new->d=l;
    new->num=rep;
    old=LISTA->next;
    new->next=old;
    LISTA->next=new;

}



int main()
{
    int tam,rep,i,j;
    char L[] = {' ', '!' ,'"' ,'#' ,'$' ,'%' ,'&' ,'\'', '(', ')' ,'*' ,'+' ,',' ,'-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                 ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 
                 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 
                 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; 
    char word[256];
    struct list *aponta= (struct list *) malloc(sizeof(struct list));
    aponta->next=NULL;
    scanf ( "%256[^\n]",word);
    tam=strlen(word);

    for(i=0;i<=90;i++)
    {
         rep=0;
        for(j=0;j<tam;j++)
        {
            if(L[i]==word[j])
            {
                rep=rep+1;
            }
        }
        if(rep>=1)
        {
            obter(aponta,L[i],rep);
        }
    }
    printar(aponta);
    free(aponta);
    return 0;
}
