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
            novoJogo();
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