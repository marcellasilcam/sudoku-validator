#include <stdio.h>
#include "TAD.h"

int main(int argc, char** argv){
    if (argc < 2){
        printf ("Uso: %s <arquivo_tabuleiro>\n", argv [0]);
        return 0;
    }

    Tabuleiro *matriz = (Tabuleiro*) malloc(sizeof(Tabuleiro));

    TabuleiroInicializa(argv[1], matriz);

    int n = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (matriz->matriz[i][j] != 0) //descobrindo a quantidade de posicoes preenchidas
                n++;

    Celula *posicaoVazia = defineVazias(matriz, n);
    Celula *posicao = (Celula*) calloc(n, sizeof(Celula));

    for (int i = 0; i < n; i++){
        posicao[i].x = 9;
        posicao[i].y = 9;
        posicao[i].quadrante = 9;
    }

    bool invalido = validacao(matriz, &posicao, n);


    if (invalido == true){
        impressaoInvalida(matriz, posicao, n);
    }
    else {
        if (n == 81)
            printf("Jogo completo. Voce ganhou!\n");
        else {
            int quant = 0;
            printf("Voce esta no caminho certo. Sugestoes:\n");
            do {
                int indice = 0;
                int *corretos = valoresValidos(matriz, posicaoVazia[quant], &indice);
                printf("(%d, %d): ", posicaoVazia[quant].x+1, posicaoVazia[quant].y+1);
                for (int i = 0; i < indice; i++){
                    printf("%d ", corretos[i]);
                }
                printf("\n");
                free(corretos);
                quant++;
            } while (quant != 81-n);
        }
    }


    free(posicaoVazia);
    free(posicao);
    free(matriz);
    return 0;
}