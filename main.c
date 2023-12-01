/*
    Projeto Monitoramento do Consumo de Energia Elétrica

    Henrique de Souza Rocha
    Andre Magalhaes Bastos

    Novembro de 2023

    compilar: gcc main funcoes.c lib.c -o main
 */

#include <stdio.h>
#include "lib.h" // Biblioteca com as estruturas e funções

int main()
{
    FILE *arquivo;
    dado dadosLidos;
    char linha[50];
    Lista lista;
    cria(&lista); // Cria a lista
    int continuar;

    do
    {
        continuar = menu(&lista, dadosLidos, arquivo); // Imprime o menu
        // preencheLista(&lista, dadosLidos, arquivo); // Coloca os dados do arquivo na lista
        // imprimeLista(lista);    // Imprime os dados da lista
    } while (continuar != 0);

    return 0;
}