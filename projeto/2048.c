#include <stdio.h>
#include "2048.h" //Incluindo declarações das funções

#define TAM_MATRIZ 4
#define TAM_CELULA 6

void limpar_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void imprimeMenu() // imprime o menu no terminal
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

int imprimeAjuda(int ajudaOk) // imprime o texto de ajuda no terminal
{
    printf("-----------AJUDA-----------\n");
    printf("O 2048 clássico é jogado em um tabuleiro de 4x4, com peças numéricas que deslizam suavemente quando o jogador as move em um dos quatro sentidos disponíveis: para cima, para baixo, à esquerda e à direita, a cada movimento, um novo número (com valor 2 ou 4) aparece aleatoriamente em um espaço vazio no tabuleiro. As peças (blocos) deslizam o mais longe possível na direção escolhida, até que sejam paradas por outra peça ou pela borda do tabuleiro. Se duas peças de mesmo número colidirem durante um movimento, elas se fundirão em uma única peça com o valor somado das duas que colidiram. A peça resultante não pode se fundir com outra peça na mesma jogada.\n");
    printf("-----------REGRAS-----------\n");
    printf("- O jogo começa com duas peças, posicionadas aleatoriamente no tabuleiro. \n- A cada jogada, o jogador deve escolher uma direção: para cima, para baixo, para a esquerda ou para a direita.\n- Após a escolha, todas as peças do tabuleiro deslizarão o máximo possível na direção indicada.\n- Se duas peças de mesmo valor colidirem durante o movimento, elas se combinarão em uma nova peça com a soma de seus valores.\n- Um movimento só é considerado válido se pelo menos uma peça se mover ou se combinar com outra.\n- Ao final de cada jogada válida, uma nova peça é adicionada em uma posição vazia aleatória.\n- Geralmente, essa nova peça será um 2, mas em 10%% das vezes, poderá ser um 4, a chance aumenta a depender do tamanho do tabuleiro 15%% para o 5x5 e 20%% para o 6x6\n- Para vencer, o jogador deve criar uma peça com o número 2048.\n- O jogo termina em derrota se o tabuleiro estiver cheio e não houver mais nenhum movimento válido possível.\n");
    printf("\nDigite [1] pra voltar ao menu: ");
    scanf("%d", &ajudaOk);
    return ajudaOk;
}

void imprimeTabuleiro()
{
    int t[TAM_MATRIZ][TAM_MATRIZ]; // cria a matriz

    for (int i = 0; i < TAM_MATRIZ; i++) // inicializa a matriz
    {
        for (int j = 0; j < TAM_MATRIZ; j++)
            t[i][j] = 2;
    }
    t[0][0] = 16;
    t[1][0] = 128;
    t[2][0] = 1024;

    printf("┏"); // parte de cima
    for (int i = 0; i < TAM_MATRIZ; i++)
    {
        for (int j = 0; j < TAM_CELULA; j++)
        {
            printf("━");
        }
        if (i < TAM_MATRIZ - 1) // imprime uma junta se não for o fim da linha
        {
            printf("┳");
        }
    }
    printf("┓\n");

    for (int i = 0; i < TAM_MATRIZ; i++) // imprime as linhas do meio
    {
        printf("┃");
        for (int j = 0; j < TAM_MATRIZ; j++)
        {
            printf(" %*d ", TAM_CELULA - 2, t[i][j]); // o código < %*d > usa o argumento < TAM_CELULA - 2 > como tamanho da célula
            printf("┃");
        }
        printf("\n");

        if (i < TAM_MATRIZ - 1) // verifica se a linha do meio deve ser impressa
        {
            printf("┣");
            for (int j = 0; j < TAM_MATRIZ; j++)
            {
                for (int k = 0; k < TAM_CELULA; k++)
                {
                    printf("━");
                }
                if (j < TAM_MATRIZ - 1) // verifica se a separação de celula deve ser escrita
                {
                    printf("╋");
                }
            }
            printf("┫\n");
        }
    }

    printf("┗"); // imprime a parte de baixo
    for (int i = 0; i < TAM_MATRIZ; i++)
    {
        for (int j = 0; j < TAM_CELULA; j++)
        {
            printf("━");
        }
        if (i < TAM_MATRIZ - 1)
        {
            printf("┻");
        }
    }
    printf("┛\n");
}