#include "2048.h" //Incluindo declarações das funções

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
    printf("(N) Novo jogo\n");
    printf("(J) Continuar o jogo atual\n");
    printf("(C) Carregar um jogo salvo\n");
    printf("(S) Salvar o jogo atual\n");
    printf("(M) Mostrar Ranking\n");
    printf("(A) Ajuda com as instruções de como jogar\n");
    printf("(R) Sair\n");

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

int tamanhoCelula(int n, int **matriz) // define tamanho da célula
{
    int maior = matriz[0][0], count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matriz[i][j] > maior)
            {
                maior = matriz[i][j];
            }
        }
    }

    if (maior == 0)
    {
        return 1;
    }

    while (maior > 0)
    {
        maior = maior / 10;
        count++;
    }

    return count;
}

int **inicializaMatriz(int n, int **matriz) // inicializa matriz
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz[i][j] = 0;
        }
    }
}

void imprimeTabuleiro(int n, int **matriz) // imprime o tabuleiro do jogo
{
    char espaço = ' ';

    int tamanhoDaCelula = tamanhoCelula(n, matriz);

    printf("┏"); // parte de cima
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < tamanhoDaCelula + 2; j++)
        {
            printf("━");
        }
        if (i < n - 1) // imprime uma junta se não for o fim da linha
        {
            printf("┳");
        }
    }
    printf("┓\n");

    for (int i = 0; i < n; i++) // imprime as linhas do meio
    {
        printf("┃");
        for (int j = 0; j < n; j++)
        {
            if (matriz[i][j] == 0)
            {
                printf(" %*c ", tamanhoDaCelula, espaço);
            }
            else
                printf(" %*d ", tamanhoDaCelula, matriz[i][j]); // o código < %*d > usa o argumento < tamanhoDaCelula - 2 > como tamanho da célula
            printf("┃");
        }
        printf("\n");

        if (i < n - 1) // verifica se a linha do meio deve ser impressa
        {
            printf("┣");
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < tamanhoDaCelula + 2; k++)
                {
                    printf("━");
                }
                if (j < n - 1) // verifica se a separação de celula deve ser escrita
                {
                    printf("╋");
                }
            }
            printf("┫\n");
        }
    }

    printf("┗"); // imprime a parte de baixo
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < tamanhoDaCelula + 2; j++)
        {
            printf("━");
        }
        if (i < n - 1)
        {
            printf("┻");
        }
    }
    printf("┛\n");
}

int tamanhoTabuleiro() // decide o tamanho do tabuleiro
{
    int n, ok = 0;
    printf("Digite o tamanho do tabuleiro:\n- [4] Jogo padrão 4x4\n- [5] Jogo 5x5\n- [6] Jogo 6x6\nResposta: ");
    scanf("%d", &n);
    limpar_buffer();

    do
    {
        if (n > 6 || n < 4)
        {
            printf("Valor inválido, digite novamente: ");
            scanf("%d", &n);
            limpar_buffer();
            ok = 0;
        }
        else
            ok = 1;

    } while (ok != 1);

    return n;
}

int **criaMatriz(int n)
{
    int **matriz;
    matriz = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        matriz[i] = malloc(n * sizeof(int));
    }

    inicializaMatriz(n, matriz);

    return matriz;
}

void liberaMatriz(int **matriz, int n)
{
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

void novoNumeroAleatorio(int n, int **matriz)
{
    srand(time(NULL));

    int i, j;               // coordenadas da matriz
    int probabilidade, nro; // define a probabilidade de a nova peça ser um 4;
    do
    {
        i = rand() % n;
        j = rand() % n;
    } while (matriz[i][j] != 0);

    switch (n)
    {
    case 4:
        probabilidade = 10;
        break;
    case 5:
        probabilidade = 15;
        break;
    case 6:
        probabilidade = 20;
        break;
    }

    nro = (rand() % 100) + 1;

    if (nro < probabilidade)
    {
        matriz[i][j] = 4;
    }
    else
        matriz[i][j] = 2;
}
