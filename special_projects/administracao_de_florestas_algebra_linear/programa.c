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

#define DIM 3 /* 9 2*/
#define N 50
/****************************************************************************/

int main(){

  int i, j, k;

  double x[DIM], x0[DIM], P[DIM][DIM], soma;

  for(i = 0; i < DIM; i++)
    x0[i]=0.0;
  x0[0] = 1.0; /*x0[1]=1.0;*/
  /*P[0][0] = 0.8;
  P[0][1] = 0.3;
  P[1][0] = 0.2;
  P[1][1] = 0.7;*/

  for(i = 0; i < DIM; i++)
    for(j = 0; j < DIM; j++)
      P[i][j] = 0.0;

  P[0][0] = 1./3.;
  P[0][1] = 1./2.;
  P[1][0] = 2./3.;
  P[1][1] = 1./4.;
  P[1][2] = 4./5.;
  P[2][1] = 1./4.;
  P[2][2] = 1./5.;

  /*P[0][0] = 1./3.;
  P[0][1] = 1./4.;
  P[0][3] = 1./4.;
  P[1][0] = 1./3.;
  P[1][1] = 1./4.;
  P[1][2] = 1./3.;
  P[1][4] = 1./5.;
  P[2][1] = 1./4.;
  P[2][2] = 1./3.;
  P[2][5] = 1./4.;
  P[3][0] = 1./3.;
  P[3][3] = 1./4.;
  P[3][4] = 1./5.;
  P[3][6] = 1./3.;
  P[4][1] = 1./4.;
  P[4][3] = 1./4.;
  P[4][4] = 1./5.;
  P[4][5] = 1./4.;
  P[4][7] = 1./4.;
  P[5][2] = 1./3.;
  P[5][4] = 1./5.;
  P[5][5] = 1./4.;
  P[5][8] = 1./3.;
  P[6][3] = 1./4.;
  P[6][6] = 1./3.;
  P[6][7] = 1./4.;
  P[7][4] = 1./5.;
  P[7][6] = 1./3.;
  P[7][7] = 1./4.;
  P[7][8] = 1./3.;
  P[8][5] = 1./4.;
  P[8][7] = 1./4.;
  P[8][8] = 1./3.;*/


  for(k = 1; k < N; k++){
    printf("iteracao \t %d\n",k);
    for(i = 0; i < DIM; i++){
      x[i] = 0.0;
      for(j = 0; j < DIM; j++)
	x[i] += P[i][j]*x0[j];
      printf("%.10E\n",x[i]);
    }
    for(i = 0; i < DIM; i++)
      x0[i] = x[i];
  }
  soma = 0.0;
  for(i = 0; i < DIM; i++)
    soma += x[i];
  printf("%.10E\n", soma);

  return(0);
}
