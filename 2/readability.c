#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void get_counts(char input[], int counts[]);
float get_letters_per_100_words(int letters, int words);
float get_sentences_per_100_words(int sentences, int words);
float get_CL_index(float L, float S);
void output_score(float score);

int main(void) {
    char input[10000];
    // in order words, sentences, letters
    int counts[3];
    
    //get user input
    printf("Text: ");
    fgets(input, 10000, stdin);

    get_counts(input, counts);

    float L = get_letters_per_100_words(counts[2], counts[0]);
    float S = get_sentences_per_100_words(counts[1], counts[0]);

    float score = get_CL_index(L, S);

    output_score(score);
    
}

void get_counts(char input[], int counts[]) {
    int length = strlen(input);
    int word_count = 1;
    int sentence_count = 0;
    int letter_count = 0;
    
    for (int i = 0; i < length; i++) {
        char c = input[i];
        if (c == ' ') {
            word_count++;
        } else if (c == '.' || c == '!' || c == '?') {
            sentence_count++;
        } else if (isalpha(c)) {
            letter_count++;
        }
    }
    counts[0] = word_count;
    counts[1] = sentence_count;
    counts[2] = letter_count;    
    
}

float get_letters_per_100_words(int letters, int words) {
    float multiplier = 100.0 / words;   
    float L = letters * multiplier;
    return L;
}

float get_sentences_per_100_words(int sentences, int words) {
    float multiplier = 100.0 / words;
    float S = sentences * multiplier;
    return S;
}

// implements index = 0.0588 * L - 0.296 * S - 15.8
float get_CL_index(float L, float S) {    
    return 0.0588 * L - 0.296 * S - 15.8;
}

void output_score(float score) {
    //TODO
    int grade = round(score);

    if (grade < 1) {
        printf("Before Grade 1\n");
    } else if (grade >= 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %d\n", grade);
    }
}
