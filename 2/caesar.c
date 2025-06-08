#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_key(int argc, char *argv[]);
void encrypt_text(char text[], int key);

int main (int argc, char *argv[]) {
    char text[1000];

    int key = get_key(argc, argv);
    if (key == 0) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //get user text
    printf("plaintext: ");
    fgets(text, 1000, stdin);

    //standardize key
    int standardized_key = key % 26;

    //print decrypted text
    encrypt_text(text, standardized_key);
    printf("ciphertext: %s\n", text);  
    
    return 0;
}

//also checks validity, returns 0 on non valid
int get_key(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }
    int key = atoi(argv[1]);
    if (key < 1) {
        return 0;
    }  
    return key;
}

void encrypt_text(char text[], int key) {
    char c;    

    for (int i = 0; i < strlen(text); i++) {
        c = text[i];
        if (!isalpha(c)) {
            continue;
        }
        if (c + key > 'z') {
            text[i] = 'a' + (c + key - 123);
        } else if (toupper(c) + key > 'Z') {
            text[i] = 'A' + (c + key - 91);
        } else {
            text[i] = c + key;
        }        
    }
}