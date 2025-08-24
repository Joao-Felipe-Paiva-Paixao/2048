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

// funções principais de jogo
void novoJogo();                   // corresponde a opção de novo jogo no menu
void emJogo(GameState *gameState); // função de jogo

// funções que interagem com o usuário
void imprimeMenu();                                        // imprime o menu no terminal
void imprimeTabuleiro(int n, int **matriz, int pontuação); // imprime o tabuleiro do jogo
void imprimeAjuda();                                       // imprime o texto de ajuda no terminal
char verificaEntrada();                                    // lê e valida a entrada de um único caractere do usuário
int tamanhoTabuleiro();                                    // decide o tamanho do tabuleiro
int vitoriaDecisao();                                      // usuário decide se continuará no jogo
int derrotaOk();                                           // usuário responde após derrota

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
void saveState(GameState *gameState);                            // salvar em arquivo saveState
void imprimeMatrizArq(int tamanho, int **matriz, FILE *arquivo); // imprime matriz de jogo em arquivo

// funções utilitárias
void limpar_buffer();     // limpa o buffer
void removeN(char *nome); // remove o \n no fim de uma string
void toLow(char *letra);

#endif