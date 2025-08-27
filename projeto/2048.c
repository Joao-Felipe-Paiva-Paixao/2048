// João Felipe Paiva Paixão
// 25.1.4014

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

void continuarJogo() // continua o último jogo
{
    GameState gameState;
    char nomeArq[30];
    strcpy(nomeArq, "saveState.txt");

    if (leArquivo(&gameState, nomeArq))
    {
        if (gameState.tamanho > 0)
        {
            printf("Continuando o jogo de %s...\n", gameState.nomeUser);
            emJogo(&gameState);

            liberaMatriz(gameState.matrizAtual, gameState.tamanho);
            liberaMatriz(gameState.matrizAnterior, gameState.tamanho);
        }
        else
        {
            printf("Erro ao ler arquivo!!\n");
        }
    }
    else // Se a leitura falhou (ficheiro não existe)
    {
        printf("Nenhum jogo em andamento para continuar!\n");
    }
}

void carregarJogo() // carrega jogo salvo
{
    GameState gameState;
    char nomeArq[30];
    pedeNomeArq(nomeArq);

    leArquivo(&gameState, nomeArq);

    if (gameState.tamanho > 0)
    {
        printf("\nContinuando o jogo de %s...\n", gameState.nomeUser);
        emJogo(&gameState);

        liberaMatriz(gameState.matrizAtual, gameState.tamanho);
        liberaMatriz(gameState.matrizAnterior, gameState.tamanho);
    }
    else
    {
        printf("\nErro ao ler arquivo!!\n");
    }
}

void salvarJogo() // salva jogo em um arquivo
{
    GameState gameState;
    char nomeArq[30];

    strcpy(nomeArq, "saveState.txt");

    leArquivo(&gameState, nomeArq);

    pedeNomeArq(nomeArq);
    saveState(&gameState, nomeArq);

    // chamar função salvaRanking
}

void mostraRanking() // mostra o ranking de pontuações
{
    int n4, n5, n6;
    FILE *arquivo = fopen("ranking.dat", "r");

    if (arquivo == NULL)
    {
        printf("\nAinda não há um ranking para mostrar!\n");
        return;
    }

    fscanf(arquivo, "%d %d %d", &n4, &n5, &n6);
    Ranking score;

    if (n4 > 0)
    {
        printf("-------- RANKING 4x4 --------\n");
        for (int i = 0; i < n4; i++)
        {
            fscanf(arquivo, "%s %d", score.nomeUser, &score.pontuacao);
            printf("%2d. %-20s %d\n", i + 1, score.nomeUser, score.pontuacao);
        }
    }
    if (n5 > 0)
    {
        printf("-------- RANKING 5x5 --------\n");
        for (int i = 0; i < n5; i++)
        {
            fscanf(arquivo, "%s %d", score.nomeUser, &score.pontuacao);
            printf("%2d. %-20s %d\n", i + 1, score.nomeUser, score.pontuacao);
        }
    }
    if (n6 > 0)
    {
        printf("-------- RANKING 6x6 --------\n");
        for (int i = 0; i < n6; i++)
        {
            fscanf(arquivo, "%s %d", score.nomeUser, &score.pontuacao);
            printf("%2d. %-20s %d\n", i + 1, score.nomeUser, score.pontuacao);
        }
    }
    fclose(arquivo);
}

int sairDoJogo() // fecha o programa a depender da confirmação do usuário
{
    char confirmacao;
    do
    {
        printf("Deseja mesmo sair?(Digite [S] ou [N]):");
        confirmacao = verificaEntrada();
        toLow(&confirmacao);

        if (confirmacao == 's')
        {
            printf("Encerrando sessão, obrigado por jogar!!\n");
            return 1; // o programa deve encerrar
        }
        else if (confirmacao == 'n')
        {
            printf("Voltando ao menu...\n\n");
            return 0; // o programa não deve encerrar
        }
        else
        {
            printf("Resposta inválida!! Tente novamente\n");
        }
    } while (1); // o loop continua até que 's' ou 'n' seja digitado
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
        imprimeTabuleiro(gameState->tamanho, gameState->matrizAtual, gameState->pontuacao, gameState->desfazer, gameState->trocar);

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
            char nomeArq[30];
            strcpy(nomeArq, "saveState.txt");
            novoNumeroAleatorio(gameState->tamanho, gameState->matrizAtual);
            saveState(gameState, nomeArq);
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
            imprimeTabuleiroFinal(gameState->tamanho, gameState->matrizAtual, gameState->pontuacao);
            if (derrotaOk(gameState->desfazer))
            {
                for (int i = 0; i < gameState->tamanho; i++) // movimento de desfazer
                {
                    for (int j = 0; j < gameState->tamanho; j++)
                    {
                        gameState->matrizAtual[i][j] = gameState->matrizAnterior[i][j];
                    }
                }

                gameState->pontuacao = pontuacaoAnterior;
                gameState->desfazer = desfazerAnterior;
                gameState->trocar = trocarAnterior;

                gameState->desfazer--;
                movimentoDesfeito = 1;
            }
            else
            {
                voltarMenu = 1;
            }
        }
    } while (!voltarMenu);
    escreveRanking(gameState);
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

