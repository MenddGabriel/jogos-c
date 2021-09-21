#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define LINHA 3
#define COLUNA 3

void tela(const char b[][COLUNA], int player);
void iniciaTabuleiro(char tab[][COLUNA]);

int main() {

	char tabuleiro[LINHA][COLUNA];
	iniciaTabuleiro(tabuleiro);

	tela(tabuleiro, 1);


	return 0;
}

void iniciaTabuleiro(char tab[][COLUNA]) {

	for (int lin = 0; lin < LINHA; lin++) {
		for (int col = 0; col < COLUNA; col++) {
			tab[lin][col] = ' ';
		}
	}
}

void tela(const char b[][COLUNA], const int player) {
	system("cls");
	printf("     ********************\n"
		"     *  Jogo da Velha!  *\n"
		"     ********************\n\n\n");

	printf("      Vez do Player %d!\n\n", player);

	printf("%20s\n", "A   B   C");

	for (int linha = 0; linha < LINHA; linha++) {
		printf("         ");
		printf("%d", linha + 1);
		for (int coluna = 0; coluna < COLUNA; coluna++) {
			if (coluna < COLUNA - 1) {
				printf(" %c |", b[linha][coluna]);
			}
			else {
				printf(" %c ", b[linha][coluna]);
			}

		}
		printf("\n");
		if (linha < LINHA - 1)
			printf("           ---------\n");
	}
	printf("\n Escolha uma posicao: \n");
}