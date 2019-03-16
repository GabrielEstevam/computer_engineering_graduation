/**====================================================================================================================

ARQUIVO: insercao.c
TÍTULO: Ordenação por Inserção
CODIFICADO POR: Gabriel Estevam de Oliveira(15104138), Raul Mendes Rosá(15102828), Igor Zanelatto Favro(15102818)
    O código utiliza versões modificadas de algorítmos vistos em sala de aula, como Ordenação por Inserção e Inserção
    e Remoção de listas encadeadas.
PARA A DISCIPLINA DE: Estrutura de Dados I
CURSO: Engenharia da Computação
DATA: Versão final codificada em 10/06/2016

OBJETIVO:
    Este programa tem como objetivo medir a quantidade de tempo e memória gastos para ordenar em ordem crescente
    uma lista encadeada sem cabeça, utilizando o método de ordenação por seleção. Para tal, são realizadas 50
    iterações, cada uma criando uma lista única e ordenando-a. Então, é feita uma média de tempo e memória gasta e
    essa média é apresentada na tela.

MÉTODO GERAL:
    A lista de tarefas gerais é:
    1. Criar uma lista encadeada sem cabeça de N elementos (definida pelo usuário através deste código);
    2. Ordenar a lista utilizando o algorítmo de Ordenação por Inserção, contando a quantidade de tempo e memória
    gastas para tal;
    3. Repetir os passos 1 e 2 por I iterações (recomenda-se 50, mas o usuário pode alterar a quantidade desejada
    no código) e apresentar a quantidade de memória e a média de tempo gastos em uma iteração.

ARQUIVOS INCLUÍDOS:
    stdio.h
    stdlib.h
    time.h
    locale.h

====================================================================================================================**/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define I 50 /* Define a quantidade de iterações realizadas pelo algorítmo */
#define N 100 /* Define o tamanho de elementos presentes na lista encadeada */

/*=================
REGISTROS
=================*/

/* Declaração da lista encadeada */
struct cel {
    int conteudo;
    struct cel * seg;
};

typedef struct cel celula;

/*====================
CABEÇALHO DE FUNÇÕES
====================*/

celula * criaLista (int n);
celula * RemoverTodas(celula * lst);
void imprimeLista(celula * lst);
void insercao (celula * lst);
void Remover(celula * lst);

/*====================
VARIÁVEIS GLOBAIS
====================*/

double memoria = 0; /* Essa variável vai quantificar a quantidade de memória gasta por iteração para a ordenação */

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
        lst = criaLista(N); /* Aqui ele cria uma nova lista */

        start = clock();/* Realiza a ordenação */
        insercao(lst);
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; /* Calcula o tempo */
        media += cpu_time_used;

        lst = RemoverTodas(lst); /* Depois limpa a memória usada com a lista atual, deixando lst
                                    pronta para receber uma nova lista aleatória */
    }

    printf("Tempo médio para lista de tamanho %d: %.7fs\n", N, (media/I));
    printf("Memória média gasta com alocação de uma lista e sua ordenação: %.2f bytes\n", memoria/I);

    return 0;

}

void insercao (celula * lst) {
    /*======================================================================================
        Esse algorítmo ordena uma lista encadeada sem cabeça em ordem crescente.
        Ele consiste em percorrer a lista, célula por célula, colocando os conteúdos de
        menores valores nas células da frente
    ======================================================================================*/
    celula * s, * t =  lst->seg;
    int x;

    memoria += sizeof(celula)*3 + sizeof(x);

    while (t != NULL) {
        s = lst;
        while (s != t) {
            x = t->conteudo;
            if (x < s->conteudo) {
                t->conteudo = s->conteudo;
                s->conteudo = x;
            }
            s =  s->seg;
        }
        t = t->seg;
    }
}

celula * criaLista (int n){
    /* =============================================================================================
        Essa função cria uma lista encadeada de n células com valores aleatórios, e
        devolve o endereço da primeira célula da lista
    ==============================================================================================*/
    int i;
    celula * lst = NULL, * c;

    memoria += sizeof(int)*2 + sizeof(celula*)*2;

    /** Adicionando as células à lista **/

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
        Essa função imprime todos os conteudos das células de uma determinada lista encadeada
    ====================================================================================================*/

    while (lst != NULL) {
        printf("| %d ",lst->conteudo);
        lst = lst->seg;
    }
    printf("|\n");
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

    while(lst->seg!=NULL){
        Remover(lst);
    }
    free(lst);
    return NULL;
}
