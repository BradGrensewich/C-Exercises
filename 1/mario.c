#include <stdio.h>

int get_valid_height(void);
void print_pyramid(int height);
void print_row (int height, int floor);
void print_bricks(int count);

int main(void) {
    int height = get_valid_height();
    print_pyramid(height);
}

int get_valid_height(void) {
    int n;
    do {
        printf("Height: ");
        scanf("%d", &n);
    } 
    while (n < 1 || n > 8);
    return n;
}

void print_pyramid(int height) {
    for (int i = 1; i <= height; i++) {
        print_row(height, i);
    }
}

void print_row (int height, int floor) {
    //print spaces
    for (int i = height; i > floor; i--) {
        printf(" ");
    }
    
    //print bricks
    print_bricks(floor);
    
    //print gap
    printf("  ");
    
    //print other bricks
    print_bricks(floor);

    //newline
    printf("\n");
}

void print_bricks(int count) {
    while (count > 0) {
        printf("#");
        count--;
    }
}