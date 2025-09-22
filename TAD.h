#ifndef TAD_H
#define TAD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct t {
    int matriz[9][9];
} Tabuleiro;

typedef struct c {
    int x;
    int y;
    int linha;
    int coluna;
    int quadrante;
} Celula;

void TabuleiroInicializa(char* argv, Tabuleiro *matriz);

void validacao_quadrante (Tabuleiro *matriz, Celula **posicao, int n, int aux2, int *invalido);

bool validacao (Tabuleiro *matriz, Celula **posicao, int tamanho);

void impressaoInvalida (Tabuleiro *matriz, Celula *posicao, int tamanho);

Celula* defineVazias(Tabuleiro *matriz, int tamanho);

int* valoresValidos(Tabuleiro *matriz, Celula posicaoVazia, int *indice);

#endif