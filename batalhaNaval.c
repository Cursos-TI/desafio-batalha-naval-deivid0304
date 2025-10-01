#include <stdio.h>

#define TAMANHO 10   // Tamanho fixo do tabuleiro 10x10
#define TAM_NAVIO 3  // Tamanho fixo de cada navio

int main() {
    // ---------- Declaração do Tabuleiro ----------
    int tabuleiro[TAMANHO][TAMANHO];

    // ---------- Inicialização do Tabuleiro ----------
    // Todas as posições começam com 0 (água)
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // ---------- Definição das Coordenadas ----------
    // Navio 1: Horizontal (linha 2, coluna inicial 4)
    int navio1_linha = 2;
    int navio1_coluna_inicial = 4;

    // Navio 2: Vertical (linha inicial 5, coluna 7)
    int navio2_linha_inicial = 5;
    int navio2_coluna = 7;

    // ---------- Posicionamento do Navio Horizontal ----------
    for (int k = 0; k < TAM_NAVIO; k++) {
        // Validação: garantir que não ultrapasse o limite do tabuleiro
        if (navio1_coluna_inicial + k < TAMANHO) {
            tabuleiro[navio1_linha][navio1_coluna_inicial + k] = 3;
        }
    }

    // ---------- Posicionamento do Navio Vertical ----------
    for (int k = 0; k < TAM_NAVIO; k++) {
        // Validação: garantir que não ultrapasse o limite do tabuleiro
        // e que não sobreponha o navio horizontal
        if (navio2_linha_inicial + k < TAMANHO &&
            tabuleiro[navio2_linha_inicial + k][navio2_coluna] == 0) {
            tabuleiro[navio2_linha_inicial + k][navio2_coluna] = 3;
        }
    }

    // ---------- Exibição do Tabuleiro ----------
    printf("=== TABULEIRO BATALHA NAVAL ===\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]); // Exibe cada posição
        }
        printf("\n"); // Quebra de linha ao final de cada linha do tabuleiro
    }

    return 0;
}
