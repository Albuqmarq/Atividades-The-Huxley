#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define TAM 10000



int divide(int *n, int comeco, int final)
{
    int media=(comeco+final)/2;
    int part= n[comeco]+n[final]+n[media];
    int p =(part)/3;
    int i,apoio;
  for(i=comeco;i<final;i++)
  {
        while(n[comeco]>p && comeco<final)
        {
            comeco=comeco+1;
        }
        while(n[final]<=p && comeco<final )
        {
            final=final-1;
        }
        apoio=n[comeco];
        n[comeco]=n[final];
        n[final]=apoio;
    
  }
    return comeco;
}

void qs(int *n, int comeco, int final)
{

    if(comeco<final || comeco+1<=final)
    {

      qs(n, comeco, divide(n, comeco, final) - 1);

      qs(n, divide(n, comeco, final), final);
    }
}

int main()
{
    int casos, alunos,o[TAM], seq[TAM],Pi;
    int i,j,f;
   
    scanf("%d", &casos);

    for(i=1; i<casos+1; i++)
    {
        scanf("%d",&alunos);
        for(j=0; j<alunos; j++)
        {
            scanf("%d", &Pi);

            o[j]=Pi;

            seq[j]=o[j];

        }
        qs(o, 0, alunos-1);

        int p=0;
        for(f=0; f<alunos;f++)
        {
            if(o[f] ==seq[f])
            {
                p=p+1;
            }
        }
        printf("%d\n",p);

    }

    return 0;
}
