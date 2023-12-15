#include <stdio.h>
#include <stdlib.h>     // Biblioteca para usar o malloc
#include "lib.h"        // Biblioteca com as estruturas e funções

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
    dado fim = {0.0, 0, 0, 0, 0, 0, 0};
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
    insere(lista, fim);

    return 0;
}

void imprimeLista(Lista *lista) // Imprime os dados da lista
{
    Node *imprime = lista->primeiro;
    for (int i = 0; i < lista->tam; i++)
    {
        if (imprime->dados.ano != 0)
            printf("Potencia: %.2f[W] -  %02d:%02d:%02d  %02d-%02d-%04d\n", imprime->dados.numero, imprime->dados.hora,
                   imprime->dados.minuto, imprime->dados.segundo, imprime->dados.dia, imprime->dados.mes, imprime->dados.ano);
        imprime = imprime->prox;
    }
}

int menu(Lista *lista, dado dadosLidos, FILE *arquivo) // Imprime o menu
{
    int opcao = 0, opcao2 = 0, opcao3 = 0;
    float potencia;

    printf("Digite a opção de sejada:\n\n");
    printf("1 - Imprimir a lista\n");
    printf("2 - Buscar potencia\n");
    printf("3 - Sair\n");

    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1: // Imprime a lista
        printf("\nDigite a opcao de sejada:\n\n");
        printf("1 - Imprimir a lista pela data e hora\n");
        printf("2 - Imprimir a lista pela potencia\n");
        scanf("%d", &opcao2);
        switch (opcao2)
        {
        case 1:     // Imprime a lista pela data e hora
            preencheLista(lista, dadosLidos, arquivo);
            imprimeLista(lista);
            break;
        case 2:     // Imprime a lista pela potencia
            preencheLista(lista, dadosLidos, arquivo);
            ordenaLista(lista);
            imprimeLista(lista);
            break;
        default:    // Opção inválida
            printf("Opcao invalida!\n\n");
            return 0;
        }
        break;
    case 2:       // Busca uma potencia
        printf("\nDigite a opcao de sejada:\n\n");
        printf("1 - Buscar maior potencia\n");
        printf("2 - buscar menor potencia\n");
        printf("3 - buscar potencia especifica\n");
        scanf("%d", &opcao3);
        switch (opcao3)
        {
        case 1: // Busca a maior potencia
            preencheLista(lista, dadosLidos, arquivo);
            maiorLista(*lista);
            break;
        case 2: // Busca a menor potencia
            preencheLista(lista, dadosLidos, arquivo);
            menorLista(*lista);
            break;
        case 3: // Busca uma potencia especifica
            printf("Digite a potencia desejada: ");
            scanf("%f", &potencia);
            preencheLista(lista, dadosLidos, arquivo);
            buscarPotencia(lista, potencia);
            break;
        default:
            printf("Opcao invalida!\n\n");
            return 0;
        }
        break;
    case 3: // Sai do programa
        return 0;
    default: // Opção inválida
        printf("Opção invalida!\n\n");
        return 0;
    }
    return 0;
}
void maiorLista(Lista lista) // Busca o maior valor da lista
{
    Node *maior = lista.primeiro;
    Node *aux = lista.primeiro;
    maior->dados.numero = 0.0;

    for (int i = 0; i < lista.tam; i++)
    {
        if ((maior->dados.numero) < (aux->dados.numero))
        {
            maior->dados.numero = aux->dados.numero;
            maior->dados.ano = aux->dados.ano;
            maior->dados.mes = aux->dados.mes;
            maior->dados.dia = aux->dados.dia;
            maior->dados.hora = aux->dados.hora;
            maior->dados.minuto = aux->dados.minuto;
            maior->dados.segundo = aux->dados.segundo;
        }
        aux = aux->prox;
    }
    printf("\nMAIOR Potencia: %.2f[W] -  %02d:%02d:%02d  %02d-%02d-%04d\n\n\n", maior->dados.numero, maior->dados.hora,
           maior->dados.minuto, maior->dados.segundo, maior->dados.dia, maior->dados.mes, maior->dados.ano);
}

void menorLista(Lista lista) // Busca o menor valor da lista
{
    Node *menor = lista.primeiro;
    Node *aux = lista.primeiro;
    menor->dados.numero = 999;

    for (int i = 0; i < lista.tam; i++)
    {
        if (menor->dados.numero > aux->dados.numero && aux->dados.mes != 0)
        {
            menor->dados.numero = aux->dados.numero;
            menor->dados.ano = aux->dados.ano;
            menor->dados.mes = aux->dados.mes;
            menor->dados.dia = aux->dados.dia;
            menor->dados.hora = aux->dados.hora;
            menor->dados.minuto = aux->dados.minuto;
            menor->dados.segundo = aux->dados.segundo;
        }
        aux = aux->prox;
    }
    printf("\nMENOR Potencia: %.2f[W] -  %02d:%02d:%02d  %02d-%02d-%04d\n\n\n", menor->dados.numero, menor->dados.hora,
           menor->dados.minuto, menor->dados.segundo, menor->dados.dia, menor->dados.mes, menor->dados.ano);
}
void ordenaLista(Lista *lista) // Ordena a lista
{
    int trocou;
    Node *atual;
    Node *anterior = NULL;

    if (lista == NULL || lista->tam <= 1) // Lista vazia ou com apenas um elemento
        return;

    do
    {
        atual = lista->primeiro;
        trocou = 0;
        while (atual->prox->dados.ano != 0)
        {
            if (atual->dados.numero > atual->prox->dados.numero)
            {
                trocaNodes(atual, atual->prox);
                trocou = 1;
            }
            anterior = atual;
            atual = atual->prox;
        }
    } while (trocou);
}

void trocaNodes(Node *a, Node *b)   // Troca os dados de dois nos
{
    dado temp = a->dados;
    a->dados = b->dados;
    b->dados = temp;
}

void buscarPotencia(Lista *lista, float potenciaBuscada)    // Busca uma potencia especifica na lista
{
    if (lista->primeiro == NULL)
    {
        printf("A lista está vazia.\n");
        return;
    }

    Node *atual = lista->primeiro;
    int encontrado = 0;
    printf("\n");
    do
    {
        if (atual->dados.numero == potenciaBuscada)
        {
            encontrado = 1;
            printf("Potencia: %.2f[W] -  %02d:%02d:%02d  %02d-%02d-%04d\n", atual->dados.numero, atual->dados.hora,
                   atual->dados.minuto, atual->dados.segundo, atual->dados.dia, atual->dados.mes, atual->dados.ano);
        }
        atual = atual->prox;
    } while (atual != lista->primeiro);

    if (!encontrado)
    {
        printf("\n\nPotencia %.2f não encontrada na lista.\n\n", potenciaBuscada);
    }
}
