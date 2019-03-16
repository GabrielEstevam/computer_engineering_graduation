/**=====================================================================================================================

ARQUIVO: Heapsort.c
TÍTULO: Heapsort em Lista
CODIFICADO POR: Gabriel Estevam de Oliveira(15104138), Raul Mendes Rosá(15102828), Igor Zanelatto Favro(15102818)
    O código utiliza versões modificadas de algorítmos vistos em sala de aula, como Heap Sort, Inserção e Remoção de
    listas duplamente encadeadas, Max Heapfica, entre outros.
PARA A DISCIPLINA DE: Estrutura de Dados I
CURSO: Engenharia da Computação
DATA: Versão final codificada em 22/06/2016

OBJETIVO:
    Este programa tem como seu objetivo medir a quantidade de tempo e memória gastos para ordenar em ordem crescente
    uma lista duplamente encadeada sem cabeça circular, utilizando o método do hea´psort. Para tal, são realizadas 50
    iterações, cada uma criando uma lista única e ordenando-a. Então, é feita uma média de tempo e memória gasta e
    essa média é apresentada na tela.

MÉTODO GERAL:
    A lista de tarefas gerais é:
    1. Criar uma lista duplamente encadeada sem cabeça de N elementos (definida pelo usuário através deste código);
    2. Criar um vetor para receber os filhos à esquerda do futuro Max Heap;
    3. Ordenar a lista utilizando o algorítmo Heapsort, contando a quantidade de tempo e memória gastas para tal;
    3. Repetir os passos 1, 2 e 3 por I iterações (recomenda-se 50, mas o usuário pode alterar a quantidade desejada
    no código) e apresentar a quantidade de memória e a média de tempo gastos em uma iteração.

ARQUIVOS INCLUÍDOS:
    stdio.h
    stdlib.h
    time.h
    locale.h

=====================================================================================================================**/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#define I 50 /* Define a quantidade de iterações realizadas pelo algorítmo */
#define N 100 /* Define o tamanho de elementos presentes na lista encadeada */

/*=================
REGISTROS
=================*/

/* Declaração da lista encadeada */
struct cel_ {
    int conteudo;
    struct cel_ * seg;
    struct cel_ * ant;
};

typedef struct cel_ celula;

/*====================
CABEÇALHO DE FUNÇÕES
====================*/

void imprimeLista(celula * lst);
void maxheapfica(celula * p, int i, celula ** V, int n);
void construir_maxheap(celula * p, int n, celula ** V);
void Heapsort(celula * p, int n, celula ** Vf, celula ** Vp);
void verificaCrescente(celula * lst);
void Remover(celula * lst);
celula * inserirCelula(celula * lst, int x);
celula * criaLista (int n);
celula * RemoverTodas(celula * lst);
celula * inserir_maxheap(celula * p, celula * t, int x, int i, celula ** V);

/*====================
VARIÁVEIS GLOBAIS
====================*/

double memoria = 0; /* Essa variável vai quantificar a de memória gasta por iteração para a ordenação */

/*====================================
INÍCIO
====================================*/

