#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define LINHA 3
#define COLUNA 3

char jogo[LINHA][COLUNA];
int ganhou = 0;

void jogar();
void tela(int player);
void iniciaTabuleiro();
int coordenadaEhValida(int x, int y);
int eValido(char letra);

int ganhouPrincipal();
int ganhouSecundaria();
int ganhouLinha();
int ganhouColuna();


int main() {

	iniciaTabuleiro();
	jogar();


	return 0;
}

void jogar() {
	int play = 1, jogadas = 0;
	int x, y, valida;
	do {
		do {

			tela(play);
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
			jogo[x][y] = 'X';
		}
		else {
			jogo[x][y] = 'O';
		}
		jogadas++;
		play++;
		if (play == 3) {
			play = 1;
		}

		ganhou += ganhouLinha();
		ganhou += ganhouColuna();
		ganhou += ganhouPrincipal();
		ganhou += ganhouSecundaria();



	} while (ganhou == 0 && jogadas < 9);

	if (jogadas == 9)
		play = 0; //Deu Velha
	else if (play == 2)
		play = 1;
	else
		play = 2;
	tela(play);
}

int ganhouColuna() {
	int i, j, igual = 1;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			if (eValido(jogo[i][j]) && jogo[i][j] == jogo[i + 1][j]) {
				igual++;
			}
		}
		if (igual == 3)
			return 1;
		igual = 1;
	}
	return 0;
}

int ganhouLinha() {
	int i, j, igual = 1;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			if (eValido(jogo[i][j]) && jogo[i][j] == jogo[i][j + 1]) {
				igual++;
			}
		}
		if (igual == 3)
			return 1;
		igual = 1;
	}
	return 0;
}

int ganhouPrincipal() {
	int igual = 1;
	for (int i = 0; i < 2; i++) {
		if (eValido(jogo[i][i]) && jogo[i][i] == jogo[i + 1][i + 1]) {
			igual++;
		}
	}
	if (igual == 3)
		return 1;
	else
		return 0;

}

int ganhouSecundaria() {
	int igual = 1;
	for (int i = 0; i < 2; i++) {
		if (eValido(jogo[i][2 - i]) && jogo[i][2 - i] == jogo[i + 1][2 - i - 1]) {
			igual++;
		}

	}
	if (igual == 3)
		return 1;
	else
		return 0;

}

int posicaoVazia(int x, int y) {
	if (jogo[x][y] != 'X' && jogo[x][y] != 'O') {
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

int eValido(char letra) {
	if (letra == 'X' || letra == 'O')
		return 1;
	else
		return 0;
}

void iniciaTabuleiro() {

	for (int lin = 0; lin < LINHA; lin++) {
		for (int col = 0; col < COLUNA; col++) {
			jogo[lin][col] = ' ';
		}
	}
}

void tela(const int player) {
	system("cls");
	printf("     ********************\n"
		"     *  Jogo da Velha!  *\n"
		"     ********************\n\n\n");
	if (ganhou != 0) {
		if (player == 0)
			printf("      Eh essa deu velha :(\n");
		else
			printf("      O Player %d ganhou essa!\n\n", player);
	}
	else
		printf("      Vez do Player %d!\n\n", player);


	int lin = 3;
	for (int linha = 0; linha < LINHA; linha++) {
		printf("         ");
		printf("%d", lin);
		for (int coluna = 0; coluna < COLUNA; coluna++) {
			if (coluna < COLUNA - 1) {
				printf(" %c |", jogo[linha][coluna]);
			}
			else {
				printf(" %c ", jogo[linha][coluna]);
			}

		}
		printf("\n");
		if (linha < LINHA - 1)
			printf("           ---------\n");
		lin--;
	}
	printf("%20s\n", "A   B   C");
}