/**=====================================================================================================================

ARQUIVO: mergesort.c
TÍTULO: Mergesort em Lista
CODIFICADO POR: Gabriel Estevam de Oliveira(15104138), Raul Mendes Rosá(15102828), Igor Zanelatto Favro(15102818)
    O código utiliza versões modificadas de algorítmos vistos em sala de aula, como Mergesort e Inserção e Remoção de
    listas duplamente encadeadas.
PARA A DISCIPLINA DE: Estrutura de Dados I
CURSO: Engenharia da Computação
DATA: Versão final codificada em 11/06/2016

OBJETIVO:
    Este programa tem como seu objetivo medir a quantidade de tempo e memória gastos para ordenar em ordem crescente
    uma lista duplamente encadeada com cabeça e cauda, utilizando o método do mergesort. Para tal, são realizadas 50
    iterações, cada uma criando uma lista única e ordenando-a. Então, é feita uma média de tempo e memória gasta e
    essa média é apresentada na tela.

MÉTODO GERAL:
    A lista de tarefas gerais é:
    1. Criar uma lista duplamente encadeada com cabeça e cauda de N elementos (definida pelo usuário através deste código);
    2. Ordenar a lista utilizando o algorítmo Mergesort, contando a quantidade de tempo e memória gastas para tal;
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
struct cel{
    int conteudo;
    struct cel * ant;
    struct cel * seg;
};

typedef struct cel celula;

/*====================
CABEÇALHO DE FUNÇÕES
====================*/

void Insere(celula * p, int x);
void Imprime(celula * p);
void CriaLista(celula * p);
void MergeSort(celula * lst, int n);
void Intercala(celula * p, celula * q, celula * r);
void Remover(celula *p);
void RemoverTodas(celula * p);

/*====================
VARIÁVEIS GLOBAIS
====================*/

double memoria = 0; /* Essa variável vai quantificar a de memória gasta por iteração para a ordenação */

/*====================================
INÍCIO
====================================*/

int main(){
    clock_t start, end;
    double cpu_time_used;
    double media = 0;
    int i;
    celula *p; /*essa variável aponta para a cabeça da lista*/
    celula h, t; /* h é a cabeça da lista, t é a cauda */

    h.ant = t.seg = NULL;
    h.seg = &t;
    t.ant = &h;
    p = &h;

    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    for (i = 0; i < I; i++) {
        CriaLista(p);/* Aqui ele cria uma nova lista */

        start = clock();/* Realiza a ordenação */
        MergeSort(p, N);
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;/* Calcula o tempo */
        media += cpu_time_used;

        RemoverTodas(p);/* Depois remove as células de conteúdo da lista atual */
    }

    printf("Tempo médio para lista de tamanho %d: %.7fs\n", N, (media/I));
    printf("Memória média gasta com alocação de uma lista e sua ordenação: %.2f bytes\n", memoria/I);

    return 0;
}

void CriaLista(celula * p){
    /* =============================================================================================
        Essa função cria uma lista duplamente encadeada de n células com valores aleatórios
    ==============================================================================================*/
    int i;

    memoria += sizeof(int) + sizeof(celula*);

    for(i = 0; i < N; i++)
        Insere(p, (rand()%10000));
}

void Insere(celula *p, int x){
    /*========================================================================================================
        Essa função cria uma nova célula de uma lista duplamente encadeada
    ========================================================================================================*/
    celula * nova = (celula*) malloc(sizeof(celula));

    memoria += sizeof(celula*)*2 + sizeof(int);

    nova->conteudo = x;
    nova->seg = p->seg;
    nova->ant = p;
    p->seg->ant = nova;
    p->seg = nova;
}

void Imprime(celula *p){
    /*====================================================================================================
        Essa função imprime todos os conteudos das células de uma determinada lista encadeada
    ====================================================================================================*/
    celula * lst = p->seg;

    while(lst->seg != NULL){
        printf("[%2i]", lst->conteudo);
        lst = lst->seg;
    }
    printf("\n\n");
}

