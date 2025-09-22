# Sudoku Validator & Advisor

Implementação em C de um **verificador e conselheiro de Sudoku**.

O programa verifica se um tabuleiro de Sudoku (completo ou parcial) é válido e, quando incompleto, sugere valores possíveis para cada célula vazia.

---

## Estrutura do Projeto

- `main.c` → ponto de entrada do programa.  
- `TAD.c` / `TAD.h` → implementação do Tipo Abstrato de Dados **Tabuleiro**.  
- `sud1.txt … sud4.txt` → quatro arquivos de exemplo de tabuleiros (válido, inválido, incompleto, etc.).  
- `TP1.pdf` → enunciado original do trabalho.  
- `Makefile` → script para compilação.  

Você também pode **criar seus próprios arquivos de tabuleiro**, seguindo o padrão:
- 9×9 inteiros separados por espaço.  
- `0` representa uma célula vazia.  

---

## Compilação e Execução

### Com Makefile
```bash
make          # compila
./exe sud1.txt
make clean    # remove executável e objetos
```

### Manualmente (sem Makefile)
```bash
gcc -c TAD.c -o TAD.o
gcc -c main.c -o main.o
gcc main.o TAD.o -o exe
./exe sud1.txt
```

---

## Exemplos de uso

Rodando o programa com diferentes tabuleiros:
```bash
./exe sud1.txt   # tabuleiro válido
./exe sud2.txt   # tabuleiro completo
./exe sud3.txt   # tabuleiro incompleto com sugestões
./exe sud4.txt   # tabuleiro inválido
```
