#include "2048.h" //incluindo declarações das funções

void novoJogo() // corresponde a opção de novo jogo no menu
{
    GameState gameState; // struct com info do jogo atual

    gameState.tamanho = tamanhoTabuleiro();
    gameState.pontuacao = 0;
    gameState.desfazer = 0;
    gameState.trocar = 0;

    printf("Digite o seu nome: ");
    fgets(gameState.nomeUser, 27, stdin);
    removeN(gameState.nomeUser);

    gameState.matrizAtual = criaMatriz(gameState.tamanho);
    gameState.matrizAnterior = criaMatriz(gameState.tamanho);

    novoNumeroAleatorio(gameState.tamanho, gameState.matrizAtual);
    novoNumeroAleatorio(gameState.tamanho, gameState.matrizAtual);

    emJogo(&gameState);

    liberaMatriz(gameState.matrizAtual, gameState.tamanho);
    liberaMatriz(gameState.matrizAnterior, gameState.tamanho);
}

void emJogo(GameState *gameState) // função de jogo
{
    int ganhou = 0;
    int movimentoDesfeito = 0;
    int voltarMenu = 0; // flag usada pra voltar ao menu
    char jogada[20], jogadaChar;
    int **matrizAux = criaMatriz(gameState->tamanho); // matriz auxiliar

    int pontuacaoAnterior = gameState->pontuacao;
    int desfazerAnterior = gameState->desfazer;
    int trocarAnterior = gameState->trocar;

    do // loop principal
    {
        imprimeTabuleiro(gameState->tamanho, gameState->matrizAtual, gameState->pontuacao);

        fgets(jogada, 20, stdin);
        removeN(jogada);
        toLow(jogada);

        if (strcmp(jogada, "voltar") == 0) // compara duas strings e retorna 0 se forem iguais
        {
            printf("Voltando ao menu principal...\n");
            voltarMenu = 1;
            continue;
        }

        else if (jogada[0] == 't' && jogada[1] == ' ')
        {
            if (gameState->trocar > 0)
            {
                char coordenada1[3], coordenada2[3]; // variaveis pra guardar as coordenadas digitadas pelo usuário
                int linha1, col1, linha2, col2;

                if (sscanf(jogada, "t %2s %2s", coordenada1, coordenada2) == 2) // a função sscanf lê uma string e verifica formato do comando
                {
                    char letraCol1 = coordenada1[0];
                    char letraCol2 = coordenada2[0];

                    toLow(&letraCol1);
                    toLow(&letraCol2);

                    col1 = letraCol1 - 'a'; // cálculo dos indices usando a tabela ascii
                    linha1 = coordenada1[1] - '1';

                    col2 = letraCol2 - 'a'; // cálculo dos indices usando a tabela ascii
                    linha2 = coordenada2[1] - '1';

                    if (linha1 >= 0 && linha1 < gameState->tamanho && col1 >= 0 && col1 < gameState->tamanho &&
                        linha2 >= 0 && linha2 < gameState->tamanho && col2 >= 0 && col2 < gameState->tamanho) // verifica se as coordenadas são válidas
                    {
                        if (gameState->matrizAtual[linha1][col1] != 0 && gameState->matrizAtual[linha2][col2] != 0) // verifica se alguma das células está vazia
                        {
                            int aux = gameState->matrizAtual[linha1][col1]; // variavel auxiliar
                            gameState->matrizAtual[linha1][col1] = gameState->matrizAtual[linha2][col2];
                            gameState->matrizAtual[linha2][col2] = aux;

                            gameState->trocar--; // remove um crédito
                        }

                        else
                        {
                            printf("Não é possível trocar uma célula vazia!\n");
                        }
                    }
                    else
                    {
                        printf("Coordenadas inválidas! Ex: 't a1 c3'\n");
                    }
                }
                else
                {
                    printf("Formato do comando inválido! Use: t <pos1> <pos2>\n");
                }
            }
            else
            {
                printf("Você não tem chances para trocar peças!\n");
            }
            continue; // a troca não deve gerar uma nova peça no tabuleiro então pulamos o resto da iteração
        }

        else if (strlen(jogada) == 1)
        {
            jogadaChar = jogada[0];

            if (jogadaChar == 'u')
            {
                if (!movimentoDesfeito && gameState->desfazer > 0)
                {
                    for (int i = 0; i < gameState->tamanho; i++)
                    {
                        for (int j = 0; j < gameState->tamanho; j++)
                        {
                            gameState->matrizAtual[i][j] = gameState->matrizAnterior[i][j];
                        }
                    }
                    gameState->pontuacao = pontuacaoAnterior;
                    gameState->desfazer = desfazerAnterior;
                    gameState->trocar = trocarAnterior;

                    movimentoDesfeito = 1;
                    gameState->desfazer--;
                }
                else
                {
                    printf("Você não pode desfazer o movimento!!\n");
                }
                continue;
            }

            pontuacaoAnterior = gameState->pontuacao;
            desfazerAnterior = gameState->desfazer;
            trocarAnterior = gameState->trocar;
            for (int i = 0; i < gameState->tamanho; i++)
            {
                for (int j = 0; j < gameState->tamanho; j++)
                {
                    matrizAux[i][j] = gameState->matrizAtual[i][j];
                    gameState->matrizAnterior[i][j] = gameState->matrizAtual[i][j];
                }
            }

            switch (jogadaChar)
            {
            case 'd':
                gameState->pontuacao += movimentacaoDireita(gameState->tamanho, gameState->matrizAtual, &gameState->desfazer, &gameState->trocar);
                movimentoDesfeito = 0;
                break;

            case 'a':
                gameState->pontuacao += movimentacaoEsquerda(gameState->tamanho, gameState->matrizAtual, &gameState->desfazer, &gameState->trocar);
                movimentoDesfeito = 0;
                break;

            case 'w':
                gameState->pontuacao += movimentacaoCima(gameState->tamanho, gameState->matrizAtual, &gameState->desfazer, &gameState->trocar);
                movimentoDesfeito = 0;
                break;

            case 's':
                gameState->pontuacao += movimentacaoBaixo(gameState->tamanho, gameState->matrizAtual, &gameState->desfazer, &gameState->trocar);
                movimentoDesfeito = 0;
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

        if (confereMovimento(gameState->tamanho, gameState->matrizAtual, matrizAux))
        {
            novoNumeroAleatorio(gameState->tamanho, gameState->matrizAtual);
        }
        else
        {
            printf("Jogada inválida tente novamente: \n");
        }

        if (!ganhou)
        {
            if (verificaGanhou(gameState->tamanho, gameState->matrizAtual))
            {
                ganhou++;
                if (!vitoriaDecisao())
                {
                    voltarMenu = 1;
                }
            }
        }

        if (verificaPerdeu(gameState->tamanho, gameState->matrizAtual))
        {
            imprimeTabuleiro(gameState->tamanho, gameState->matrizAtual, gameState->pontuacao);
            derrotaOk();
            voltarMenu = 1;
        }

        // função saveState
    } while (!voltarMenu);
}

// funções que interagem com o usuário

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

void imprimeTabuleiro(int n, int **matriz, int pontuação) // imprime o tabuleiro do jogo
{
    char espaço = ' ';
    int tamanhoDaCelula = tamanhoCelula(n, matriz);

    printf("PONTUAÇÃO: %d\n", pontuação);
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

void imprimeAjuda() // imprime o texto de ajuda no terminal
{
    int resposta;

    printf("-----------AJUDA-----------\n");
    printf("O 2048 clássico é jogado em um tabuleiro de 4x4, com peças numéricas que deslizam suavemente quando o jogador as move em um dos quatro sentidos disponíveis: para cima, para baixo, à esquerda e à direita, a cada movimento, um novo número (com valor 2 ou 4) aparece aleatoriamente em um espaço vazio no tabuleiro. As peças (blocos) deslizam o mais longe possível na direção escolhida, até que sejam paradas por outra peça ou pela borda do tabuleiro. Se duas peças de mesmo número colidirem durante um movimento, elas se fundirão em uma única peça com o valor somado das duas que colidiram. A peça resultante não pode se fundir com outra peça na mesma jogada.\n");
    printf("-----------REGRAS-----------\n");
    printf("- O jogo começa com duas peças, posicionadas aleatoriamente no tabuleiro. \n- A cada jogada, o jogador deve escolher uma direção: para cima, para baixo, para a esquerda ou para a direita.\n- Após a escolha, todas as peças do tabuleiro deslizarão o máximo possível na direção indicada.\n- Se duas peças de mesmo valor colidirem durante o movimento, elas se combinarão em uma nova peça com a soma de seus valores.\n- Um movimento só é considerado válido se pelo menos uma peça se mover ou se combinar com outra.\n- Ao final de cada jogada válida, uma nova peça é adicionada em uma posição vazia aleatória.\n- Geralmente, essa nova peça será um 2, mas em 10%% das vezes, poderá ser um 4, a chance aumenta a depender do tamanho do tabuleiro 15%% para o 5x5 e 20%% para o 6x6\n- Para vencer, o jogador deve criar uma peça com o número 2048.\n- O jogo termina em derrota se o tabuleiro estiver cheio e não houver mais nenhum movimento válido possível.\n");
    printf("-----------COMANDOS-----------\n");
    printf("- <w, a, s, d>: Movem as peças do tabuleiro para cima, esquerda, para baixo ou para direita, respectivamente.\n- <u>: Desfazer o  ́ultimo movimento.\n- <t pos1, pos2>: Trocar duas peças de posição, ou seja, troca o conteúdo da posição pos1 com o conteúdo da posição pos2.\n");

    do
    {
        scanf("%d", &resposta);
        limpar_buffer();
        if (resposta != 1)
        {
            printf("Resposta inválida! Por favor, digite [1] para voltar: ");
        }
    } while (resposta != 1);
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

int vitoriaDecisao()
{
    int decisao;
    printf("Parabéns você conseguiu chegar a 2048!!\nVocê quer continuar jogando?\nDigite [1] pra continuar jogando e [0] pra voltar ao menu: ");
    scanf("%d", &decisao);
    limpar_buffer();

    do
    {
        if (decisao != 1 && decisao != 0)
        {
            printf("Resposta inválida!! Por favor digite novamente: ");
            scanf("%d", &decisao);
            limpar_buffer();
        }
    } while (decisao != 1 && decisao != 0);

    return decisao;
}

int derrotaOk()
{
    int resposta;
    printf("Que pena!! Infelizmente você perdeu, para voltar ao menu digite [1]: ");
    scanf("%d", &resposta);
    limpar_buffer();

    do
    {
        if (resposta != 1)
        {
            printf("Resposta inválida!! Por favor digite novamente: ");
            scanf("%d", &resposta);
            limpar_buffer();
        }
    } while (resposta != 1);

    return resposta;
}

// movimentação

int movimentacaoEsquerda(int n, int **matriz, int *desfazer, int *trocar) // movimenta as peças no tabuleiro e retorna a pontuação da jogada
{
    int moveu;                       // variavel que mostra quando o movimento não é mais possivel
    int **matrizAux = criaMatriz(n); // criando matriz auxiliar
    int pontuacao = 0;
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
                    if (matriz[i][j] == 128) // verifica se o usuário deve receber um novo movimento de desfazer
                    {
                        (*desfazer)++;
                    }

                    if (matriz[i][j] == 256) // verifica se o usuário deve receber um novo movimento de troca
                    {
                        (*trocar)++;
                    }

                    matriz[i][j - 1] = (matriz[i][j]) * 2;
                    matriz[i][j] = 0;
                    pontuacao += matriz[i][j - 1];

                    matrizAux[i][j - 1] = 1;

                    moveu = 1; // variavel indicando que houve movimento
                }
            }
        }

    } while (moveu); // lógica booleana que repete o código enquanto a condição "moveu" for verdadeira

    liberaMatriz(matrizAux, n); // libera a matriz auxiliar criada
    return pontuacao;
}

