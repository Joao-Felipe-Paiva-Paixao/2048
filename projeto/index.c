#include "2048.h" // Incluindo biblioteca do jogo

int main()
{
    char escolha, confirmacao;
    int ajudaOk;

    do
    {
        imprimeMenu();               // imprime o menu de decisão
        escolha = verificaEntrada(); // lê e valida a entrada de um único caractere do usuário

        switch (escolha)
        {
        case 'r': // o programa deve encerrar
        case 'R':
        {
            do
            {
                printf("Deseja mesmo sair?(Digite [S] ou [N]):");
                confirmacao = verificaEntrada();

                switch (confirmacao)
                {
                case 's':
                case 'S':
                    printf("Encerrando sessão, obrigado por jogar!!\n");
                    return 0;
                    break;

                case 'n':
                case 'N':
                    printf("Voltando ao menu...\n");
                    break;

                default:
                    printf("Resposta inválida!!Tente novamente\n");
                    confirmacao = '`';
                    break;
                }
            } while (confirmacao == '`');
            escolha = '`';
            break;
        }
        case 'n': // cria um novo jogo
        case 'N':
        {
            int tamanho = tamanhoTabuleiro();
            int **matriz = criaMatriz(tamanho);
            int **matrizAux = criaMatriz(tamanho);
            int voltarMenu = 0; // flag usada pra voltar ao menu
            char jogada[20], jogadaChar;

            novoNumeroAleatorio(tamanho, matriz);
            novoNumeroAleatorio(tamanho, matriz);

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
                printf("Jogada: ");

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
            } while (!voltarMenu);

            liberaMatriz(matriz, tamanho);
            liberaMatriz(matrizAux, tamanho);
            break;
        }
        case 'j':
        case 'J':
            printf("Chegou\n");
            break;
        case 'c':
        case 'C':
            printf("Chegou\n");
            break;
        case 's':
        case 'S':
            printf("Chegou\n");
            break;
        case 'm':
        case 'M':
            printf("Chegou\n");
            break;
        case 'a':
        case 'A': // mostra o texto de ajuda
        {
            do
            {
                ajudaOk = imprimeAjuda(ajudaOk);
            } while (ajudaOk != 1);
            limpar_buffer();

            break;
        default:
            if (escolha != '`')
                printf("Resposta inválida!! tente novamente\n\n");
            break;
        }
        }
    } while (escolha != 'r' && escolha != 'R');

    return 0;
}