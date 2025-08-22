#include "2048.h" //Incluindo declarações das funções

void limpar_buffer() // limpa o buffer
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
    printf("-----------COMANDOS-----------\n");
    printf("- <w, a, s, d>: Movem as peças do tabuleiro para cima, esquerda, para baixo ou para direita, respectivamente.\n- <u>: Desfazer o  ́ultimo movimento.\n- <t pos1, pos2>: Trocar duas peças de posição, ou seja, troca o conteúdo da posição pos1 com o conteúdo da posição pos2.\n");

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

    printf("   "); // letras
    for (int i = 0; i < n; i++)
    {
        printf(" %*c ", tamanhoDaCelula, (char)97 + i);

        if (i < n - 1)
        {
            printf(" ");
        }
    }
    printf(" \n");

    printf("  ┏"); // parte de cima
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
        printf("%d ", 1 + i);

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
            printf("  ┣");
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

    printf("  ┗"); // imprime a parte de baixo
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

    printf("Jogada: ");
}

int **criaMatriz(int n) // cria matriz com alocação dinâmica
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

void liberaMatriz(int **matriz, int n) // libera uma matriz criada em alocacção dinâmica
{
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

void novoNumeroAleatorio(int n, int **matriz) // cria um novo número aleatório em uma celula aleatória da matriz
{
    srand(time(NULL)); // semente pra geração de número aleatório

    int i, j;               // coordenadas da matriz
    int probabilidade, nro; // define a probabilidade de a nova peça ser um 4;
    do                      // define coordenadas
    {
        i = rand() % n;
        j = rand() % n;
    } while (matriz[i][j] != 0);

    switch (n) // define a probabilidade com base no tamanho do tabuleiro
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

    nro = (rand() % 100) + 1; // gera número de 1 a 100

    if (nro < probabilidade) // define qual será o valor da nova peça
    {
        matriz[i][j] = 4;
    }
    else
        matriz[i][j] = 2;
}

int confereMovimento(int n, int **matriz, int **matrizAux) // função que confere se houve movimento no tabuleiro do jogo
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matriz[i][j] != matrizAux[i][j])
                return 1;
        }
    }

    return 0;
}

void movimentacaoEsquerda(int n, int **matriz) // movimenta as peças no tabuleiro
{
    int moveu;                       // variavel que mostra quando o movimento não é mais possivel
    int **matrizAux = criaMatriz(n); // criando matriz auxiliar
    do
    {
        moveu = 0; // começa o movimento com a variavel como 0

        for (int i = 0; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (matriz[i][j] != 0 && matriz[i][j - 1] == 0) // move a peça e troca o valor da posição inicial por 0
                {
                    matriz[i][j - 1] = matriz[i][j];
                    matriz[i][j] = 0;

                    moveu = 1; // variavel indicando que houve movimento
                }
                else if (matriz[i][j] != 0 && matriz[i][j - 1] == matriz[i][j] && matrizAux[i][j - 1] == 0 && matrizAux[i][j] == 0) // movimento pra quando as peças devem ser combinadas
                {
                    matriz[i][j - 1] = (matriz[i][j]) * 2;
                    matriz[i][j] = 0;

                    matrizAux[i][j - 1] = 1;

                    moveu = 1; // variavel indicando que houve movimento
                }
            }
        }

    } while (moveu); // lógica booleana que repete o código enquanto a condição "moveu" for verdadeira

    liberaMatriz(matrizAux, n); // libera a matriz auxiliar criada
}

void movimentacaoDireita(int n, int **matriz) // movimenta as peças no tabuleiro
{
    int moveu;                       // variavel que mostra quando o movimento não é mais possivel
    int **matrizAux = criaMatriz(n); // criando matriz auxiliar
    do
    {
        moveu = 0; // começa o movimento com a variavel como 0

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - 1; j++)
            {
                if (matriz[i][j] != 0 && matriz[i][j + 1] == 0) // move a peça e troca o valor da posição inicial por 0
                {
                    matriz[i][j + 1] = matriz[i][j];
                    matriz[i][j] = 0;

                    moveu = 1; // variavel indicando que houve movimento
                }
                else if (matriz[i][j] != 0 && matriz[i][j + 1] == matriz[i][j] && matrizAux[i][j + 1] == 0 && matrizAux[i][j] == 0) // movimento pra quando as peças devem ser combinadas
                {
                    matriz[i][j + 1] = (matriz[i][j]) * 2;
                    matriz[i][j] = 0;

                    matrizAux[i][j + 1] = 1;

                    moveu = 1; // variavel indicando que houve movimento
                }
            }
        }

    } while (moveu); // lógica booleana que repete o código enquanto a condição "moveu" for verdadeira

    liberaMatriz(matrizAux, n); // libera a matriz auxiliar criada
}

