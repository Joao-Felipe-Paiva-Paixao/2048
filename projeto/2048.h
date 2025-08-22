#ifndef FUNCTIONS_H // Remove a declaração anterior da biblioteca se existir
#define FUNCTIONS_H // Cria declaração da biblioteca

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void imprimeMenu();                                         // imprime o menu no terminal
void limpar_buffer();                                       // limpa o buffer
int imprimeAjuda(int ajudaOk);                              // imprime o texto de ajuda no terminal
void imprimeTabuleiro(int n, int **matriz);                 // imprime o tabuleiro do jogo
int tamanhoTabuleiro();                                     // decide o tamanho do tabuleiro
int **criaMatriz(int n);                                    // cria uma matriz com alocação dinamica
void liberaMatriz(int **matriz, int n);                     // libera uma matriz criada em alocação dinamica
int tamanhoCelula(int n, int **matriz);                     // define tamanho da célula
int **inicializaMatriz(int n, int **matriz);                // inicializa matriz
void novoNumeroAleatorio(int n, int **matriz);              // gera um número aleatório em uma célula vazia da matriz
int confereMovimento(int n, int **matriz, int **matrizAux); // função que confere se houve movimento no tabuleiro do jogo
void movimentacaoEsquerda(int n, int **matriz);             // movimenta as peças no tabuleiro
void movimentacaoDireita(int n, int **matriz);              // movimenta as peças no tabuleiro
void movimentacaoCima(int n, int **matriz);                 // movimenta as peças no tabuleiro
void movimentacaoBaixo(int n, int **matriz);                // movimenta as peças no tabuleiro
char verificaEntrada();                                     // lê e valida a entrada de um único caractere do usuário
int verificaGanhou(int tamanho, int **matriz);              // verifica se alguma célula do tabuleiro é 2048
int vitoriaDecisao();
void emJogo(int tamanho, int **matriz, int **matrizAux);    // função de jogo
void novoJogo();                                            // corresponde a opção de novo jogo no menu

#endif