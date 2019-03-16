/**=========================================================================================================================

ARQUIVO: selecao.c
T�TULO: Ordena��o por Sele��o
CODIFICADO POR: Gabriel Estevam de Oliveira(15104138), Raul Mendes Ros�(15102828), Igor Zanelatto Favro(15102818)
    O c�digo utiliza vers�es modificadas de algor�tmos vistos em sala de aula, como Ordena��o por Sele��o e Inser��o
    e Remo��o de listas encadeadas.
PARA A DISCIPLINA DE: Estrutura de Dados I
CURSO: Engenharia da Computa��o
DATA: Vers�o final codificada em 10/06/2016

OBJETIVO:
    Este programa tem como objetivo medir a quantidade de tempo e mem�ria gastos para ordenar em ordem crescente
    uma lista encadeada sem cabe�a, utilizando o m�todo de ordena��o por sele��o. Para tal, s�o realizadas 50
    itera��es, cada uma criando uma lista �nica e ordenando-a. Ent�o, � feita uma m�dia de tempo e mem�ria gasta e
    essa m�dia � apresentada na tela.

M�TODO GERAL:
    A lista de tarefas gerais �:
    1. Criar uma lista encadeada sem cabe�a de N elementos (definida pelo usu�rio atrav�s deste c�digo);
    2. Ordenar a lista utilizando o algor�tmo de Ordena��o por Sele��o, contando a quantidade de tempo e mem�ria
    gastas para tal;
    3. Repetir os passos 1 e 2 por I itera��es (recomenda-se 50, mas o usu�rio pode alterar a quantidade desejada
    no c�digo) e apresentar a quantidade de mem�ria e a m�dia de tempo gastos em uma itera��o.

ARQUIVOS INCLU�DOS:
    stdio.h
    stdlib.h
    time.h
    locale.h

=========================================================================================================================**/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define I 50 /* Define a quantidade de itera��es realizadas pelo algor�tmo */
#define N 100 /* Define o tamanho de elementos presentes na lista encadeada */

/*=================
REGISTROS
=================*/

/* Declara��o da lista encadeada */
struct cel {
    int conteudo;
    struct cel * seg;
};

typedef struct cel celula;

/*====================
CABE�ALHO DE FUN��ES
====================*/

celula * criaLista (int n);
celula * RemoverTodas(celula * lst);
void imprimeLista(celula * lst);
void selecao(celula *lst);
void Remover(celula * lst);

/*====================
VARI�VEIS GLOBAIS
====================*/

double memoria = 0; /* Essa vari�vel vai quantificar a quantidade de mem�ria gasta por itera��o para a ordena��o */

/*====================================
IN�CIO
====================================*/

int main(){
    int i;
    celula * lst;
    clock_t start, end;
    double cpu_time_used;
    double media = 0;

    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    for (i = 0; i < I; i++) {
        lst = criaLista(N); /*Criando uma nova lista encadeada */

        start = clock(); /*Aqui ele ordena a lista e conta o tempo gasto */
        selecao(lst);
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;/* Calcula o tempo */
        media += cpu_time_used;

        lst = RemoverTodas(lst); /* Depois limpa a mem�ria usada com a lista atual, deixando lst
                                    pronta para receber uma nova lista aleat�ria */
    }

    printf("Tempo m�dio para lista de tamanho %d: %.7fs\n", N, (media/I));
    printf("Mem�ria m�dia gasta com aloca��o de uma lista e sua ordena��o: %.2f bytes\n", memoria/I);

    return 0;
}

void selecao(celula *lst) {
    /*========================================================================================
        Esse algor�tmo tem como objetivo ordenar em ordem crescente uma lista encadeada
        sem cabe�a. Para tal, ele percorre a lista, e para cada c�lula, a fun��o procura
        o elemento que deveria estar naquela posi��o, que � o m�nimo dos que est�o ap�s
        a c�lula
    ========================================================================================*/
    int x;
    celula * i, * j, * min;

    memoria += sizeof(x) + sizeof(celula*)*4;

    i = lst;
    while (i != NULL) {
        min = i; /* Define um valor m�nimo arbitr�rio, usado para compara��o. Ele � o da pr�pria c�lula */
        j = i->seg;
        while (j != NULL) { /* Aqui ele procura por um valor menor do que o guardado por min, e se achar,
                               coloca aquele valor em min */
            if (j->conteudo < min->conteudo)
                min = j;
            j = j->seg;
        }
        /* Aqui ele coloca o valor m�nimo na posi��o atual de i */
        x = i->conteudo;
        i->conteudo = min->conteudo;
        min->conteudo = x;

        i = i->seg;
    }
}

celula * criaLista (int n){
    /* =============================================================================================
        Essa fun��o cria uma lista encadeada de n c�lulas com valores aleat�rios, e
        devolve o endere�o da primeira c�lula da lista
    ==============================================================================================*/

    int i;
    celula * lst = NULL, * c;

    memoria += sizeof(int)*2 + sizeof(celula*)*2;

    for (i = 0; i < n; i++) {
        c = (celula*)malloc(sizeof(celula));
        memoria += sizeof(celula);
        c->conteudo = rand()%10000;
        c->seg = lst;
        lst = c;
    }

    return lst;
}

void imprimeLista(celula * lst) {
    /*====================================================================================================
        Essa fun��o imprime todos os conteudos das c�lulas de uma determinada lista encadeada
    ====================================================================================================*/

    while (lst != NULL) {
        printf("| %d ",lst->conteudo);
        lst = lst->seg;
    }
    printf("|\n");
}

void Remover(celula *lst){
    /*=============================================================================
        Essa fun��o remove a c�lula seguinte � c�lula recebida por par�metro
    =============================================================================*/

    celula * lixo = lst->seg;
    lst->seg = lixo->seg;
    free(lixo);
}

celula *RemoverTodas(celula * lst){
    /*=====================================================================================
        Essa fun��o percorre todos os elementos da lista, chamando a fun��o Remover para
        remover o pr�ximo elemento da atual. Depois, ela remove o elemento remanescente
        e devolve para o ponteiro da lista o valor NULL, indicando que ela est� vazia
    =====================================================================================*/

    while(lst->seg!=NULL){
        Remover(lst);
    }
    free(lst);
    return NULL;
}

