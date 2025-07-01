// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>  

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define N 2000

// Hash table
node *table[N];
unsigned long dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
  
    //get hash
    unsigned int hash_value = hash(word);

    //search in dictionary
    node *ptr = table[hash_value];
    while (ptr != NULL) {
        if (strcasecmp(ptr->word, word) == 0) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 0;
    for(int i = strlen(word); i >= 0; i--) {
        hash += word[i];
    }
    return hash % 2000;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //set hashtable heads to NULL
    for (int i = 0; i < N; i++) {
        table[i] = NULL;
    }
    //open file
    FILE *f = NULL;
    f = fopen(dictionary, "r");
    if (f == NULL) {
        printf("Error opening dictionary\n");
        return false;
    }

    //read through
    char buff[LENGTH +1];
    while (fgets(buff, LENGTH, f) != NULL) {  
        
        //remove trailing newline
        if (buff[strlen(buff) - 1] == '\n') {
            buff[strlen(buff) - 1] = '\0';
        }
        //create node for word
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            printf("Error mallocing node\n");
            return false;
        }
        strcpy(n->word, buff);

        //get hash
        unsigned int hash_value = hash(n->word);

        //insert into appropriate LL (reversed)
        n->next = table[hash_value];
        table[hash_value] = n;
        dictionary_size++;    
    }   
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{   
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) {
        node *ptr = table[i];
        while (ptr != NULL) {
            node *tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    return true;
}
