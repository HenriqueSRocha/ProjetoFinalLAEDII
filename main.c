/*
    Projeto Monitoramento do Consumo de Energia Elétrica

    Henrique de Souza Rocha
    Andre Luiz Magalhaes

    Novembro de 2023

    compilar: gcc main funcoes.c lib.c -o monitoramento
 */

#include <stdio.h>
#include "lib.h" // Biblioteca com as estruturas e funções

int main()
{
    FILE *arquivo;
    dado dadosLidos;
    Lista lista;
    int continuar;

    do
    {
        cria(&lista);                                  // Cria a lista
        continuar = menu(&lista, dadosLidos, arquivo); // Imprime o menu
    } while (continuar != 0);

    return 0;
}
