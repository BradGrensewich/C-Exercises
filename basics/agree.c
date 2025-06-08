#include <stdio.h>

int main(void) {
    char c;

    printf("Do you agree? ");
    scanf("%c", &c);

    if (c == 'Y' || c == 'y') {
        printf("Agreed\n");
    } else {
        printf("Not agreed\n");
    }
}