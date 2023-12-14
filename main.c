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
        cria(&lista); // Cria a lista
        continuar = menu(&lista, dadosLidos, arquivo); // Imprime o menu
    } while (continuar != 0);

    return 0;
}