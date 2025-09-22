#include "TAD.h"

void TabuleiroInicializa(char* argv, Tabuleiro *matriz) {
    FILE *arquivo = fopen(argv, "r");
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            fscanf(arquivo, "%d", &matriz->matriz[i][j]);
        }
    }
    fclose(arquivo);
}

void validacao_quadrante (Tabuleiro *matriz, Celula **posicao, int n, int aux2, int *invalido){
    int aux = 0; 
    if (aux2 < 9){
        for (int j = 0; j < 9; j+=3){
            for (int i = aux2; i < aux2+3; i++){
                for (int j2 = j; j2 < aux+3; j2++){
                    for (int i2 = aux2; i2 < aux2+3; i2++){
                        if (matriz->matriz[i][j] != 0){
                            if (matriz->matriz[i][j] == matriz->matriz[i2][j2]){
                                if (i == i2 && j == j2)
                                    break;
                                else {
                                    if ( i < 3 && j < 3){
                                        (*posicao)[n].quadrante = 0;
                                        (*posicao)[n+1].quadrante = 0;
                                    }
                                    else if ( i < 6 && j < 3){
                                        (*posicao)[n].quadrante = 3;
                                        (*posicao)[n+1].quadrante = 3;
                                    }
                                    else if ( i < 9 && j < 3){
                                        (*posicao)[n].quadrante = 6;
                                        (*posicao)[n+1].quadrante = 6;
                                    }
                                    else if ( i < 3 && j < 6){
                                        (*posicao)[n].quadrante = 1;
                                        (*posicao)[n+1].quadrante = 1;
                                    }
                                    else if ( i < 6 && j < 6){
                                        (*posicao)[n].quadrante = 4;
                                        (*posicao)[n+1].quadrante = 4;
                                    }
                                    else if ( i < 9 && j < 6){
                                        (*posicao)[n].quadrante = 7;
                                        (*posicao)[n+1].quadrante = 7;
                                    }
                                    else if ( i < 3 && j < 9){
                                        (*posicao)[n].quadrante = 2;
                                        (*posicao)[n+1].quadrante = 2;
                                    }
                                    else if ( i < 6 && j < 9){
                                        (*posicao)[n].quadrante = 5;
                                        (*posicao)[n+1].quadrante = 5;
                                    }
                                    else if ( i < 9 && j < 9){
                                        (*posicao)[n].quadrante = 8;
                                        (*posicao)[n+1].quadrante = 8;
                                    }
                                    (*posicao)[n].x = i;
                                    (*posicao)[n].y = j;
                                    n++;
                                    (*posicao)[n].x = i2;
                                    (*posicao)[n].y = j2;
                                    n++;
                                    *invalido = 1;
                                }
                            }
                            
                        }
                        else 
                            break;
                    }
                }
            }
            aux += 3;
        }
        validacao_quadrante (matriz, posicao, n, aux2+3, invalido); //olha q chique prof eu usando recursividade rsrs
    }
}

bool validacao (Tabuleiro *matriz, Celula **posicao, int tamanho){
    int n = 0; int invalido = 0;
    for (int k = 0; k < 9; k++){ //coluna
        for (int i = 0; i < 9; i++){
            if (matriz->matriz[i][k] != 0){
                for (int j = i+1; j < 9; j++){
                    if (matriz->matriz[i][k] == matriz->matriz[j][k]){
                        (*posicao)[n].x = i;
                        (*posicao)[n].y = k;
                        (*posicao)[n].coluna = 1;
                        n++;
                        (*posicao)[n].x = j;
                        (*posicao)[n].y = k;
                        (*posicao)[n].coluna = 1;
                        n++;
                        invalido = 1;
                    }
                }
            }
            else 
                continue;
        }
    }

    for (int k = 0; k < 9; k++){ //linha
        for (int i = 0; i < 9; i++){
            if (matriz->matriz[k][i] != 0){
                for (int j = i+1; j < 9; j++){
                    if (matriz->matriz[k][i] == matriz->matriz[k][j]){
                        (*posicao)[n].x = k;
                        (*posicao)[n].y = i;
                        (*posicao)[n].linha = 1;
                        n++;
                        (*posicao)[n].x = k;
                        (*posicao)[n].y = j;
                        (*posicao)[n].linha = 1;
                        n++;
                        invalido = 1;
                    }
                }
            }
            else 
                continue;
        }
    }

    int aux = 0;
    validacao_quadrante(matriz, posicao, n, aux, &invalido);

    
    if (invalido == 1)
        return true;
    else 
        return false;
}

