#include <stdio.h>

// defines
#define MAX_ATTEMPTS 10

// procedimentos
void welcome_msg(); // mensagem de instruções e boas vindas

int main () {

	// variaveis
	char word[] = "nuvem"; // vetor de string secreta
	char latter; // conter letra de entrada do usuário

	// mensagem de instução
	welcome_msg();
	// verificado se a entrada for igual à '\n'
	printf("\tDigite enter para continuar!: "); while (getchar() != '\n');



	return 0;
}



// procedimentos

void welcome_msg()
{

	puts("\t__________");
	puts("\t|\t |");
	puts("\t|\t |");
	puts("\t|\t O \tBem-Vindo ao jogo da forca!");
	puts("\t|\t/|\\ \tO jogo consiste em uma palavra de 5 letras,");
	puts("\t|\t/ \\ \tE o jogador tem 10 tentativas! Boa sorte!");
	puts("\t|");
	putchar('\n');
}

