#include <stdio.h>

#define TAMANHO 10   // Tamanho fixo do tabuleiro (10x10)
#define TAM_NAVIO 3  // Tamanho fixo dos navios (3 posições)

// Função auxiliar para posicionar navios
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int orientacao) {
    /*
       Orientação:
       0 = horizontal (esquerda -> direita)
       1 = vertical (cima -> baixo)
       2 = diagonal principal (↘, linha++ / coluna++)
       3 = diagonal secundária (↙, linha++ / coluna--)
    */

    for (int k = 0; k < TAM_NAVIO; k++) {
        int novaLinha = linha;
        int novaColuna = coluna;

        if (orientacao == 0) {            // Horizontal
            novaColuna = coluna + k;
        } else if (orientacao == 1) {     // Vertical
            novaLinha = linha + k;
        } else if (orientacao == 2) {     // Diagonal principal (↘)
            novaLinha = linha + k;
            novaColuna = coluna + k;
        } else if (orientacao == 3) {     // Diagonal secundária (↙)
            novaLinha = linha + k;
            novaColuna = coluna - k;
        }

        // Validação de limites do tabuleiro
        if (novaLinha < TAMANHO && novaLinha >= 0 &&
            novaColuna < TAMANHO && novaColuna >= 0) {
            
            // Validação de sobreposição: só posiciona se não tiver outro navio
            if (tabuleiro[novaLinha][novaColuna] == 0) {
                tabuleiro[novaLinha][novaColuna] = 3;
            }
        }
    }
}

int main() {
    // ---------- Declaração do Tabuleiro ----------
    int tabuleiro[TAMANHO][TAMANHO];

    // ---------- Inicialização do Tabuleiro ----------
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0; // 0 = água
        }
    }

    // ---------- Posicionamento dos Navios ----------
    // Dois navios "clássicos" (horizontal e vertical)
    posicionarNavio(tabuleiro, 2, 1, 0); // Navio horizontal começando na (2,1)
    posicionarNavio(tabuleiro, 5, 4, 1); // Navio vertical começando na (5,4)

    // Dois navios diagonais
    posicionarNavio(tabuleiro, 0, 0, 2); // Navio diagonal principal (↘) a partir de (0,0)
    posicionarNavio(tabuleiro, 3, 9, 3); // Navio diagonal secundária (↙) a partir de (3,9)

    // ---------- Exibição do Tabuleiro ----------
    printf("=== TABULEIRO BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