int main(){
    int i, j;
    celula * lst;
    celula ** Vf = (celula**)malloc(sizeof(celula*) * (N/2 + 1)); /* Esse vetor irá armazenar os filhos à esquerda dos elementos
                                                                     da lista max heap*/
    celula ** Vp = (celula**)malloc(sizeof(celula*) * (N/2 + 1)); /* E esse vetor irá armazenar os pais de todos os elementos da lista */
    clock_t start, end;
    double cpu_time_used;
    double media = 0;

    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    for (i = 0; i < I; i++) {
        lst = criaLista(N);/* Aqui ele cria uma nova lista */

        memoria += sizeof(celula **)*(N/2 + 1)*2; /*Memoria utilizada pelos vetores auxiliares*/

        /*Aqui são criados os vetores que guardam os filhos à esquerda e os pais a serem usados*/
        Vf[1] = lst->seg;
        Vp[1] = lst;
        for(j = 2; j <= N/2; j++){
            Vf[j] = Vf[j-1]->seg->seg;/* Insere no vetor os filhos á esquerda*/
            Vp[j] = Vp[j-1]->seg;/* E aqui insere os pais */
        }
        /*=====================================================================================*/

        start = clock();/* Realiza a ordenação */
        Heapsort(lst, N, Vf, Vp);
        end = clock();
        verificaCrescente(lst);

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;/* Calcula o tempo */
        media += cpu_time_used;

        lst = RemoverTodas(lst);/* Depois limpa a memória usada com a lista atual, deixando lst
                                    pronta para receber uma nova lista aleatória */
    }
    free(Vf);
    free(Vp);

    printf("Tempo médio para lista de tamanho %d: %.7fs\n", N, (media/I));
    printf("Memória média gasta com alocação de uma lista e sua ordenação: %.2f bytes\n", memoria/I);


    return 0;
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

/** Funções do heapsort **/
celula * inserir_maxheap(celula * p, celula * t, int x, int i, celula ** V){
    /*===================================================================================
        Essa função recebe um max heap que vai da célula apontada por p até a célula
        apontada por t, e insere um novo elemento, reajustando o max heap caso algum
        problema ocorra nesta inserção, e então retorna o endereço seguinte ao final do
        max heap
    ===================================================================================*/
    celula * f = t->seg;
    celula * g = f;
    int auxf = i + 1;
    int aux;

    memoria += sizeof(celula*)*4 + sizeof(int)*4 + sizeof(celula**);

    g = V[auxf/2];

    /* Agora que foi inserido o elemento, este bloco de while vai verificar se o pai do elemento
    é maior que o elemento inserido. Se não foi, eles são trocados e a mesma verificação é feita
    pro próximo pai */
    while(auxf != 1 && g->conteudo < f->conteudo){
        aux = f->conteudo;
        f->conteudo = g->conteudo;
        g->conteudo = aux;
        f = g;

        auxf = auxf/2;

        g = V[auxf/2];
    }

    return t->seg;
}

void construir_maxheap(celula * p, int n, celula ** V){
    /*========================================================================================
        Essa função transforma uma lista encadeada qualquer em um Max Heap, utilizando
        a função inserir_maxheap para ajustar os elementos nela presentes
    ========================================================================================*/
    celula * t = p;
    int i;

    memoria += sizeof(celula*)*2 + sizeof(int)*2 + sizeof(celula**);

    for(i = 1; i < n; i++)
        t = inserir_maxheap(p, t, t->seg->conteudo, i, V);
}

void maxheapfica(celula * p, int i, celula ** V, int n){
    /*============================================================================
        Essa função recebe um quase max heap, e o transforma num max heap
    ============================================================================*/
    int auxr = 1, aux, ife = 2 * auxr, ifd = 2 * auxr + 1;
    celula * r = p, * maior = r;

    memoria += sizeof(celula*)*5 + sizeof(int)*6 + sizeof(celula**);

    /** Verificando qual o maior dentre o pai e seus filhos **/

    if (ife <= i && ife != 0 && V[auxr]->conteudo > maior->conteudo)
        maior = V[auxr];
    if (ifd <= i && ifd != 0 && V[auxr]->seg->conteudo > maior->conteudo)
        maior = V[auxr]->seg;

    if (maior == V[auxr])
        auxr = ife;
    else if (maior == V[auxr]->seg)
        auxr = ifd;

    while (maior != r){
        aux = r->conteudo;
        r->conteudo = maior->conteudo;
        maior->conteudo = aux;

        r = maior;

        /** Reinicia os valores **/
        ife = 2 * auxr;
        ifd = 2 * auxr + 1;
        /** =================== **/

        if (auxr <= n/2){
            if (ife <= i && ife != 0 && V[auxr]->conteudo > maior->conteudo)
                maior = V[auxr];
            if (ifd <= i && ifd != 0 && V[auxr]->seg->conteudo > maior->conteudo)
                maior = V[auxr]->seg;

            if (maior == V[auxr])
                auxr = ife;
            else if (maior == V[auxr]->seg)
                auxr = ifd;
        }
    }
}

void Heapsort(celula * p, int n, celula ** Vf, celula ** Vp){
    /*=====================================================================================================
        Essa função ordena uma lista encadeada da seguinte forma: Ela transforma a lista em um
        max heap, e depois utiliza da propriedade deste estrutura, que diz que o elemento raiz
        é o maior elemento da lista, para ordená-la de modo crescente, trocando o primeiro
        elemento com o ultimo, reconstruindo o max heap ignorando os elementos ja ordenados, e
        então repetindo o processo
    =====================================================================================================*/
    celula * t;
    int aux, auxt = n;

    memoria += sizeof(celula*)*2 + sizeof(int)*3 + sizeof(celula**)*2;

    construir_maxheap(p, n, Vp); /* Neste ponto, ele transforma a lista em um max heap*/
    t = p->ant;

    while (auxt >= 2){
        /**
            Neste bloco de while, ele coloca o maior numero no final da lista, e transforma
            a lista de tamanho auxt - 1 e um novo max heap, para repetir o processo
        **/
        aux = p->conteudo;
        p->conteudo = t->conteudo;
        t->conteudo = aux;

        auxt--;

        t = t->ant;

        maxheapfica(p, auxt, Vf, n);
    }
}

void verificaCrescente(celula * lst) {
    /*==========================================================================
        Essa função verifica se uma lista encadeada é crescente ou não
    ==========================================================================*/
    celula * aux =  lst;
    while (lst->seg != aux) {
        if (lst->seg->conteudo < lst->conteudo) {
            printf("ERRO\n");
            break;
        }
        lst = lst->seg;
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

    while(lst->seg != lst){
        Remover(lst);
    }
    free(lst);
    return NULL;
}
