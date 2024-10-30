#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// defines
#define MAX_ATTEMPTS 10

// procedimentos
void welcome_msg(); // mensagem de instruções e boas vindas
void wordInitialization(char * vstr); // inicializar a palavra (string) no vetor que irá guardar a palavra
void wordMask(char *vstr); // mascarando palavra
// funções
char *secretWord(); // retorna a palavra (string) secreta


int main () {
	// variaveis
	char word[5 + 1]; // declaração de vetor para armazenar a palavra secreta
	wordInitialization(word); // inicializando palavra (word) secreta

	char letter_user;
	int attempts = 0;
	// mensagem de instução
	welcome_msg();
	// verificado se a entrada for igual à '\n'
	printf("\tDigite enter para continuar!: "); while (getchar() != '\n');
	system("cls"); // limpando a tela do system OP

	do {
		wordMask(word);
		putchar('\n'); // pulando uma linha
		printf("Entre com a letra: ");
		letter_user = getchar();
		attempts++;

		while (getchar() != '\n')
	} while(attempts != MAX_ATTEMPTS);
	// mascarando string secreta
	
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


void wordInitialization(char * vstr)
{
	/*
		Inicializando vetor 'word' com palavra chave
	*/

	// declaração de ponteiro para armazenar 
	char * word_secret = secretWord(); // armazenando palavra selecionada aleatoriamente

	int i;
	// percorrendo palavra (string) sorteada
	for (i = 0; *word_secret; i++) {
		// adicionando caractere da string no vetor passado como argumento
		*(vstr + i) = *word_secret;
		word_secret++; // incrementando ponteiro (+1byte) para percorrer string
	}
}

void wordMask(char *vstr)
{
	/*
		Mascarando cada caractere da palavra secreta
	*/
	int i;
	// percorrendo cada caratere da palavra secreta
	for (i = 0; *vstr; i++) {
		// verificando se o caractere aninhado é um espaço
		if (*vstr == ' ') printf(" * ");
		// caso não for imprimir 
		else printf(" | - | ");
		vstr++; // incrementando +1 byte no ponteiro
	}
}


// funções

// palavra (string) secreta
char *secretWord()
{
	/*
		define a palavra secreta a partir (string) de uma lista de palavras (strings) definidas na variavel list 
	*/

	srand(time(NULL)); // basear geração de números aleatorios com base no horário do sistema op

	// ponteiro de vetores do tipo char
	char * list[] = {"Palavra 1", "Palavra 2", "Palavra 3", "Palavra 4", "Palavra 5", "Palavra 6", "Palavra 7", "Palavra 8", "Palavra 9","Palavra 10"};

	int num = rand() % 9; // gerando número aleatório de 0 à 2

	// retornando palavra (string) aleatótia
	return *(list + num);
}