#include <stdio.h>

int main(void)
{

    long number = 3553123456784321;

    printf("Starting number: %li\n", number);

    do
    {
        printf("Digit: %li\n", number % 10);
        number = number / 10;
        printf("New number: %li\n", number);
    }
    while (number > 0);
    
    return 0;

}