void imprimeTabuleiro(int n, int **matriz, int pontuação, int desfazer, int trocar) // imprime o tabuleiro do jogo
{
    char espaço = ' ';
    int tamanhoDaCelula = tamanhoCelula(n, matriz);

    printf("PONTUAÇÃO: %d   DESFAZER: %d   TROCAR: %d\n", pontuação, desfazer, trocar);
    printf("   "); // letras
    for (int i = 0; i < n; i++)
    {
        printf(" %*c ", tamanhoDaCelula, 'A' + i);

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

void imprimeTabuleiroFinal(int n, int **matriz, int pontuação) // imprime o tabuleiro do jogo quando o usuário perde
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

    printf("Digite [1] pra voltar ao menu: ");
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

int vitoriaDecisao() // usuário decide se continuará no jogo
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

int derrotaOk(int desfazer) // usuário responde após derrota
{
    int resposta;
    printf("Que pena!! Infelizmente você perdeu!\n");

    if (desfazer > 0) // se o jogador tiver chances de desfazer
    {
        printf("Você tem %d chance(s) de desfazer. Deseja usar uma?\n", desfazer);
        printf("Digite [1] para desfazer ou [0] para voltar ao menu: ");
        do
        {
            scanf("%d", &resposta);
            limpar_buffer();
            if (resposta != 1 && resposta != 0)
            {
                printf("Resposta inválida! Por favor, digite [1] ou [0]: ");
            }
        } while (resposta != 1 && resposta != 0);

        return resposta; // retorna 1 caso o usuário queira desfazer o movimento
    }
    else
    {
        printf("Que pena!! Para voltar ao menu digite [1]: ");
        do
        {
            scanf("%d", &resposta);
            limpar_buffer();
            if (resposta != 1)
            {
                printf("Resposta inválida!! Por favor, digite [1] para voltar: ");
            }
        } while (resposta != 1);

        return 0; // volta pro menu
    }
}

void pedeNomeArq(char nomeArq[30]) // pede nome do arquivo, pra slavar ou carregar jogo
{
    printf("Digite o nome do arquivo desejado (sem a extensão .txt): ");
    fgets(nomeArq, 30, stdin);
    removeN(nomeArq);

    strcat(nomeArq, ".txt");
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

int verificaGanhou(int tamanho, int **matriz) // verifica se alguma célula do tabuleiro é 2048
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

int verificaPerdeu(int tamanho, int **matriz) // verifica se há movimento válido
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

void saveState(GameState *gameState, char nomeArq[30]) // salvar em arquivo saveState
{
    FILE *arquivo = fopen(nomeArq, "w");

    fprintf(arquivo, "%d %d %d\n%d %s\n", gameState->tamanho, gameState->desfazer, gameState->trocar, gameState->pontuacao, gameState->nomeUser);

    imprimeMatrizArq(gameState->tamanho, gameState->matrizAtual, arquivo);
    imprimeMatrizArq(gameState->tamanho, gameState->matrizAnterior, arquivo);

    fclose(arquivo);
}

void imprimeMatrizArq(int tamanho, int **matriz, FILE *arquivo) // imprime matriz de jogo em arquivo
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

void leMatrizArq(int tamanho, int **matriz, FILE *arquivo) // lê uma matriz de um arquivo txt
{
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            fscanf(arquivo, "%d ", &matriz[i][j]);
        }
        fscanf(arquivo, "\n");
    }
}

int leArquivo(GameState *gameState, char nomeArq[30]) // lê info de jogo de um arquivo txt
{
    FILE *arquivo = fopen(nomeArq, "r");

    if (arquivo == NULL)
    {
        return 0; // se o arquivo não existir
    }

    fscanf(arquivo, "%d %d %d %d", &gameState->tamanho, &gameState->desfazer, &gameState->trocar, &gameState->pontuacao);
    fscanf(arquivo, "%s", gameState->nomeUser);

    gameState->matrizAtual = criaMatriz(gameState->tamanho);
    gameState->matrizAnterior = criaMatriz(gameState->tamanho);

    leMatrizArq(gameState->tamanho, gameState->matrizAtual, arquivo);
    leMatrizArq(gameState->tamanho, gameState->matrizAnterior, arquivo);

    fclose(arquivo);
    return 1; // se a leitura for bem sucedida
}

void escreveRanking(GameState *gameState) // escreve ranking em um arquivo dat
{
    Ranking rank4[11], rank5[11], rank6[11];
    int n4 = 0, n5 = 0, n6 = 0;
    FILE *arquivo = fopen("ranking.dat", "r");

    if (arquivo != NULL)
    {
        fscanf(arquivo, "%d %d %d", &n4, &n5, &n6);
        for (int i = 0; i < n4; i++)
            fscanf(arquivo, "%s %d", rank4[i].nomeUser, &rank4[i].pontuacao);
        for (int i = 0; i < n5; i++)
            fscanf(arquivo, "%s %d", rank5[i].nomeUser, &rank5[i].pontuacao);
        for (int i = 0; i < n6; i++)
            fscanf(arquivo, "%s %d", rank6[i].nomeUser, &rank6[i].pontuacao);
        fclose(arquivo);
    }

    Ranking jogoAtual;

    strcpy(jogoAtual.nomeUser, gameState->nomeUser);
    jogoAtual.pontuacao = gameState->pontuacao;

    if (gameState->tamanho == 4 && n4 < 11)
    {
        rank4[n4++] = jogoAtual;
    }
    else if (gameState->tamanho == 5 && n5 < 11)
    {
        rank5[n5++] = jogoAtual;
    }
    else if (gameState->tamanho == 6 && n6 < 11)
    {
        rank6[n6++] = jogoAtual;
    }

    Ranking *total = NULL;      // inicializa a struct com valor nulo
    int *tamanhoRanking = NULL; // guarda o tamanho de cada lista de ranking

    if (gameState->tamanho == 4)
    {
        total = rank4;
        tamanhoRanking = &n4;
    }
    else if (gameState->tamanho == 5)
    {
        total = rank5;
        tamanhoRanking = &n5;
    }
    else if (gameState->tamanho == 6)
    {
        total = rank6;
        tamanhoRanking = &n6;
    }

    if (total != NULL)
    {
        for (int i = 0; i < *tamanhoRanking - 1; i++)
        {
            for (int j = 0; j < *tamanhoRanking - i - 1; j++)
            {
                if (total[j].pontuacao < total[j + 1].pontuacao)
                {
                    Ranking aux = total[j];
                    total[j] = total[j + 1];
                    total[j + 1] = aux;
                }
            }
        }
    }

    arquivo = fopen("ranking.dat", "w");
    if (arquivo == NULL)
        return;

    fprintf(arquivo, "%d %d %d\n", n4 > 10 ? 10 : n4, n5 > 10 ? 10 : n5, n6 > 10 ? 10 : n6);
    for (int i = 0; i < n4 && i < 10; i++)
        fprintf(arquivo, "%s %d\n", rank4[i].nomeUser, rank4[i].pontuacao);
    for (int i = 0; i < n5 && i < 10; i++)
        fprintf(arquivo, "%s %d\n", rank5[i].nomeUser, rank5[i].pontuacao);
    for (int i = 0; i < n6 && i < 10; i++)
        fprintf(arquivo, "%s %d\n", rank6[i].nomeUser, rank6[i].pontuacao);

    fclose(arquivo);
}

// funções utilitárias

void limpar_buffer() // limpa o buffer
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void removeN(char *nome) // remove o \n no fim de uma string
{
    nome[strcspn(nome, "\n")] = '\0';
}

void toLow(char *letra) // transforma todas as letras de uma string em minusculas
{
    if (*letra >= 'A' && *letra <= 'Z')
    {
        *letra = *letra + 32;
    }
}
