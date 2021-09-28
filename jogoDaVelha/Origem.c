#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define LINHA 3
#define COLUNA 3

char jogo[LINHA][COLUNA];
int ganhou = 0;
char cordenadaDigitada[3] = { '\0' };

void clear();
void jogar();
void tela(int player);
void iniciaTabuleiro();
void digito();
int posicaoVazia(int x, int y);
int coordenadaEhValida(int x, int y);
int eValido(char letra);
int isLetra(char c);
int isNumero(char c);
int posY();
int posX();

int ganhouPrincipal();
int ganhouSecundaria();
int ganhouLinha();
int ganhouColuna();


int main() {
	int maisUma = 1;
	do {
		ganhou = 0;
		iniciaTabuleiro();
		jogar();

		printf("\nJogar Novamente 1: \n");
		printf("Sair 2: \n");
		scanf("%d", &maisUma);
		
	} while (maisUma != 2);
	
	return 0;
}

void jogar() {
	int play = 1, jogadas = 0;
	int x, y, valida;
	do {
		int invalida = 0;
		do {
			clear();
			tela(play);
			
			printf("\n      Player %d\n", play);

			if(invalida != 0)
				printf("      Cordenada [%s] ja ocupada tente outra!\n", cordenadaDigitada);
			printf("      Cordenada: ");
			invalida++;

			digito();

			x = posX();
			y = posY();
			
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
	clear();
	tela(play);
}

void clear() {

	DWORD n;  						/* Número de caracteres escritos */
	DWORD size;						/* número de caracteres visíveis */
	COORD coord = { 0, 0 };			/* Posição superior esquerda da tela */
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	/* Obter um identificador para o console */
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(h, &csbi);

	/* Encontre o número de caracteres a serem sobrescritos */
	size = csbi.dwSize.X * csbi.dwSize.Y;

	/* Sobrescrever o buffer de tela com espaços em branco */
	FillConsoleOutputCharacter(h, TEXT(' '), size, coord, &n);
	GetConsoleScreenBufferInfo(h, &csbi);
	FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);

	/* Redefine o cursor para a posição superior esquerda */
	SetConsoleCursorPosition(h, coord);
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

int isLetra(char c)//verifica se a entrada e uma letra a, b ou c
{

	if (c == 'a' || c == 'b' || c == 'c' || c == 'A' || c == 'B' || c == 'C')
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

int isNumero(char c)//verifica se a entrada e um numero 1, 2 ou 3
{

	if (c == '1' || c == '2' || c == '3')
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void digito()
{
	memset(cordenadaDigitada, '\0', 3);

	char c;
	int i = 0;
	char letra;
	int numero = 0;
	int aceitos = 3;

	do
	{
		c = _getch();

		if (isLetra(c) != 0 && i < 1)
		{
			cordenadaDigitada[i] = c;
			i++;
			printf("%c", c);
		}
		else if (isNumero(c) != 0 && i == 1)
		{
			cordenadaDigitada[i] = c;
			i++;
			printf("%c", c);
		}
		else if (c == 8 && i)
		{
			cordenadaDigitada[i] = '\0';
			i--;
			printf("\b \b");
		}

	} while (c != 13);

	cordenadaDigitada[i] = '\0';


}

int posY()
{
	int y = 0;
	switch (cordenadaDigitada[0])
	{
	case 'A':
	case 'a':
		y = 0;
		break;
	case 'B':
	case 'b':
		y = 1;
		break;
	case 'C':
	case 'c':
		y = 2;
		break;
	}

	return y;

}

int posX()
{
	int x = 0;
	switch (cordenadaDigitada[1])
	{
	case '3':
		x = 0;
		break;
	case '2':
		x = 1;
		break;
	case '1':
		x = 2;
		break;
	}

	return x;

}

void tela(const int player) {


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