void impressaoInvalida (Tabuleiro *matriz, Celula *posicao, int tamanho){
    int jaFoi = 9;
    printf("Alguma coisa deu errado... Invalidos:\n");
    for (int i = 0; i < 9; i++){ //linha
        for (int j = 0; j < tamanho; j++){
            if (posicao[j].x == i && posicao[j].linha == 1){
                if (jaFoi != i){
                    jaFoi = i;
                    printf("Linha %d: ", i+1);
                    int flag = 0;
                    for (int j = 0; j < tamanho; j++){
                        if (posicao[j].x == i && posicao[j].linha == 1){
                            if (flag == 0){
                                printf("(%d, %d) ", posicao[j].x+1, posicao[j].y+1);
                                flag = 1;
                            }
                            else 
                                printf("e (%d, %d) ", posicao[j].x+1, posicao[j].y+1);
                        }
                    }
                    printf("\n");
                }
            }
        }
    }

    jaFoi = 9;
    for (int i = 0; i < 9; i++){ //coluna
        for (int j = 0; j < tamanho; j++){
            if (posicao[j].y == i && posicao[j].coluna == 1){
                if (jaFoi != i){
                    jaFoi = i;
                    printf("Coluna %d: ", i+1);
                    int flag = 0;
                    for (int j = 0; j < tamanho; j++){
                        if (posicao[j].y == i && posicao[j].coluna == 1){
                            if (flag == 0){
                                printf("(%d, %d) ", posicao[j].x+1, posicao[j].y+1);
                                flag = 1;
                            }
                            else
                                printf("e (%d, %d) ", posicao[j].x+1, posicao[j].y+1);
                        }
                    }
                    printf("\n");
                }
            }
        }
    }

    for (int i = 0; i < tamanho; i++){ //regiao
        if (posicao[i].quadrante != 9){
            if (posicao[i].quadrante == posicao[i+1].quadrante){
                continue;
            }
            else {
                printf("Regiao %d: ", posicao[i].quadrante+1);
                int flag = 0;
                for (int j = 0; j < tamanho; j++){
                    if (posicao[j].quadrante == posicao[i].quadrante){
                        if (flag == 0){
                            printf("(%d, %d) ", posicao[j].x+1, posicao[j].y+1);
                            flag = 1;
                        }
                        else 
                            printf("e (%d, %d) ", posicao[j].x+1, posicao[j].y+1);

                    }
                }
                printf("\n");
            }
        }
    }

}

Celula* defineVazias(Tabuleiro *matriz, int tamanho){
    Celula *posicaoVazia;
    if (tamanho != 81){
        posicaoVazia = (Celula*) calloc(81-tamanho, sizeof(Celula));
        int n = 0;
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                if (matriz->matriz[i][j] == 0){
                    if ( i < 3 && j < 3){
                        posicaoVazia[n].quadrante = 0;
                    }
                    else if ( i < 6 && j < 3){
                        posicaoVazia[n].quadrante = 3;
                    }
                    else if ( i < 9 && j < 3){
                        posicaoVazia[n].quadrante = 6;
                    }
                    else if ( i < 3 && j < 6){
                        posicaoVazia[n].quadrante = 1;
                    }
                    else if ( i < 6 && j < 6){
                        posicaoVazia[n].quadrante = 4;
                    }
                    else if ( i < 9 && j < 6){
                        posicaoVazia[n].quadrante = 7;
                    }
                    else if ( i < 3 && j < 9){
                        posicaoVazia[n].quadrante = 2;
                    }
                    else if ( i < 6 && j < 9){
                        posicaoVazia[n].quadrante = 5;
                    }
                    else {
                        posicaoVazia[n].quadrante = 8;
                    }
                    posicaoVazia[n].x = i;
                    posicaoVazia[n].y = j;
                    n++;
                }
            }
        }
    }
    else {
        posicaoVazia = (Celula*) calloc(1, sizeof(Celula));
    }
    return posicaoVazia;
}

