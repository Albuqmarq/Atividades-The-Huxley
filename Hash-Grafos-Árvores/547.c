#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int mundial=0;
int m2=0;


struct tree{
    struct tree* left;

    struct tree* right;

    int v;
};

int printar(struct tree* tr,int n,int add){

    struct tree *provisorio=(struct tree*)malloc(sizeof(struct tree));

    provisorio=tr;

    if (provisorio->left!=NULL){
        if(tr->v==n){
            printf("ESTA NA ARVORE\n%d\n",add+1);
            mundial=mundial+1;
            return;
        }
        else if (tr->v!=n) printar(provisorio->left,n,add+1);
        
    } 
    if (provisorio->right!=NULL){
        if(tr->v!=n) printar(provisorio->right,n,add+1);
        
        else if(tr->v==n){
            printf("ESTA NA ARVORE\n%d\n",add+1);
            mundial=mundial+1;
            return;
        }
        
    }
    add=add-1;
    return add;
}

void nar(struct tree* arvore,char *p){
   
    struct tree *novo=(struct tree *) malloc(sizeof(struct tree));

    struct tree *provisorio=(struct tree *) malloc(sizeof(struct tree));

    provisorio->left=NULL;

    provisorio -> right = NULL;

    provisorio -> v = - 1;

    novo->left = NULL;
    novo->right = NULL;
    novo->v=-1;

    if(p[m2]=='(')
    {
        if(p[m2+1]!=')'){
            if (arvore ->v == -1){
                m2=m2+1;
                int soma;
                soma=0;
                while(p[m2] != '(' && p[m2] != ')'){

                    if(p[m2] >= '0' && p[m2] <= '9')
                    {  
                        soma = soma * 10 + (p[m2] - '0');   
                    }
                    m2++;
                }

                arvore->v=soma;
                arvore->left=novo;

                nar(novo,p);

                if(novo->v==-1){
                    arvore->left==NULL;
                }

                arvore->right=provisorio;

                nar(provisorio,p);

                if(provisorio->v==-1){
                    arvore->right==NULL;
                }

                if(p[m2]==')'){
                m2=m2+1;
                }
                return;   
            }
            else if(arvore->v!=-1){ 
                arvore->right=novo;
                nar(novo,p);
                nar(arvore,p);
                return;
            }

        }
        else if(p[m2+1]==')')
        {
            m2= m2 + 2 ;

            return;
        }

    }
    else if (p[m2]!='(') return;
    if(p[m2]==' ' || p[m2]=='\0'){
        m2=m2+1;
    }
    return;
}



int main(){
    int m,m2,cont;
    m2=0;

    char word[1000];
    struct tree *raiz=(struct tree*)malloc(sizeof(struct tree));

    raiz->right = NULL;

    raiz->left=NULL;

    raiz->v=-1;

    

    scanf(" ");

    fgets(word,1000,stdin);

    nar(raiz,word);

    scanf("%d",&m);

    
    cont=-1;

    cont=printar(raiz,m,cont);

    if(mundial==0) printf("NAO ESTA NA ARVORE\n-1\n");
    

    free(raiz);
    return 0;
}
