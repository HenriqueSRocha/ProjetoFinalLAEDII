#include <stdio.h>

typedef struct Data     // Estrutura para armazenar os dados da lista
{
    float numero;
    int ano, mes, dia, hora, minuto, segundo;
} dado;

typedef struct no       // Estrutura do nó da lista
{
    struct no *ant;
    struct no *prox;
    dado dados;
} Node;

typedef struct      // Estrutura da lista
{
    Node *primeiro;
    Node *ultimo;
    int tam;
} Lista;

void cria(Lista *lst);      // Cria a lista
void imprimeLista(Lista *lista);     // Imprime os dados da lista
int insere(Lista *lst, dado dados);     // Insere um novo nó na lista
int preencheLista(Lista *lista, dado dadosLidos, FILE *arquivo);        // Coloca os dados do arquivo na lista
int menu(Lista *lista, dado dadosLidos, FILE *arquivo);        // Imprime o menu
