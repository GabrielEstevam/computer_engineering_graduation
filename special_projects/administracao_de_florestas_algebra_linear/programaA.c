/* O programa resolve o problema da ONG contido na apresentacao Cadeias de
 * de Markov.
 * Uma maquina com o sistema operacional linux foi utilizada
 * Para compilar este programa utilize o comando:
 * 	$ gcc -Wall -ansi -pedantic -O3 cm_ong.c -o cm_ong -lm
 *
 * E para executar o programa:
 * 	$ ./cm_ong
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM 6 /* 9 2*/
#define N 50
/****************************************************************************/

int main(){

  int i, j, k, w;

  float total = 0.0;

  float p[DIM-1]={50.0,100.0,150.0,200.0,250.0};

  float RT[DIM-1];

  float x[DIM]={100.0,100.0,100.0,100.0,100.0,100.0};
  float y[DIM]={0.0,0.0,0.0,0.0,0.0,0.0};

  float m[DIM][DIM]={
  {0.72,0.0,0.0,0.0,0.0,0.0},
  {0.28,0.69,0.0,0.0,0.0,0.0},
  {0.0,0.31,0.75,0.0,0.0,0.0},
  {0.0,0.0,0.25,0.77,0.0,0.0},
  {0.0,0.0,0.0,0.23,0.63,0.0},
  {0.0,0.0,0.0,0.0,0.37,1.0},
  };

  for(i=0;i<DIM;i++){
    for(j=0;j<DIM;j++){
        printf(" %.2f ",m[i][j]);
    }
    printf("\n");
  }

  for(w=0;w<100;w++){
    printf("\nIteracao %i",w+1);
    for(k=0;k<DIM;k++){
        for(i=0;i<DIM;i++){
            y[k]+=m[k][i]*x[i];
        }
    }

    for(i=0;i<DIM;i++){
        printf("\nClasse %i: %.1f",i+1,y[i]);
        printf("       Valor: %.2f",y[i]*p[i-1]);
    }

    int maior = 1;

    for(i=2;i<DIM;i++){
        if((y[i]*p[i-1])>(y[maior]*p[maior-1])){
            maior=i;
        }
    }

    total +=y[maior]*p[maior-1];
    printf("\nTotal: %.2f",total);
    y[0]+=y[maior];
    y[maior]=0.0;


    for(k=0;k<DIM;k++){
        x[k]=y[k];
        y[k]=0.0;
    }

    printf("\n");
  }

/*
  //Laço
    RT[0]=p[0]/(1/m[1][0]);
    RT[1]=p[1]/((1/m[1][0])+(1/m[2][1]));
    RT[2]=p[2]/((1/m[1][0])+(1/m[2][1])+(1/m[3][2]));
    RT[3]=p[3]/((1/m[1][0])+(1/m[2][1])+(1/m[3][2])+(1/m[4][3]));
    RT[4]=p[4]/((1/m[1][0])+(1/m[2][1])+(1/m[3][2])+(1/m[4][3])+(1/m[5][4]));

  for(i=0;i<DIM-1;i++){
    printf("\nRT%i = %.1f",i+2,RT[i]);
    printf("s");
  }
*/
  return(0);
}
