#include <stdio.h>
#include "2048.h" //Incluindo declarações das funções

void imprimeMenu()
{
    printf("-----------MENU-----------\n");
    printf("(R) Sair\n");
    printf("(N) Novo jogo\n");
    printf("(J) Continuar o jogo atual\n");
    printf("(C) Carregar um jogo salvo\n");
    printf("(S) Salvar o jogo atual\n");
    printf("(M) Mostrar Ranking\n");
    printf("(A) Ajuda com as instruções de como jogar\n");

    printf("\nDigite a sua resposta: ");
}

void limpar_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}