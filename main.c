#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
// defines
#define KICKS 10 // chutes
#define MAXIMUM_ERRORS 6; // máximo de erros
#define SECRET_WORD_SIZE 5 + 1 // largura máxima de palavra secreta

// procedimentos


void welcome_message (); // mensagem de boas vindas

void word_initializer (char * string_secret); // inicializador de palavra secreta

void letter_mask (char * wordSecret); // susbstituindo caracteres das letras por '-'

void unmasking_word (int indice, char * mask, char * str); // substitui indice da mascara pelo caracter encontrado

void initializing_letter_mask (char * mask, char * wordSecret); // inicializando a mascara da string secreta

void show_hud (); // mostrando hud do jogo para o usuário



// funções

char * word_secret (); // retorna a string secreta

int existence_check (char * str, char letter_input); // verifica se a letra existe dentro da string


int main () {

	// variaveis do jogo

	char stringSecret[SECRET_WORD_SIZE]; // vetor armazém de palavra secreta
	char maskString[SECRET_WORD_SIZE]; // vetor de mascara de palavra secreta
	int attempts, errors, hits; // contabilizar quantidade de tentativas e quantos erros aconteceramm durante o jogo
	char inputLetter; // conter a letra de entrada do usuário

	// exibindo mensagem de boas vindas e regras do jogo

	welcome_message();
	putchar('\n');
	printf("\tPor favor, pressione a tecla ENTER e inicie o jogo: "); while (getchar() != '\n'); // esperando o caracter '\n' [NewLine]



	// inicializando todos os dados do jogo

	word_initializer(stringSecret); // inicializando a palavra secreta do jogo
	attempts = 0; // iniciando variavel que ira conter as tentativas
	errors = 0; // iniciando variavel que ira conter os erros
	initializing_letter_mask(maskString, stringSecret); // inicializando a mascara da palavra

	// iniciando lógica do jogo

	do {
		system("clear");
		printf("\n\n %s \n\n", stringSecret);
		show_hud(errors, attempts, maskString);
		putchar('\n');

		printf("Por favor, entre com uma letra: ");
		inputLetter = getchar();

		int i = existence_check(stringSecret, inputLetter);
		if (i != 6) {
			if (hits == strlen(stringSecret)) {
				printf("FIM! Venceu\n");
				return 0;
			}

			hits++;
			unmasking_word(i, maskString, stringSecret);
		} else {

			if (errors == 6) {
				printf("FIM! Perdeu\n");
				break;
			}

			errors++;
		}

		

		while(getchar() != '\n');

	} while(attempts != KICKS);


	return 0;
}





// Funções


int existence_check (char * str, char letter_input) {

	for (int i = 0; *str; i++) {
		if (*str == letter_input) return i; 
		*str++;

	}

	return 6;
}





char * word_secret () {

	/*
		Criador de palavra secreta, selecionando palavra secreta aleatoriamente
	*/

	char * SecretWordList[] = {
		"Amor",
		"Casa",
		"Paz",
		"Flor",
		"Céu",
		"Mar",
		"Luz",
		"Vida",
		"Bem",
		"Livro"
	};

	srand(time(NULL)); // baseando a randomização com o time do sys op

	return *(SecretWordList + (rand() % SECRET_WORD_SIZE) );

}








// procedimentos

void welcome_message () {
	

	/*
		Exibindo a mensagem inicial do jogo
	*/


	puts("\t ____________");
	puts("\t |\t   |");
	puts("\t |\t   |");
	puts("\t |\t   O \t Bem Vindo ao Jogo da Forca!");
	puts("\t |\t  /|\\ \t As regras do jogo são: ");
	puts("\t |\t  / \\ \t Número de Tentativas: 10\t|\tTamnho da Palavra 5 letras!");
	puts("\t | \t \t Acerte com o mínimo de tentativas a palavra secreta!");
	puts("\t | \t \t Boa Sorte!");
	puts("\t |");
}




void word_initializer (char * string_secret) {

	/*
		Inicializando a palavra secreta
	*/

	strncpy(string_secret, word_secret(), SECRET_WORD_SIZE);
}




void initializing_letter_mask (char * mask, char * wordSecret) {

	/*
		Inicializando a mascara da plavara secreta
	*/


	// percorrendo palavra secreta
	for (int i = 0; *wordSecret; i++) {
		*(mask + i) = '-'; // atribuindo o caratere '-' em cada indice do vetor mask
		*(wordSecret++); // +1 byte
	}

}






void show_hud (int errors, int attempts, char * maskString) {


	puts("\t ____________");
	puts("\t |\t   |");
	puts("\t |\t   |");
	printf("\t |\t   %c \t Número de tentativas restantes: %d\n", errors >= 1 ? 'O' : ' ', KICKS - attempts);
	printf("\t |\t  %c%c%c \t Palavra secreta: %s\n", errors >= 3 ? '/' : ' ', errors >= 2 ? '|': ' ', errors >= 4 ? '\\' : ' ', maskString);
	printf("\t |\t  %c %c \n", errors >= 5 ? '/' : ' ', errors >= 6 ? '\\': ' ');
	puts("\t |");
	puts("\t |");
	puts("\t |");

}




void unmasking_word (int indice, char * mask, char * str) {

	*(mask + indice) = *(str + indice);

}