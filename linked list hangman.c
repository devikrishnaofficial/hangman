#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct Node {
    char letter;
    struct Node* next;
};
struct Node* head;
char letter;
struct Node* addToGuessedLetters() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->letter = letter;
    newNode->next = head;
    return newNode;
}
int isLetterGuessed(char letter) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->letter == letter) {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}

int main() {
	int i;
    char *words[] = {"programming", "hangman", "computer", "keyboard", "developer"};
    srand(time(NULL));
    int index = rand() % 5;
    char word[20], guessed[20];
    strcpy(word, words[index]);
    int len = strlen(word), tries = 6, correct = 0;
    printf("Welcome to Hangman!\n");

    struct Node* guessedLetters = NULL; 

    while (tries > 0 && correct < len) {
        printf("\nWord: ");
        for (i = 0; i < len; i++) {
            if (guessed[i] || word[i] == ' ') {
                printf("%c", word[i]);
            } else {
                printf("_");
            }
        }
        printf("\nGuessed letters: ");
        struct Node* current = guessedLetters;
        while (current != NULL) {
            printf("%c ", current->letter);
            current = current->next;
        }
        printf("\nGuess a letter: ");
        char guess;
        scanf(" %c", &guess);

        if (isLetterGuessed( guess)) {
            printf("You've already guessed that letter.\n");
            continue;
        }

        guessedLetters = addToGuessedLetters( guess);

        int found = 0;
        for (i = 0; i < len; i++) {
            if (!guessed[i] && word[i] == guess) {
                guessed[i] = 1;
                correct++;
                found = 1;
            }
        }
        if (!found) {
            tries--;
            printf("Incorrect guess. Tries left: %d\n", tries);
        }
    }
    printf("\n");
    if (correct == len) {
        printf("Congratulations! You guessed the word: %s\n", word);
    } else {
        printf("Sorry, you're out of tries. The word was: %s\n", word);
        printf("  ______\n");
        printf(" |      |\n");
        printf(" |      O\n");
        printf(" |     /|\\\n");
        printf(" |     / \\\n");
        printf("_|_\n");
    }

    // Free memory for the guessed letters linked list
    struct Node* current = guessedLetters;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
