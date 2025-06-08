#include <stdio.h>

int main(void) {
    int i = 3;

    while (i > 0) {
        printf("In a while loop\n");
        i--;
    }
    
    for (i = 0; i < 3; i++) {
        printf("In a for loop\n");
    }

    while (1) {
        printf("Infinite loop\n");
    }
}