// João Felipe Paiva Paixão
// 25.1.4014

#include "2048.h" // incluindo biblioteca do jogo

int main()
{

    srand(time(NULL)); // semente pra geração de número aleatório
    char escolha, confirmacao;
    GameState *gameState;

    do
    {
        imprimeMenu();               // imprime o menu de decisão
        escolha = verificaEntrada(); // lê e valida a entrada de um único caractere do usuário
        toLow(&escolha);             // transforma a entrada em uma letra minuscula

        switch (escolha)
        {
        case 'r': // o programa deve encerrar
        {
            do
            {
                printf("Deseja mesmo sair?(Digite [S] ou [N]):");
                confirmacao = verificaEntrada();
                toLow(&confirmacao);

                switch (confirmacao)
                {
                case 's':
                    printf("Encerrando sessão, obrigado por jogar!!\n");
                    return 0;

                case 'n':
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
        {
            novoJogo();
            break;
        }
        case 'j': // continua a partir do arquivo saveState.txt
        {
            continuarJogo();
            break;
        }
        case 'c': // carrega jogo salvo
        {
            carregarJogo();
            break;
        }
        case 's': // salvar jogo
        {
            salvarJogo();
            break;
        }
        case 'm': // mostrar ranking
        {
            mostraRanking();
            break;
        }
        case 'a': // mostra o texto de ajuda
        {
            imprimeAjuda();
            break;
        }
        default:
        {
            if (escolha != '`')
                printf("Resposta inválida!! tente novamente\n\n");
            break;
        }
        }
    } while (escolha != 'r');

    return 0;
}