#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

// defines
#define KICKS 10  // número máximo de tentativas
#define MAXIMUM_ERRORS 6  // máximo de erros permitidos
#define SECRET_WORD_SIZE 6  // largura máxima de palavra secreta +1 para '\0'

// procedimentos
void clear_screen();
void welcome_message(); // mensagem de boas-vindas
void word_initializer(char *string_secret); // inicializa a palavra secreta
void letter_mask(char *wordSecret); // substitui caracteres das letras por '-'
void unmasking_word(int index, char *mask, char *str); // desmascara a letra correta
void initializing_letter_mask(char *mask, char *wordSecret); // inicializa a máscara
void show_hud(int errors, int attempts, char *maskString); // mostra o HUD do jogo
void winner_msg(char *string_secret); // mensagem de vitória
void loser_msg(char *string_secret); // mensagem de derrota
void loser_msg_maxAttempts(char *string_secret); // mensagem de derrota por máximo de tentativas

// funções
char* word_secret(); // retorna uma palavra secreta aleatória
void existence_check(char *str, char letter_input, int *indices, int *found_count); // verifica a existência de letras

int main() {
    char stringSecret[SECRET_WORD_SIZE];
    char maskString[SECRET_WORD_SIZE];
    int attempts = 0, errors = 0, hits = 0;
    char inputLetter;

    welcome_message();
    putchar('\n');
    printf("\tPor favor, pressione a tecla ENTER para iniciar o jogo: ");
    while (getchar() != '\n');

    word_initializer(stringSecret);
    initializing_letter_mask(maskString, stringSecret);

    do {
        clear_screen();
        show_hud(errors, attempts, maskString);

        // captura da entrada do usuário com validação
        printf("Entre com uma letra: => ");
        scanf(" %c", &inputLetter);
        inputLetter = tolower(inputLetter);

        // verifica a letra em todas as ocorrências
        int indices[SECRET_WORD_SIZE] = {0}, found_count = 0;
        existence_check(stringSecret, inputLetter, indices, &found_count);

        if (found_count > 0) {
            hits += found_count;
            for (int j = 0; j < found_count; j++) {
                unmasking_word(indices[j], maskString, stringSecret);
            }

            if (hits == strlen(stringSecret)) {
                clear_screen();
                winner_msg(stringSecret);
                return 0;
            }
        } else {
            errors++;
            if (errors == MAXIMUM_ERRORS) {
                clear_screen();
                loser_msg(stringSecret);
                return 1;
            }
        }

        attempts++;
    } while (attempts < KICKS);

    clear_screen();
    loser_msg_maxAttempts(stringSecret);
    return 0;
}

// Funções

void existence_check(char *str, char letter_input, int *indices, int *found_count) {
    *found_count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (tolower(str[i]) == letter_input) {
            indices[*found_count] = i;
            (*found_count)++;
        }
    }
}

char* word_secret() {
    char *SecretWordList[] = {
        "amor", "casa", "paz", "flor", "ceu", "mar", "luz", "vida", "bem", "livro"
    };
    srand(time(NULL));
    return SecretWordList[rand() % (sizeof(SecretWordList) / sizeof(SecretWordList[0]))];
}

void word_initializer(char *string_secret) {
    strncpy(string_secret, word_secret(), SECRET_WORD_SIZE);
}

void initializing_letter_mask(char *mask, char *wordSecret) {
    int len = strlen(wordSecret);
    for (int i = 0; i < len; i++) {
        mask[i] = '-';
    }
    mask[len] = '\0';
}

void show_hud(int errors, int attempts, char *maskString) {
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

void unmasking_word(int index, char *mask, char *str) {
    mask[index] = str[index];
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void welcome_message() {
    puts("\t ____________");
    puts("\t |\t   |");
    puts("\t |\t   |");
    puts("\t |\t   O \t Bem Vindo ao Jogo da Forca!");
    puts("\t |\t  /|\\ \t Tente adivinhar a palavra secreta!");
    puts("\t |\t  / \\ ");
    puts("\t | \t Número de Tentativas: 10\t Tamanho da Palavra: 5 letras!");
    puts("\t |");
}

void winner_msg(char *string_secret) {
    puts("\t ____________");
    puts("\t |\t   |");
    puts("\t |\t   |");
    puts("\t |\t   O \t PARABÉNS! VOCÊ GANHOU O JOGO!");
    printf("\t |\t  /|\\ \t Palavra secreta: %s\n", string_secret);
    puts("\t |\t  / \\ ");
    puts("\t |");
}

void loser_msg(char *string_secret) {
    puts("\t ____________");
    puts("\t |\t   |");
    puts("\t |\t   |");
    puts("\t |\t   O \t QUE PENA... VOCÊ PERDEU O JOGO!");
    printf("\t |\t  /|\\ \t Palavra secreta: %s\n", string_secret);
    puts("\t |\t  / \\ ");
    puts("\t |");
}

void loser_msg_maxAttempts(char *string_secret) {
    puts("\t ____________");
    puts("\t |\t   |");
    puts("\t |\t   |");
    puts("\t |\t   O \t VOCÊ PERDEU O JOGO POR EXCEDER O LIMITE DE TENTATIVAS!");
    printf("\t |\t  /|\\ \t Palavra secreta: %s\n", string_secret);
    puts("\t |\t  / \\ ");
    puts("\t |");
}