void movimentacaoCima(int n, int **matriz) // movimenta as peças no tabuleiro
{
    int moveu;                       // variavel que mostra quando o movimento não é mais possivel
    int **matrizAux = criaMatriz(n); // criando matriz auxiliar
    do
    {
        moveu = 0; // começa o movimento com a variavel como 0

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matriz[i][j] != 0 && matriz[i - 1][j] == 0) // move a peça e troca o valor da posição inicial por 0
                {
                    matriz[i - 1][j] = matriz[i][j];
                    matriz[i][j] = 0;

                    moveu = 1; // variavel indicando que houve movimento
                }
                else if (matriz[i][j] != 0 && matriz[i - 1][j] == matriz[i][j] && matrizAux[i - 1][j] == 0 && matrizAux[i][j] == 0) // movimento pra quando as peças devem ser combinadas
                {
                    matriz[i - 1][j] = (matriz[i][j]) * 2;
                    matriz[i][j] = 0;

                    matrizAux[i - 1][j] = 1;

                    moveu = 1; // variavel indicando que houve movimento
                }
            }
        }

    } while (moveu); // lógica booleana que repete o código enquanto a condição "moveu" for verdadeira

    liberaMatriz(matrizAux, n); // libera a matriz auxiliar criada
}

void movimentacaoBaixo(int n, int **matriz) // movimenta as peças no tabuleiro
{
    int moveu;                       // variavel que mostra quando o movimento não é mais possivel
    int **matrizAux = criaMatriz(n); // criando matriz auxiliar
    do
    {
        moveu = 0; // começa o movimento com a variavel como 0

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matriz[i][j] != 0 && matriz[i + 1][j] == 0) // move a peça e troca o valor da posição inicial por 0
                {
                    matriz[i + 1][j] = matriz[i][j];
                    matriz[i][j] = 0;

                    moveu = 1; // variavel indicando que houve movimento
                }
                else if (matriz[i][j] != 0 && matriz[i + 1][j] == matriz[i][j] && matrizAux[i + 1][j] == 0 && matrizAux[i][j] == 0) // movimento pra quando as peças devem ser combinadas
                {
                    matriz[i + 1][j] = (matriz[i][j]) * 2;
                    matriz[i][j] = 0;

                    matrizAux[i + 1][j] = 1;

                    moveu = 1; // variavel indicando que houve movimento
                }
            }
        }

    } while (moveu); // lógica booleana que repete o código enquanto a condição "moveu" for verdadeira

    liberaMatriz(matrizAux, n); // libera a matriz auxiliar criada
}

char verificaEntrada() // lê e valida a entrada de um único caractere do usuário
{
    char entrada[10];
    char escolha;

    do
    {
        fgets(entrada, 10, stdin);

        if (entrada[0] != '\n' && entrada[1] == '\n')
        {
            escolha = entrada[0];
            return escolha; // Retorna o caractere se a entrada for válida
        }
        else
        {
            printf("Resposta inválida!! Digite apenas uma letra e pressione Enter.\n");
        }
    } while (1);
}

void novoJogo() // corresponde a opção de novo jogo no menu
{
    int tamanho = tamanhoTabuleiro();
    int **matriz = criaMatriz(tamanho);
    int **matrizAux = criaMatriz(tamanho);

    novoNumeroAleatorio(tamanho, matriz);
    novoNumeroAleatorio(tamanho, matriz);

    emJogo(tamanho, matriz, matrizAux);

    liberaMatriz(matriz, tamanho);
    liberaMatriz(matrizAux, tamanho);
}