void MergeSort(celula * lst, int n){
    /*===================================================================================================
        Esse algorítmo de ordenação divide uma lista duplamente encadeada em duas, ordena as duas
        individualmente, e depois as junta (merge) intercalando seus valores.
        Ela utiliza o ponteiro da primeira célula da lista, e um valor n, que é o total de elementos
        da lista, para achar a célula da metade e realizar a divisão das listas
    ===================================================================================================*/
    int i;
    celula * p, *q;

    memoria += sizeof(celula*)*3 + sizeof(int)*2;

    if(n > 1){
        MergeSort (lst, n/2); /* Realiza a ordenação da primeira metade da lista */
        p = lst; /* Agora ele vai encontrar a célula que está na metade da lista */
        for (i = 0; i < (n)/2; i++)
            p = p->seg;
        MergeSort (p, (n+1)/2); /* E então ele ordena a segunda metade da lista*/

        p = lst->seg;
        for (i = 0; i < (n/2)-1; i++)
            p = p->seg;
        q = p;
        for (i = 0; i < (n+1)/2; i++)
            q = q->seg;

        Intercala(lst->seg, p, q); /* Agora ele vai juntar as duas listas em uma só */
    }
}

void Intercala(celula * p, celula * q, celula * r){
    /*============================================================================================================
        Intercala funciona praticamente da mesma maneira que a implementada em sala, somente com algumas
        modificações. Ele separa a lista recebida em duas listas X (p, q) e Y (q->seg, r), e depois
        junta ambas de maneira ordenada, intercalando suas células
    ============================================================================================================*/

    celula * B = (celula*) malloc(sizeof(celula));
    celula * guardaR = r->seg,* guardaP = p->ant, * aux = q; /* Guarda vai receber o endereço seguinte ao ultimo dessa lista e
                                                                o anterior ao primeiro. Fiz essa consideração pois pode ser uma
                                                                lista que nao comece na cabeça e nem termine na cauda.
                                                                aux é auxiliar somente kkkk*/

    memoria += sizeof(celula*)*7;

    B->seg = NULL; /* Aprontando a cabeça da lista auxiliar */
    q = q->seg; /* q seria o final da lista X, então q->seg é o inicio da lista Y. Usarei q para percorrê-la */
    aux->seg = NULL; /* Como salvei o fim da lista X em aux, aqui eu finalmente separo X de Y */
    r->seg = NULL; /* Aqui separo Y de qualquer possível continuação */
    aux = B; /* aux agora vai guardar o endereço da cabeça da lista B */

    /*
        Os seguintes blocos de while percorrem as listas X e Y, e adicionam, de cada vez, a menor célula
        comparada entre elas à lista B.
    */

    while((p!=NULL)&&(q!=NULL)){
        if(p->conteudo < q->conteudo){
            B->seg = p;
            p->ant = B;
            p = p->seg;
        }
        else{
            B->seg = q;
            q->ant = B;
            q = q->seg;
        }
        B = B->seg;
    }
    while(p!=NULL){
        B->seg = p;
        p->ant = B;
        p = p->seg;
        B = B->seg;
    }
    while(q!=NULL){
        B->seg = q;
        q->ant = B;
        q = q->seg;
        B = B->seg;
    }

    /* Agora chega a hora de colocar a lista intercalada de volta na lista original, restaurando seu início e fim */

    B->seg = guardaR;
    if(B->seg != NULL)
        B->seg->ant = B;
    aux->seg->ant = guardaP;
    if(aux->seg->ant != NULL)
        aux->seg->ant->seg = aux->seg;

    free(aux); /* e aqui, libero a cabeça da lista provisória */
}

void Remover(celula * p){
    /*=====================================================================================
        Essa função remove a célula seguinte à célula recebida por parâmetro
    =====================================================================================*/
    celula * lixo = p->seg;
    p->seg = lixo->seg;
    lixo->seg->ant = p;

    free(lixo);
}

void RemoverTodas(celula * p){
    /*=====================================================================================
        Essa função remove todos os elementos da lista. A função remover sempre removerá
        o seguinte, então o while termina quando a célula seguinte for a cauda
    =====================================================================================*/
    while(p->seg->seg != NULL)
        Remover(p);
}
