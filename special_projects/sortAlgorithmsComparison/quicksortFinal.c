/**=====================================================================================================================

ARQUIVO: quicksort.c
TÍTULO: Quicksort em Lista
CODIFICADO POR: Gabriel Estevam de Oliveira(15104138), Raul Mendes Rosá(15102828), Igor Zanelatto Favro(15102818)
    O código utiliza versões modificadas de algorítmos vistos em sala de aula, como Quicksort e Inserção e Remoção de
    listas duplamente encadeadas.
PARA A DISCIPLINA DE: Estrutura de Dados I
CURSO: Engenharia da Computação
DATA: Versão final codificada em 11/06/2016

OBJETIVO:
    Este programa tem como seu objetivo medir a quantidade de tempo e memória gastos para ordenar em ordem crescente
    uma lista duplamente encadeada sem cabeça, utilizando o método do quicksort. Para tal, são realizadas 50
    iterações, cada uma criando uma lista única e ordenando-a. Então, é feita uma média de tempo e memória gasta e
    essa média é apresentada na tela.

MÉTODO GERAL:
    A lista de tarefas gerais é:
    1. Criar uma lista duplamente encadeada sem cabeça de N elementos (definida pelo usuário através deste código);
    2. Ordenar a lista utilizando o algorítmo Quicksort, contando a quantidade de tempo e memória gastas para tal;
    3. Repetir os passos 1 e 2 por I iterações (recomenda-se 50, mas o usuário pode alterar a quantidade desejada
    no código) e apresentar a quantidade de memória e a média de tempo gastos em uma iteração.

ARQUIVOS INCLUÍDOS:
    stdio.h
    stdlib.h
    time.h
    locale.h

=====================================================================================================================**/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define I 50 /* Define a quantidade de iterações realizadas pelo algorítmo */
#define N 100 /* Define o tamanho de elementos presentes na lista encadeada */

/*=================
REGISTROS
=================*/

/* Declaração da lista duplamente encadeada */
struct cel {
    int conteudo;
    struct cel * seg;
    struct cel * ant;
};

typedef struct cel celula;

/*====================
CABEÇALHO DE FUNÇÕES
====================*/

celula * criaLista (int n);
celula * Separa (celula * p, celula * r);
celula * inserirCelula(celula * lst, int x);
celula * RemoverTodas(celula * lst);
void Quicksort (celula * p, celula * r);
void imprimeLista(celula * lst);
void Remover(celula * lst);

/*====================
VARIÁVEIS GLOBAIS
====================*/

double memoria = 0; /* Essa variável vai quantificar a de memória gasta por iteração para a ordenação */

/*====================================
INÍCIO
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

        start = clock();/* Realiza a ordenação */
        Quicksort(lst, lst->ant);
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;/* Calcula o tempo */
        media += cpu_time_used;

        lst = RemoverTodas(lst);/* Depois limpa a memória usada com a lista atual, deixando lst
                                    pronta para receber uma nova lista aleatória */

    }

    printf("Tempo médio para lista de tamanho %d: %.7fs\n", N, (media/I));
    printf("Memória média gasta com alocação de uma lista e sua ordenação: %.2f bytes\n", memoria/I);


    return 0;
}

celula * Separa (celula *p, celula *r){
    /*===================================================================================================
        Essa função escolhe uma célula com um elemento, chamado pivô. Neste algorítmo, ela é a última
        célula ( r ). Então, a função coloca todos os valores menores que o pivô à esquerda, deixa
        todos os maiores a direita, e então coloca o pivô entre eles, de modo que a esquerda todos os
        valores sejam menores que o pivô, e a direita todos maiores. Então, ela retorna o endereço da
        célula contendo o elemento pivô.
    ===================================================================================================*/
    int c, t;
    celula *j, *k;

    memoria += sizeof(celula*)*4 + sizeof(int)*2;

    c = r->conteudo; /* Salva o valor do elemento pivô */
    j = p; /* j vai guardar a última célula com valor inferior ao do pivô */
    for (k = p; k != r; k=k->seg) {
        if (k->conteudo <= c) { /* Se o valor de k for inferior ao do pivô, ele é trocado com o valor
                                   de j */
            t = j->conteudo;
            j->conteudo = k->conteudo;
            k->conteudo = t;
            j = j->seg;
        }
    }
    /* Depois o elemento pivô é colocado entre seus menores e maiores */
    r->conteudo = j->conteudo;
    j->conteudo = c;
    return j;
}

void Quicksort (celula * p, celula * r) {
    /*=================================================================================================================
        Esse algorítmo recursivo ordena uma lista duplamente encadeada. Para tal, ele seleciona um elemento
        arbitrariamente, e usando a função Separa, o coloca no local em que deveria estar se a lista estivesse
        ordenada. Então, ele realiza o mesmo procedimento para uma semilista que vá do começo da lista original
        até esse elemento previamente escolhido, e depois para uma semilista que vá do elemento escolhido até
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
        Essa função cria uma lista duplamente encadeada de n células com valores aleatórios, e
        devolve o endereço da primeira célula da lista
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
        Essa função imprime todos os conteudos das células de uma determinada lista encadeada
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
        Essa função cria uma nova célula de uma lista duplamente encadeada, e retorna o seu endereço
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
        Essa função remove a célula seguinte à célula recebida por parâmetro
    =============================================================================*/

    celula * lixo = lst->seg;
    lst->seg = lixo->seg;
    free(lixo);
}

celula *RemoverTodas(celula * lst){
    /*=====================================================================================
        Essa função percorre todos os elementos da lista, chamando a função Remover para
        remover o próximo elemento da atual. Depois, ela remove o elemento remanescente
        e devolve para o ponteiro da lista o valor NULL, indicando que ela está vazia
    =====================================================================================*/

    while(lst->seg!=lst){
        Remover(lst);
    }
    free(lst);
    return NULL;
}
