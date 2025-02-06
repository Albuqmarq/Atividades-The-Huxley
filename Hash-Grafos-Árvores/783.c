#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


int golbal;
global=0;

struct arvore{
    struct arvore* lf;
    struct arvore* d;
    int val;
};

void printar(struct arvore* arv){
    struct arvore *local=(struct arvore*)malloc(sizeof(struct arvore));


    local=arv;

    printf(" ( %d ",local->val);
    if(local->lf!=NULL){
        printar(local->lf);
        }

    else if(local->lf ==NULL){
        printf(" () ");
        }
   

    
    if(local->d!=NULL){ 
        printar(local->d);}
    else if(local->d==NULL){
        printf(" () ");}

    printf(") ");

    return;
}


void constroi(struct arvore* tree,int moment){

    int num;
    num=0;   
    struct arvore *newst=(struct arvore*)malloc(sizeof(struct arvore));

    struct arvore *l=(struct arvore*)malloc(sizeof(struct arvore));

    newst->lf=NULL;

    newst->d=NULL;

    newst->val=moment;

    l=tree;

    while(1)
    {
          if(moment >= l->val){
            if(l->d == NULL){

                l->d=newst;

                break;
            }
        l=l->d;
        }

        else if(moment < l->val){
            if(l->lf==NULL){

                l->lf=newst;

                break;
            }
        l = l->lf;
        }
      
      
    }
    return;
}

int transnumero(char *w){     

    int mais;
    mais=0;
    while(w[global] != ' ' && w[global] != '\0'){

    if(w[global] >= '0' && w[global] <= '9'){  
        mais = mais * 10 + (w[global] - '0');   

    }

    global=global+1;
    }
    return mais;
}



int main(){

    struct arvore *raiz=(struct arvore*)malloc(sizeof(struct arvore));

    
    raiz->d=NULL;

    raiz->lf=NULL;

    char pala[1000];
    fgets(pala,1000,stdin);

    raiz->val=transnumero(pala);
    printf("----\n");
    printf("Adicionando %d\n",raiz->val);
    printf("  ");
    printar(raiz);
    printf("\n");
    printf("----\n");

    global=global+1;

    
    while(pala[global]!='\0'){
        int v;
        v=transnumero(pala);
        if(v!=0){

            constroi(raiz,v);
            printf("Adicionando %d\n",v);

            printf("  ");

            printar(raiz);

            printf("\n");

            printf("----\n");
            global=global+1;
        }
    }
    free(raiz);
    return 0;
}