int movimentacaoDireita(int n, int **matriz, int *desfazer, int *trocar) // movimenta as peças no tabuleiro e retorna a pontuação da jogada
{
    int moveu;                       // variavel que mostra quando o movimento não é mais possivel
    int **matrizAux = criaMatriz(n); // criando matriz auxiliar
    int pontuacao = 0;

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
                    if (matriz[i][j] == 128) // verifica se o usuário deve receber um novo movimento de desfazer
                    {
                        (*desfazer)++;
                    }

                    if (matriz[i][j] == 256) // verifica se o usuário deve receber um novo movimento de troca
                    {
                        (*trocar)++;
                    }

                    matriz[i][j + 1] = (matriz[i][j]) * 2;
                    matriz[i][j] = 0;
                    pontuacao += matriz[i][j + 1];

                    matrizAux[i][j + 1] = 1;

                    moveu = 1; // variavel indicando que houve movimento
                }
            }
        }

    } while (moveu); // lógica booleana que repete o código enquanto a condição "moveu" for verdadeira

    liberaMatriz(matrizAux, n); // libera a matriz auxiliar criada
    return pontuacao;
}

int movimentacaoCima(int n, int **matriz, int *desfazer, int *trocar) // movimenta as peças no tabuleiro e retorna a pontuação da jogada
{
    int moveu;                       // variavel que mostra quando o movimento não é mais possivel
    int **matrizAux = criaMatriz(n); // criando matriz auxiliar
    int pontuacao = 0;

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
                    if (matriz[i][j] == 128) // verifica se o usuário deve receber um novo movimento de desfazer
                    {
                        (*desfazer)++;
                    }

                    if (matriz[i][j] == 256) // verifica se o usuário deve receber um novo movimento de troca
                    {
                        (*trocar)++;
                    }

                    matriz[i - 1][j] = (matriz[i][j]) * 2;
                    matriz[i][j] = 0;
                    pontuacao += matriz[i - 1][j];

                    matrizAux[i - 1][j] = 1;

                    moveu = 1; // variavel indicando que houve movimento
                }
            }
        }

    } while (moveu); // lógica booleana que repete o código enquanto a condição "moveu" for verdadeira

    liberaMatriz(matrizAux, n); // libera a matriz auxiliar criada
    return pontuacao;
}

