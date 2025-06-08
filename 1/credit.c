#include <stdio.h>

long get_number(void);
int passes_luhn (long number);
int get_digits(long number);
int is_visa(long number, int digits);
int is_mastercard(long number, int digits);
int is_amex(long number, int digits);

int main(void) {
    long input = get_number();
    
    if (!passes_luhn(input)) {
        printf("INVALID\n");
        return 0;
    }

    int digits = get_digits(input);
    if (is_visa(input, digits)) {
        printf("VISA\n");
    } else if (is_mastercard(input, digits)) {
        printf("MASTERCARD\n");
    } else if (is_amex(input, digits)) {
        printf("AMEX\n");
    } else {
        printf("INVALID\n");
    }
}

long get_number(void) {
    long n;
    do {
        printf("Number: ");
        scanf("%ld", &n);
    } 
    while (n < 1);
    return n;
}

int passes_luhn (long number) {
    int added_products = 0;
    int sum = 0;
    while (number > 0) {
        //add first digit to sum
        sum += (number % 10);
        
        number /= 10;

        //add next digit to products
        int product = number % 10 * 2;
        if (product > 9) {
            added_products += 1;
        }
        added_products += product % 10;
        
        number /= 10;
    }
    int final_total = sum + added_products;   
    if (final_total % 10 == 0) {
        return 1;
    }
    return 0;
}

int get_digits(long number) {
    int digits = 0;
    while (number > 0) {
        digits++;
        number /= 10;
    }
    return digits;
}

int is_visa(long number, int digits) {
    if (digits == 16) {
        number /= 1000000000000000;        
    } else if (digits == 13) {
        number /= 1000000000000;
    }
    if (number == 4) {
        return 1;
    } else {
        return 0;
    }
}
int is_mastercard(long number, int digits) {
    if (digits == 16) {
        number /= 100000000000000;        
    }
    if (number > 50 && number < 56) {
        return 1;
    } else {
        return 0;
    }
}
int is_amex(long number, int digits) {
    if (digits == 15) {
        number /= 10000000000000;        
    }
    if (number == 34 || number == 37) {
        return 1;
    } else {
        return 0;
    }
}