void emJogo(int tamanho, int **matriz, int **matrizAux) // função de jogo
{
    int ganhou = 0;
    int voltarMenu = 0; // flag usada pra voltar ao menu
    char jogada[20], jogadaChar;

    do // loop principal
    {
        for (int i = 0; i < tamanho; i++)
        {
            for (int j = 0; j < tamanho; j++)
            {
                matrizAux[i][j] = matriz[i][j];
            }
        }

        imprimeTabuleiro(tamanho, matriz);

        fgets(jogada, 20, stdin);
        jogada[strcspn(jogada, "\n")] = '\0'; // a função strcspn conta o número de algarismos até que a string 1 coincida com a 2, assim podemos trocar o valor da posição do "\n" por '\0'

        if (strcmp(jogada, "voltar") == 0) // compara duas strings e retorna 0 se forem iguais
        {
            printf("Voltando ao menu principal...\n");
            voltarMenu = 1;
            continue;
        }
        else if (strlen(jogada) == 1)
        {
            jogadaChar = jogada[0];

            switch (jogadaChar)
            {
            case 'd':
                movimentacaoDireita(tamanho, matriz);
                break;

            case 'a':
                movimentacaoEsquerda(tamanho, matriz);
                break;

            case 'w':
                movimentacaoCima(tamanho, matriz);
                break;

            case 's':
                movimentacaoBaixo(tamanho, matriz);
                break;

            case 'u':
                break;

            default:
                printf("Jogada inválida tente novamente: ");
                continue;
            }
        }
        else
        {
            printf("Comando inválido. Tente novamente.\n");
            continue;
        }

        if (confereMovimento(tamanho, matriz, matrizAux))
        {
            novoNumeroAleatorio(tamanho, matriz);
        }
        else
        {
            printf("Jogada inválida tente novamente: \n");
        }

        if (!ganhou)
        {
            if (verificaGanhou(tamanho, matriz))
            {
                ganhou++;
                if (vitoriaDecisao)
                {
                    voltarMenu = 1;
                }
            }
        }

    } while (!voltarMenu);
}

int verificaGanhou(int tamanho, int **matriz)
{
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            if (matriz[i][j] == 2048)
            {
                return 1;
            }
        }
    }

    return 0;
}

int vitoriaDecisao()
{
    int decisao;
    printf("Parabéns você conseguiu chegar a 2048!!\nVocê quer continuar jogando?\nDigite [1] pra continuar jogando e [0] pra voltar ao menu: ");
    scanf("%d", &decisao);

    do
    {
        if (decisao != 1 && decisao != 0)
        {
            printf("Resposta inválida!! Por favor digite novamente: ");
            scanf("%d", &decisao);
        }
    } while (decisao != 1 && decisao != 0);

    return decisao;
}

// pedir info de usuário, criar aquivo com o nome que o usuário decidir
//  função
// saveState(char nomeArq, int tamMatriz,int desfazer,int trocar, int pontuação, int nomeUser, int **matrizAtual, int **matrizAnterior); transformar info em struct
/*Formato do arquivo
Formato do arquivo texto:

<TAMANHO> <NDESFAZER> <NTROCAR>
<PONTUAÇÃO> <NOME>
<MATRIZ_TABULEIRO_ATUAL>
<MATRIZ_TABULEIRO_ULTIMA_JOGADA>

Onde:

INFO DE FORMATO ARQUIVO

<TAMANHO>: É um número inteiro (4, 5 ou 6) indicando o tamanho do tabuleiro;
<NDESFAZER>: número jogadas "desfazer" disponíveis (int)
<NTROCAR>: número jogadas "trocar" disponíveis (int)
<PONTUAÇÃO>: pontuação do jogador (int)
<NOME>: string de 27 posições que armazena o nome do jogador
<MATRIZ_TABULEIRO_ATUAL>: matriz de int com dimensão TAMANHO x TAMANHO, com os valores das células do jogo atual. O valor 0 (zero) indica uma posição vazia
<MATRIZ_TABULEIRO_ULTIMA_JOGADA>: matriz de int com dimensão TAMANHO x TAMANHO, com os valores das células da última jogada. O valor 0 (zero) indica uma posição vazia*/

// criar função em jogo, passar como parametros o tamanho e a matriz, save state a cada movimento