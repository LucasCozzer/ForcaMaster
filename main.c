#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
// defines
#define KICKS 10 // chutes
#define MAXIMUM_ERRORS 6 // máximo de erros
#define SECRET_WORD_SIZE 5 + 1 // largura máxima de palavra secreta

// procedimentos

// limpar tela
void clear_screen();


void welcome_message (); // mensagem de boas vindas

void word_initializer (char * string_secret); // inicializador de palavra secreta

void letter_mask (char * wordSecret); // susbstituindo caracteres das letras por '-'

void unmasking_word (int indice, char * mask, char * str); // substitui indice da mascara pelo caracter encontrado

void initializing_letter_mask (char * mask, char * wordSecret); // inicializando a mascara da string secreta

void show_hud (int errors, int attempts, char * maskString); // mostrando hud do jogo para o usuário

void winner_msg (char * string_secret); // mensagem de ganhador

void loser_msg (char * string_secret); // mensagem de perdedor

void loser_msg_maxAttempts (char * string_secret); // mensagem de perdedor caso passe o limite de tentativas

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
	hits = 0; // iniciando variavel que ira conter os erros
	initializing_letter_mask(maskString, stringSecret); // inicializando a mascara da palavra

	// iniciando lógica do jogo
	do {

		// limpando a tela
		clear_screen();
		// mostrando o hud para o jogador
		show_hud(errors, attempts, maskString);

		// capturando entrada do usuario
		putchar('\n');
		printf("Entre com uma letra: => ");
		inputLetter = getchar();

		// verificação de letra
		int i; // armazena o retorno (indice) da letra correta

		// verificação de retorno da verificação
		if ( (i = existence_check(stringSecret, inputLetter)) != 6) {

			/*
				caso retorno seja diferente do valor maximo + '\0' (6)
			*/

			hits++; // incrementando +1 acerto

			// removendo a mascara da letra certa
			unmasking_word(i, maskString, stringSecret);


			// verificando se o número de acertos é igual ao tamanho da palavra secreta
			if (hits == strlen(stringSecret)) {

				// limpando a tela
				clear_screen();

				// imprimindo mensagem de vitória
				winner_msg(stringSecret);

				return 0;
			}

		} else {

			/*
				caso retorno seja igual ao valor maximo + '\0' (6)
			*/

			errors++; // incrementa +1 erro

			// verificação de quantidade de erros
			if (errors == MAXIMUM_ERRORS) {

				// limpando a tela
				clear_screen();

				// exibindo mensagem de perdedor
				loser_msg(stringSecret);

				return 1;
			}

		}

		attempts++;


		//limpando buffer
		while(getchar() != '\n');

	} while(attempts != KICKS);

	// verificando se passou o máximo de tentativas
	if (attempts >= KICKS) {

		// limpando tela
		clear_screen();

		// exibindo mensagem de perdedor
		loser_msg_maxAttempts(stringSecret);
	}

	return 0;
}





// Funções


int existence_check (char * str, char letter_input) {

	for (int i = 0; *str; i++) {
		if (tolower(*str) == tolower(letter_input)) return i; 
		str++;

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
		"Ceu",
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
 	int len = strlen(wordSecret); // Obtém o comprimento da palavra secreta

    for (int i = 0; i < len; i++) {
        mask[i] = '-'; // Preenche a máscara com '-'
    }
    mask[len] = '\0'; // Finaliza a string corretamente com o caractere nulo

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




void clear_screen() {
    #ifdef _WIN32
        system("cls");  // Comando para Windows
    #else
        system("clear");  // Comando para Linux e MacOS
    #endif
}



void winner_msg (char * string_secret) {
	puts("\t ____________");
	puts("\t |\t   |");
	puts("\t |\t   |");
	puts("\t |\t   O \t PARABÉNSSS! VOCÊ GANHOU O JOGO!");
	printf("\t |\t  /|\\ \t Palavra secreta: %s\n", string_secret);
	puts("\t |\t  / \\ ");
	puts("\t |");
	puts("\t |");
	puts("\t |");
}

void loser_msg (char * string_secret) {
	puts("\t ____________");
	puts("\t |\t   |");
	puts("\t |\t   |");
	puts("\t |\t   O \t QUE PENA...VOCÊ PERDEU O JOGO!");
	printf("\t |\t  /|\\ \t Palavra secreta: %s\n", string_secret);
	puts("\t |\t  / \\ ");
	puts("\t |");
	puts("\t |");
	puts("\t |");
}

void loser_msg_maxAttempts (char * string_secret) {
	puts("\t ____________");
	puts("\t |\t   |");
	puts("\t |\t   |");
	puts("\t |\t   O \t QUE PENA...VOCÊ PERDEU O JOGO!");
	printf("\t |\t  /|\\ \t Palavra secreta: %s\n", string_secret);
	puts("\t |\t  / \\ \t Motivo: Execedeu o limite de tentativas!!");
	puts("\t |");
	puts("\t |");
	puts("\t |");
}