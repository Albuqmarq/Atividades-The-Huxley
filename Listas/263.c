#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void comp_arrays(int list1[],int list2[],int lista_final[])
{
    int loc;
    loc=0;
    for(int i=0;i<=19;i++)
    {
        lista_final[i]=-1;
        }
    for(int i=0;i<=19;i++)
    {
        for(int j=0;j<=19;j++)
        {
            if(list1[i]==list2[j])
            {
                
                lista_final[loc]=list2[j];
                
                if(lista_final[loc]==lista_final[loc-1])
                {
                
                lista_final[loc]=-1;
                
                }
                else{
                    loc=loc+1;
                }
            }
        }
    }
    if(lista_final[0]==-1)
    {
            printf("VAZIO\n");
        }
    else if(lista_final[0]!=-1)
    {
        for(int i=0;i<=19;i++)
        {
            if(lista_final[i]==-1)
            {
            i=20;
            }
            else if(lista_final[i]!=-1)
            {
                printf("%d\n",lista_final[i]);
            }
        }
    }
}
int main()
{
    int l1[20],l2[20],array[20],aux;
    aux=0;
    for(int i=0;i<=19;i++)
    {
        scanf("%d",&l1[i]);
    }
    for(int i=0;i<=19;i++)
    {
        for(int j=0;j<19-i;j++)
        { 
            if(l1[j]>l1[j+1]){
                aux = l1[j];
                l1[j] = l1[j+1];
                l1[j+1] = aux;
            }
        }
    }
    aux=0;

    for(int i=0; i<=19; i++)
    {
        scanf("%d",&l2[i]);
    }
    for(int i=0; i<=19; i++)
    {
        for(int j=0; j<19-i; j++)
        { 
            if(l2[j]>l2[j+1])
            {
                aux = l2[j];
                l2[j] = l2[j+1];
                l2[j+1] = aux;
            }
        }
    }
    comp_arrays(l1,l2,array);

    return 0;
}
