#include <stdio.h>

int get_positive_integer(void);
void meow(int n);

int main(void) {
    int n = get_positive_integer();
    meow(n);
    
}

int get_positive_integer(void) {
    int n;
    do {
        printf("Enter a positive integer: ");
        scanf("%d", &n);
    } while (n <= 0);
    return n;
}

void meow(int n) {
    while (n > 0) {
        printf("meow\n");
        n--;
    }
}