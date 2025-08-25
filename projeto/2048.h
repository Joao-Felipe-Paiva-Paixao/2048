// João Felipe Paiva Paixão
// 25.1.4014

#ifndef FUNCTIONS_H // Remove a declaração anterior da biblioteca se existir
#define FUNCTIONS_H // Cria declaração da biblioteca

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// structs
typedef struct
{
    int tamanho;
    int pontuacao;
    int desfazer;
    int trocar;
    char nomeUser[27];
    int **matrizAtual;
    int **matrizAnterior; // para a função de desfazer
} GameState;

typedef struct
{
    char nomeUser[27];
    int pontuacao;
} Ranking;

// funções principais de jogo
void novoJogo();                   // corresponde a opção de novo jogo no menu
void emJogo(GameState *gameState); // função de jogo
void continuarJogo();              // continua o último jogo
void carregarJogo();               // carrega jogo salvo
void salvarJogo();                 // salva jogo em um arquivo
void mostraRanking();              // mostra o ranking de pontuações
int sairDoJogo();                  // fecha o programa a depender da confirmação do usuário

// funções que interagem com o usuário
void imprimeMenu();                                                                  // imprime o menu no terminal
void imprimeTabuleiro(int n, int **matriz, int pontuação, int desfazer, int trocar); // imprime o tabuleiro do jogo
void imprimeTabuleiroFinal(int n, int **matriz, int pontuação);                      // imprime o tabuleiro do jogo quando o usuário perde
void imprimeAjuda();                                                                 // imprime o texto de ajuda no terminal
char verificaEntrada();                                                              // lê e valida a entrada de um único caractere do usuário
int tamanhoTabuleiro();                                                              // decide o tamanho do tabuleiro
int vitoriaDecisao();                                                                // usuário decide se continuará no jogo
int derrotaOk(int desfazer);                                                         // usuário responde após derrota
void pedeNomeArq(char nomeArq[30]);                                                  // pede nome do arquivo, pra slavar ou carregar jogo

// movimentação
int movimentacaoEsquerda(int n, int **matriz, int *desfazer, int *trocar); // movimenta as peças no tabuleiro
int movimentacaoDireita(int n, int **matriz, int *desfazer, int *trocar);  // movimenta as peças no tabuleiro
int movimentacaoCima(int n, int **matriz, int *desfazer, int *trocar);     // movimenta as peças no tabuleiro
int movimentacaoBaixo(int n, int **matriz, int *desfazer, int *trocar);    // movimenta as peças no tabuleiro

// verificações do gameState
int confereMovimento(int n, int **matriz, int **matrizAux); // função que confere se houve movimento no tabuleiro do jogo
int verificaGanhou(int tamanho, int **matriz);              // verifica se alguma célula do tabuleiro é 2048
int verificaPerdeu(int tamanho, int **matriz);              // verifica se há movimento válido

// geração de matriz
int **criaMatriz(int n);                       // cria uma matriz com alocação dinamica
void liberaMatriz(int **matriz, int n);        // libera uma matriz criada em alocação dinamica
int **inicializaMatriz(int n, int **matriz);   // inicializa matriz
void novoNumeroAleatorio(int n, int **matriz); // gera um número aleatório em uma célula vazia da matriz
int tamanhoCelula(int n, int **matriz);        // define tamanho da célula

// funções de arquivo
void saveState(GameState *gameState, char nomeArq[30]);          // salvar em arquivo saveState
void imprimeMatrizArq(int tamanho, int **matriz, FILE *arquivo); // imprime matriz de jogo em arquivo
void leMatrizArq(int tamanho, int **matriz, FILE *arquivo);      // lê uma matriz de um arquivo txt
int leArquivo(GameState *gameState, char nomeArq[30]);           // lê info de jogo de um arquivo txt
void escreveRanking(GameState *gameState);                       // escreve ranking em um arquivo dat

// funções utilitárias
void limpar_buffer();     // limpa o buffer
void removeN(char *nome); // remove o \n no fim de uma string
void toLow(char *letra);  // transforma todas as letras de uma string em minusculas

#endif