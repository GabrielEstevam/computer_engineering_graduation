/**=====================================================================================================================

ARQUIVO: quicksort.c
T�TULO: Quicksort em Lista
CODIFICADO POR: Gabriel Estevam de Oliveira(15104138), Raul Mendes Ros�(15102828), Igor Zanelatto Favro(15102818)
    O c�digo utiliza vers�es modificadas de algor�tmos vistos em sala de aula, como Quicksort e Inser��o e Remo��o de
    listas duplamente encadeadas.
PARA A DISCIPLINA DE: Estrutura de Dados I
CURSO: Engenharia da Computa��o
DATA: Vers�o final codificada em 11/06/2016

OBJETIVO:
    Este programa tem como seu objetivo medir a quantidade de tempo e mem�ria gastos para ordenar em ordem crescente
    uma lista duplamente encadeada sem cabe�a, utilizando o m�todo do quicksort. Para tal, s�o realizadas 50
    itera��es, cada uma criando uma lista �nica e ordenando-a. Ent�o, � feita uma m�dia de tempo e mem�ria gasta e
    essa m�dia � apresentada na tela.

M�TODO GERAL:
    A lista de tarefas gerais �:
    1. Criar uma lista duplamente encadeada sem cabe�a de N elementos (definida pelo usu�rio atrav�s deste c�digo);
    2. Ordenar a lista utilizando o algor�tmo Quicksort, contando a quantidade de tempo e mem�ria gastas para tal;
    3. Repetir os passos 1 e 2 por I itera��es (recomenda-se 50, mas o usu�rio pode alterar a quantidade desejada
    no c�digo) e apresentar a quantidade de mem�ria e a m�dia de tempo gastos em uma itera��o.

ARQUIVOS INCLU�DOS:
    stdio.h
    stdlib.h
    time.h
    locale.h

=====================================================================================================================**/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define I 50 /* Define a quantidade de itera��es realizadas pelo algor�tmo */
#define N 100 /* Define o tamanho de elementos presentes na lista encadeada */

/*=================
REGISTROS
=================*/

/* Declara��o da lista duplamente encadeada */
struct cel {
    int conteudo;
    struct cel * seg;
    struct cel * ant;
};

typedef struct cel celula;

/*====================
CABE�ALHO DE FUN��ES
====================*/

celula * criaLista (int n);
celula * Separa (celula * p, celula * r);
celula * inserirCelula(celula * lst, int x);
celula * RemoverTodas(celula * lst);
void Quicksort (celula * p, celula * r);
void imprimeLista(celula * lst);
void Remover(celula * lst);

/*====================
VARI�VEIS GLOBAIS
====================*/

double memoria = 0; /* Essa vari�vel vai quantificar a de mem�ria gasta por itera��o para a ordena��o */

/*====================================
IN�CIO
====================================*/

int main() {
    int i;
    celula * lst;
    clock_t start, end;
    double cpu_time_used;
    double media = 0;

    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    for (i = 0; i < I; i++) {
        lst = criaLista(N);/* Aqui ele cria uma nova lista */

        start = clock();/* Realiza a ordena��o */
        Quicksort(lst, lst->ant);
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;/* Calcula o tempo */
        media += cpu_time_used;

        lst = RemoverTodas(lst);/* Depois limpa a mem�ria usada com a lista atual, deixando lst
                                    pronta para receber uma nova lista aleat�ria */

    }

    printf("Tempo m�dio para lista de tamanho %d: %.7fs\n", N, (media/I));
    printf("Mem�ria m�dia gasta com aloca��o de uma lista e sua ordena��o: %.2f bytes\n", memoria/I);


    return 0;
}

celula * Separa (celula *p, celula *r){
    /*===================================================================================================
        Essa fun��o escolhe uma c�lula com um elemento, chamado piv�. Neste algor�tmo, ela � a �ltima
        c�lula ( r ). Ent�o, a fun��o coloca todos os valores menores que o piv� � esquerda, deixa
        todos os maiores a direita, e ent�o coloca o piv� entre eles, de modo que a esquerda todos os
        valores sejam menores que o piv�, e a direita todos maiores. Ent�o, ela retorna o endere�o da
        c�lula contendo o elemento piv�.
    ===================================================================================================*/
    int c, t;
    celula *j, *k;

    memoria += sizeof(celula*)*4 + sizeof(int)*2;

    c = r->conteudo; /* Salva o valor do elemento piv� */
    j = p; /* j vai guardar a �ltima c�lula com valor inferior ao do piv� */
    for (k = p; k != r; k=k->seg) {
        if (k->conteudo <= c) { /* Se o valor de k for inferior ao do piv�, ele � trocado com o valor
                                   de j */
            t = j->conteudo;
            j->conteudo = k->conteudo;
            k->conteudo = t;
            j = j->seg;
        }
    }
    /* Depois o elemento piv� � colocado entre seus menores e maiores */
    r->conteudo = j->conteudo;
    j->conteudo = c;
    return j;
}

void Quicksort (celula * p, celula * r) {
    /*=================================================================================================================
        Esse algor�tmo recursivo ordena uma lista duplamente encadeada. Para tal, ele seleciona um elemento
        arbitrariamente, e usando a fun��o Separa, o coloca no local em que deveria estar se a lista estivesse
        ordenada. Ent�o, ele realiza o mesmo procedimento para uma semilista que v� do come�o da lista original
        at� esse elemento previamente escolhido, e depois para uma semilista que v� do elemento escolhido at�
        o final da lista original.
    ================================================================================================================*/
    celula * j;
    if (p != r) {
        j = Separa(p, r);
        if (j != p)
            Quicksort(p, j->ant);
        if (j != r)
            Quicksort(j->seg, r);
    }
}

celula * criaLista (int n){
    /* =============================================================================================
        Essa fun��o cria uma lista duplamente encadeada de n c�lulas com valores aleat�rios, e
        devolve o endere�o da primeira c�lula da lista
    ==============================================================================================*/
    int i, x;
    celula * lst = NULL;

    memoria += sizeof(int)*3 + sizeof(lst);

    for (i = n; i > 0; i--) {
        x = rand()%10000;
        lst = inserirCelula(lst, x);
    }

    return lst;
}

void imprimeLista(celula * lst) {
    /*====================================================================================================
        Essa fun��o imprime todos os conteudos das c�lulas de uma determinada lista encadeada
    ====================================================================================================*/

    celula * p = lst;

    do {
        printf("| %d ",lst->conteudo);
        lst = lst->seg;
    } while (lst != p);

    printf("|\n");
}

celula * inserirCelula(celula * lst, int x) {
    /*========================================================================================================
        Essa fun��o cria uma nova c�lula de uma lista duplamente encadeada, e retorna o seu endere�o
    ========================================================================================================*/
    celula * nova;
    nova = (celula*)malloc(sizeof(celula));
    nova->conteudo =  x;

    memoria += sizeof(celula*)*2 + sizeof(int);

    if (lst == NULL) {
        nova->seg = nova;
        nova->ant = nova;
        return nova;
    } else {
        nova->ant = lst->ant;
        nova->ant->seg = nova;
        lst->ant = nova;
        nova->seg = lst;
        return nova;
    }
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

    while(lst->seg!=lst){
        Remover(lst);
    }
    free(lst);
    return NULL;
}
