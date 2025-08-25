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
            if (sairDoJogo())
                remove("saveState.txt"); // apaga o arquivo saveState.txt
            return 0;
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
    } while (1);

    return 0;
}