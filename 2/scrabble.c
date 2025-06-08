#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int SCORES [] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}; 

int get_score(char word[]);
int get_letter_score(char letter);
void print_winner(int score1, int score2);

int main(void) {        
    char word1[100];
    char word2[100];

    //get inputs
    printf("Player 1: ");
    scanf("%s", word1);
    printf("Player 2: ");
    scanf("%s", word2);

    //score words
    int score1 = get_score(word1);
    int score2 = get_score(word2);

    printf("%s has a score of %d\n", word1, score1);
    printf("%s has a score of %d\n", word2, score2);
}

int get_score(char word[]) {
    int sum = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        sum += get_letter_score(word[i]);
    }    
    return sum;
}

int get_letter_score(char letter) {
    //ignore non-alpha characters
    if (!isalpha(letter)) {
        return 0;
    }

    //normalize char
    char normalized = toupper(letter);
    
    //cast as int
    int index = normalized - 65;
    return SCORES[index];
}

void print_winner(int score1, int score2) {
    if (score1 > score2) {
        printf("Player 1 wins!\n");
    } else if (score1 < score2) {
        printf("Player 2 wins!\n");
    } else {
        printf("TIE!\n");
    }
}