int* valoresValidos(Tabuleiro *matriz, Celula posicaoVazia, int *indice){
    int validos[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 9; i++){ //checando valores por coluna
        int j = posicaoVazia.y;
        for (int k = 0; k < 9; k++){
            if (matriz->matriz[i][j] == validos[k]){
                validos[k] = 0;
            }

        }
    }

    for (int j = 0; j < 9; j++){ //checando valores por linha
        int i = posicaoVazia.x;
        for (int k = 0; k < 9; k++){
            if (matriz->matriz[i][j] == validos[k]){
                validos[k] = 0;
            }
        }
    }

    /* checando valores por quadrante */
    if (posicaoVazia.quadrante == 0){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                for (int k = 0; k < 9; k++)
                    if (matriz->matriz[i][j] == validos[k]){
                        validos[k] = 0;
                    }
            }
        }
    }
    else if (posicaoVazia.quadrante == 3){
        for (int i = 3; i < 6; i++){
            for (int j = 0; j < 3; j++){
                for (int k = 0; k < 9; k++)
                    if (matriz->matriz[i][j] == validos[k]){
                        validos[k] = 0;
                    }
            }
        }
    }
    else if (posicaoVazia.quadrante == 6){
        for (int i = 6; i < 9; i++){
            for (int j = 0; j < 3; j++){
                for (int k = 0; k < 9; k++)
                    if (matriz->matriz[i][j] == validos[k]){
                        validos[k] = 0;
                    }
            }
        }
    }
    else if (posicaoVazia.quadrante == 1){
        for (int i = 0; i < 3; i++){
            for (int j = 3; j < 6; j++){
                for (int k = 0; k < 9; k++)
                    if (matriz->matriz[i][j] == validos[k]){
                        validos[k] = 0;
                    }
            }
        }
    }
    else if (posicaoVazia.quadrante == 4){
        for (int i = 3; i < 6; i++){
            for (int j = 3; j < 6; j++){
                for (int k = 0; k < 9; k++)
                    if (matriz->matriz[i][j] == validos[k]){
                        validos[k] = 0;
                    }
            }
        }
    }
    else if (posicaoVazia.quadrante == 7){
        for (int i = 6; i < 9; i++){
            for (int j = 3; j < 6; j++){
               for (int k = 0; k < 9; k++)
                    if (matriz->matriz[i][j] == validos[k]){
                        validos[k] = 0;
                    }
            }
        }
    }
    else if (posicaoVazia.quadrante == 2){
        for (int i = 0; i < 3; i++){
            for (int j = 6; j < 9; j++){
                for (int k = 0; k < 9; k++)
                    if (matriz->matriz[i][j] == validos[k]){
                        validos[k] = 0;
                    }
            }
        }
    }
    else if (posicaoVazia.quadrante == 5){
        for (int i = 3; i < 6; i++){
            for (int j = 6; j < 9; j++){
                for (int k = 0; k < 9; k++)
                    if (matriz->matriz[i][j] == validos[k]){
                        validos[k] = 0;
                    }
            }
        }
    }
    else if (posicaoVazia.quadrante == 8){
        for (int i = 6; i < 9; i++){
            for (int j = 6; j < 9; j++){
                for (int k = 0; k < 9; k++)
                    if (matriz->matriz[i][j] == validos[k]){
                        validos[k] = 0;
                    }
            }
        }
    }

    for (int k = 0; k < 9; k++)
        if (validos[k] != 0)
            *indice += 1;

    int *corretos = (int*) malloc(*indice * sizeof(int));
    int n = 0;

    for (int k = 0; k < 9; k++){
        if (validos[k] != 0){
            corretos[n] = validos[k];
            n++;
        }
    }

    return corretos;
}