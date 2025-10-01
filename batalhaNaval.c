#include <stdio.h>

#define TAMANHO 10   // Tabuleiro 10x10
#define TAM_NAVIO 3  // Tamanho fixo dos navios
#define SKILL_SIZE 5 // Tamanho das matrizes de habilidade (5x5)

/*
  Valores no tabuleiro:
   0 = água
   3 = navio
   5 = área de habilidade (quando não há navio)
   8 = navio + área de habilidade (3 + 5) -> para mostrar sobreposição
*/

// Função para inicializar o tabuleiro com zero (água)
void inicializaTabuleiro(int tab[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tab[i][j] = 0;
        }
    }
}

// Função auxiliar para posicionar um navio (orientacao: 0=horizontal,1=vertical,2=diag principal,3=diag secundaria)
// Esta função ignora validações complexas — posiciona apenas quando dentro dos limites e sem sobreposição (simples).
void posicionarNavio(int tab[TAMANHO][TAMANHO], int linha, int coluna, int orientacao) {
    for (int k = 0; k < TAM_NAVIO; k++) {
        int r = linha;
        int c = coluna;
        if (orientacao == 0) { // horizontal -> coluna + k
            c = coluna + k;
        } else if (orientacao == 1) { // vertical -> linha + k
            r = linha + k;
        } else if (orientacao == 2) { // diagonal principal (↘) linha+ k, coluna + k
            r = linha + k;
            c = coluna + k;
        } else if (orientacao == 3) { // diagonal secundária (↙) linha + k, coluna - k
            r = linha + k;
            c = coluna - k;
        }

        // validação simples de limites e não sobrescrever outra posição já ocupada
        if (r >= 0 && r < TAMANHO && c >= 0 && c < TAMANHO) {
            if (tab[r][c] == 0) {
                tab[r][c] = 3;
            } else {
                // se já havia algo (p.ex. outro navio), não sobrescreve — simplificação
            }
        }
    }
}

// Gera a matriz "cone" dinamicamente (SKILL_SIZE x SKILL_SIZE)
// Forma: topo no centro da linha 0, expandindo para baixo (↘ e ↙)
void gerarCone(int cone[SKILL_SIZE][SKILL_SIZE]) {
    int centro = SKILL_SIZE / 2;
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            // condição: na linha i, colunas com |j - centro| <= i são parte do cone
            if ( (j - centro < 0 ? centro - j : j - centro) <= i ) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }
}

// Gera a matriz "cruz" dinamicamente (linha e coluna do centro)
void gerarCruz(int cruz[SKILL_SIZE][SKILL_SIZE]) {
    int centro = SKILL_SIZE / 2;
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            if (i == centro || j == centro) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// Gera a matriz "octaedro" (vista frontal de um octaedro -> losango / diamant)
// condição: distância Manhattan <= centro
void gerarOctaedro(int octa[SKILL_SIZE][SKILL_SIZE]) {
    int centro = SKILL_SIZE / 2;
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            int distManhattan = (i > centro ? i - centro : centro - i) + (j > centro ? j - centro : centro - j);
            if (distManhattan <= centro) {
                octa[i][j] = 1;
            } else {
                octa[i][j] = 0;
            }
        }
    }
}

// Sobrepõe a matriz de habilidade (skillMat) ao tabuleiro centrando em (origemLinha, origemColuna).
// Se skillMat[i][j] == 1 e posição dentro dos limites, marca no tabuleiro:
//  - se água (0) -> vira 5
//  - se navio (3) -> vira 8 (para indicar navio + área)
//  - se já 5 ou 8 -> mantém como está
void sobreporHabilidade(int tab[TAMANHO][TAMANHO], int skillMat[SKILL_SIZE][SKILL_SIZE], int origemLinha, int origemColuna) {
    int centro = SKILL_SIZE / 2;
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            if (skillMat[i][j] == 1) {
                int r = origemLinha - centro + i;
                int c = origemColuna - centro + j;
                // validação de limites do tabuleiro
                if (r >= 0 && r < TAMANHO && c >= 0 && c < TAMANHO) {
                    if (tab[r][c] == 0) {
                        tab[r][c] = 5;
                    } else if (tab[r][c] == 3) {
                        tab[r][c] = 8; // navio + area
                    } else {
                        // se já é 5 ou 8, mantém
                    }
                }
            }
        }
    }
}

// Exibe o tabuleiro no console com legenda
void exibirTabuleiro(int tab[TAMANHO][TAMANHO]) {
    printf("Legenda: 0=agua  3=navio  5=area  8=navio+area\n");
    printf("=== TABULEIRO ===\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // 1) Inicializa tabuleiro
    inicializaTabuleiro(tabuleiro);

    // 2) Posiciona navios (exemplos - sem input; definidas diretamente)
    // Mantendo diversidade: um horizontal, um vertical, dois diagonais (como níveis anteriores)
    posicionarNavio(tabuleiro, 1, 1, 0); // horizontal em (1,1)
    posicionarNavio(tabuleiro, 4, 6, 1); // vertical em (4,6)
    posicionarNavio(tabuleiro, 0, 0, 2); // diagonal principal a partir de (0,0)
    posicionarNavio(tabuleiro, 6, 9, 3); // diagonal secundária a partir de (6,9)

    // 3) Gera dinamicamente as matrizes de habilidade (5x5)
    int cone[SKILL_SIZE][SKILL_SIZE];
    int cruz[SKILL_SIZE][SKILL_SIZE];
    int octaedro[SKILL_SIZE][SKILL_SIZE];

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // 4) Define pontos de origem para cada habilidade no tabuleiro (linha, coluna)
    int origConeLinha = 2, origConeColuna = 4;   // exemplo: cone com origem perto do topo
    int origCruzLinha = 7, origCruzColuna = 3;   // cruz com origem mais embaixo
    int origOctLinha  = 5, origOctColuna  = 8;   // octaedro à direita

    // 5) Sobrepõe habilidades no tabuleiro (com validações de limites feitas na função)
    sobreporHabilidade(tabuleiro, cone, origConeLinha, origConeColuna);
    sobreporHabilidade(tabuleiro, cruz, origCruzLinha, origCruzColuna);
    sobreporHabilidade(tabuleiro, octaedro, origOctLinha, origOctColuna);

    // 6) Exibe resultados
    exibirTabuleiro(tabuleiro);

    // (Opcional) — imprimir as matrizes de habilidade para visualização (debug)
    printf("\nMatriz Cone (1 = área):\n");
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) printf("%d ", cone[i][j]);
        printf("\n");
    }

    printf("\nMatriz Cruz (1 = área):\n");
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) printf("%d ", cruz[i][j]);
        printf("\n");
    }

    printf("\nMatriz Octaedro (1 = área):\n");
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) printf("%d ", octaedro[i][j]);
        printf("\n");
    }

    return 0;
}
