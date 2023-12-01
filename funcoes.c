#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

void cria(Lista *lst) // Cria a lista
{
    lst->primeiro = NULL;
    lst->ultimo = NULL;
    lst->tam = 0;
}

int insere(Lista *lst, dado dados) // Insere um novo nó na lista
{
    Node *aux;
    aux = (Node *)malloc(sizeof(Node));
    if (aux == NULL)
        return 0;

    aux->dados = dados;

    if (lst->primeiro == NULL) // Lista vazia

    {
        lst->primeiro = aux;
        lst->ultimo = aux;
        aux->ant = lst->ultimo;
        aux->prox = lst->primeiro;
    }
    else // Insere no final da lista
    {
        aux->ant = lst->ultimo;
        aux->prox = lst->primeiro;
        lst->ultimo->prox = aux;
        lst->primeiro->ant = aux;
        lst->ultimo = aux;
    }
    lst->tam++;
    return 1;
}

int preencheLista(Lista *lista, dado dadosLidos, FILE *arquivo) // Coloca os dados do arquivo na lista
{
    char linha[50];

    arquivo = fopen("saida.txt", "r"); // Abre o arquivo

    if (arquivo == NULL) // Verifica se o arquivo foi aberto
    {
        fprintf(stderr, "ERRO! Nao foi possivel abrir o arquivo\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) // Lê o arquivo linha por linha
    {
        sscanf(linha, "%f - %04d-%02d-%02d %02d:%02d:%02d", &dadosLidos.numero, &dadosLidos.ano,
               &dadosLidos.mes, &dadosLidos.dia, &dadosLidos.hora, &dadosLidos.minuto, &dadosLidos.segundo);

        insere(lista, dadosLidos); // Insere os dados na lista
    }

    fclose(arquivo); // Fecha o arquivo

    return 0;
}

void imprimeLista(Lista *lista) // Imprime os dados da lista
{
    Node *imprime = lista->primeiro;
    for (int i = 0; i < lista->tam; i++)
    {
        printf("Potencia: %.2f[W] -  %02d:%02d:%02d  %02d-%02d-%04d\n", imprime->dados.numero, imprime->dados.hora,
               imprime->dados.minuto, imprime->dados.segundo, imprime->dados.dia, imprime->dados.mes, imprime->dados.ano);
        imprime = imprime->prox;
    }
}

int menu(Lista *lista, dado dadosLidos, FILE *arquivo)      // Imprime o menu
{
    int opcao;

    printf("\nDigite a opção de sejada:\n");
    printf("1 - Imprimir a lista\n");
    printf("2 - Sair\n");

    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:     // Imprime a lista
        preencheLista(lista, dadosLidos, arquivo);
        imprimeLista(lista);
        break;
    case 2:     // Sai do programa
        return 0;
        break;
    default:        // Opção inválida
        printf("\e[H\e[2J");
        printf("Opção inválida!\n");
        return 1;
        break;
    }
}