int movimentacaoBaixo(int n, int **matriz, int *desfazer, int *trocar) // movimenta as peças no tabuleiro e retorna a pontuação da jogada
{
    int moveu;                       // variavel que mostra quando o movimento não é mais possivel
    int **matrizAux = criaMatriz(n); // criando matriz auxiliar
    int pontuacao = 0;

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
                    if (matriz[i][j] == 128) // verifica se o usuário deve receber um novo movimento de desfazer
                    {
                        (*desfazer)++;
                    }

                    if (matriz[i][j] == 256) // verifica se o usuário deve receber um novo movimento de troca
                    {
                        (*trocar)++;
                    }

                    matriz[i + 1][j] = (matriz[i][j]) * 2;
                    matriz[i][j] = 0;
                    pontuacao += matriz[i + 1][j];

                    matrizAux[i + 1][j] = 1;

                    moveu = 1; // variavel indicando que houve movimento
                }
            }
        }

    } while (moveu); // lógica booleana que repete o código enquanto a condição "moveu" for verdadeira

    liberaMatriz(matrizAux, n); // libera a matriz auxiliar criada
    return pontuacao;
}

// verificações do gameState

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

int verificaPerdeu(int tamanho, int **matriz)
{
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            if (matriz[i][j] == 0)
            {
                return 0; // se houver uma celula vazia ainda existem jogadas válidas
            }
        }
    }

    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            // verifica célula a direita
            if (j < tamanho - 1 && matriz[i][j] == matriz[i][j + 1])
            {
                return 0; // se encontrar jogadas possiveis
            }
            // verifica célula a esquerda
            if (i < tamanho - 1 && matriz[i][j] == matriz[i + 1][j])
            {
                return 0; // se encontrar jogadas possiveis
            }
        }
    }

    return 1; // se não houver jogada possível o usuario perde
}

// geração de matriz

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

// funções de arquivo

void saveState(GameState *gameState) // salvar em arquivo saveState
{
    FILE *arquivo = fopen("saveState.txt", "w");

    fprintf(arquivo, "%d %d %d\n%d %s\n", gameState->tamanho, gameState->desfazer, gameState->trocar, gameState->pontuacao, gameState->nomeUser);

    imprimeMatrizArq(gameState->tamanho, gameState->matrizAtual, arquivo);
    imprimeMatrizArq(gameState->tamanho, gameState->matrizAnterior, arquivo);

    fclose(arquivo);
}

void imprimeMatrizArq(int tamanho, int **matriz, FILE *arquivo)
{
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            fprintf(arquivo, "%d ", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }
}

// funções utilitárias

void limpar_buffer() // limpa o buffer
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void removeN(char *nome)
{
    nome[strcspn(nome, "\n")] = '\0';
}

void toLow(char *letra)
{
    if (*letra >= 'A' && *letra <= 'Z')
    {
        *letra = *letra + 32;
    }
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
