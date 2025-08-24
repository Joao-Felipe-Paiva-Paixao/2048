#include "2048.h" // incluindo biblioteca do jogo

int main()
{
    char escolha, confirmacao;

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
        case 'j':
        {
            printf("Chegou\n");
            break;
        }
        case 'c':
        {
            printf("Chegou\n");
            break;
        }
        case 's':
        {
            printf("Chegou\n");
            break;
        }
        case 'm':
        {
            printf("Chegou\n");
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