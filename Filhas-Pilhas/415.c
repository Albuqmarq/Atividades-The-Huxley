#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


#define TAM 255
struct plh{
    int p;
    char letter[TAM];
};


char pop(struct plh *tower){
    if(tower->p==-1){
        return 'A';
    }
    else if(tower->p!=-1)
    {
        char momentoatual;
        momentoatual=tower->letter[tower->p];
        tower->p--;
        return momentoatual;
    }
    
}


void add(char plvr[TAM],struct plh *tower,int tam)
{
    int PE=0,PD=0,CE=0,CD=0;
   
    if(plvr[0]==' '){
        printf("Yes\n"); return;
    }
    int i;
    for(i=0;i<tam;i++)
    {

        char momentoatual;

       momentoatual=pop(tower);

       if(momentoatual=='(')
       {
            PE=PE+1;
       }
       else if(momentoatual==')')
       {
            PD=PD+1;
       }
       else if(momentoatual=='[')
       {

            CE=CE+1;           
       }
       else if(momentoatual==']')
       {

            CD=CD+1;
       }
       
       if(PD<PE){
            printf("No\n");

        return;
       }
       else if(CD<CE){
        printf("No\n"); 
            return;
       }     
    }
    if(CE==CD && PE==PD){
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }   
    return;
}
void finaliza(struct plh *tower){
    tower->p=-1; return;
}
void empurra(char plvr[TAM],struct plh *tower,int tam){
    int j;
    for(j=0;j<tam;j++)
    {
        tower->p++;
        tower->letter[tower->p]=plvr[j];
    }  
    return; 
}


int main()
{
    struct plh tower;

    tower.p=-1;

    char plvr[TAM];

    int totalplvr=0,t=0;
    
  
    scanf("%d",&totalplvr);

    totalplvr=totalplvr+1;

    int i;
    for(i=0;i<totalplvr;i++)
    {
        if(t==0){
        gets(plvr);
        t++;
        }
        else if(t!=0){
            gets(plvr);
            if(strlen(plvr)==0){
                printf("Yes\n");
            }
            else if(strcmp(plvr,"0")==0){
                printf("Yes\n");
            }
            else{
                empurra(plvr,&tower,strlen(plvr));

                add(plvr,&tower,strlen(plvr));

                finaliza(&tower);
            }
        }
        
    }
    return 0;
}
