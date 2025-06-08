#include <stdio.h>

int main(void) 
{
    char username[100];
    printf("What's your name? ");
    scanf("%s", username);
    printf("hello, %s\n", username);
}