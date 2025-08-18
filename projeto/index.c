#include "2048.h" // Incluindo biblioteca do jogo

int main()
{
    char escolha, confirmacao;
    int ajudaOk;

    do
    {
        imprimeMenu();         // imprime o menu de decisão
        scanf("%c", &escolha); // recebe decisão do usuário
        limpar_buffer();

        switch (escolha)
        {
        case 'r': // o programa deve encerrar
        case 'R':
        {
            printf("Deseja mesmo sair?(Digite [S] ou [N]):");
            scanf("%c", &confirmacao);
            limpar_buffer();
            if (confirmacao == 'S' || confirmacao == 's')
                return 0;
            else
                escolha = '`';

            break;
        }
        case 'n': // cria um novo jogo
        case 'N':
        {
            int tamanho = tamanhoTabuleiro();
            int **matriz = criaMatriz(tamanho);
            char jogada;

            novoNumeroAleatorio(tamanho, matriz);
            novoNumeroAleatorio(tamanho, matriz);
            do
            {
                imprimeTabuleiro(tamanho, matriz);
                printf("Jogada: ");
                do
                {
                    scanf("%c", &jogada);
                    limpar_buffer();

                    switch (jogada)
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
                        jogada = '`';
                    }
                } while (jogada == '`');

                novoNumeroAleatorio(tamanho, matriz);

                if (jogada == 'u')
                    break;
            } while (1 < 2);

            liberaMatriz(matriz, tamanho);
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