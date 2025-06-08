#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int LETTERS_IN_ALPHABET = 26;

int valid_key (char *key);
void encrypt_text(char text[], char *key);

int main (int argc, char *argv[]) {
    char text[1000];

    if (argc != 2 || !valid_key(argv[1])) {
        printf("Usage ./substitution key\n");
        return 1;
    } 
    
    //get input
    printf("plaintext: ");
    fgets(text, 1000, stdin);

    encrypt_text(text, argv[1]);

    printf("ciphertext: %s\n", text);


}

//also normalizes key to uppercase
int valid_key (char *key) {
    if (strlen(key) != LETTERS_IN_ALPHABET) {
        return 0;
    }

    int used[26] = {0};

    for (int i = 0; i < LETTERS_IN_ALPHABET; i++){
        if (!isalpha(key[i])) {
            return 0;
        }
        //normalize
        key[i] = toupper(key[i]);

        //check if already used in key
        char c_index = key[i] - 'A';
        if (used[c_index] == 1) {
            return 0;
        }
        used[c_index] = 1;
    }
    return 1;
}

void encrypt_text(char text[], char *key) {
    int length = strlen(text);

    for (int i = 0; i < length; i++) {
        if (isupper(text[i])) {
            text[i] = key[text[i] - 'A'];
        } else if (islower(text[i])) {
            text[i] = tolower(key[text[i] - 'a']);
        }
    }

}