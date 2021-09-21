#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define LINHA 3
#define COLUNA 3

char tabuleiro[LINHA][COLUNA];

void jogar(char matriz[][COLUNA]);
void tela(const char b[][COLUNA], int player);
void iniciaTabuleiro(char tab[][COLUNA]);
int coordenadaEhValida(int x, int y);
int eValido(char letra);
int jogador();


int main() {

	iniciaTabuleiro(tabuleiro);
	jogar(tabuleiro);


	return 0;
}

void jogar(char matriz[][COLUNA]) {
	int play = 1, jogadas = 0, ganhou = 0;
	int x, y, valida;
	do {
		do {

			tela(matriz, play);
			printf("Escolha uma posicao!\n");
			printf("Linha 1,2,3:\n");
			scanf("%d", &x);
			printf("Coluna A,B,C:\n");
			scanf("%d", &y);

			valida = coordenadaEhValida(x, y);
			if (valida == 1) {
				valida += posicaoVazia(x, y);
			}
		} while (valida != 2);
		if (play == 1) {
			matriz[x][y] = 'X';
		}
		else {
			matriz[x][y] = 'O';
		}
		jogadas++;
		play++;
		if (play == 3) {
			play = 1;
		}
	} while (ganhou == 0 && jogadas < 9);
}

int posicaoVazia(int x, int y) {
	if (tabuleiro[x][y] != 'X' && tabuleiro[x][y] != 'O') {
		return 1;
	}
	else {
		return 0;
	}

}

int coordenadaEhValida(int x, int y) {

	if (x >= 0 && x < LINHA) {
		if (y >= 0 && y < 3) {
			return 1;
		}
	}
	return 0;
}

int jogador() {
	
}



int eValido(char letra) {
	if (letra == 'X' || letra == 'O')
		return 1;
	else
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
}