//credit for pset1 - resubmit as format/comments optimised
//credit - another resubmit as main logic optimised to fit into one loop
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long number;

    do
    {
        number = get_long("Enter Credit Card#: ");
    }
    while (number < 0);

    long temp_num = number; // temporary variable to operate w/o losing input

    int length = 0;
    int sum1 = 0;
    int temp_num_x2;
    int sum2 = 0;
    int digit0;
    int digit1;

    do // main loop to work out length of number and calculate checksums
    {
        if (length % 2 == 0) // for last digit and every two digits after
        {
            sum2 = sum2 + (temp_num % 10); // add digit to running total
            digit0 = temp_num % 10; // store that digit for later
        }
        else // for every other digit
        {
            temp_num_x2 = 2 * (temp_num % 10); //multiply that digit by two
            sum1 = sum1 + (temp_num_x2 % 10) + ((temp_num_x2 / 10) % 10);
            digit1 = temp_num % 10;
        }
        temp_num = temp_num / 10; //reduces length of number by 1

        length ++; //increments length variable
    }
    while (temp_num > 0); // this works as long as card numbers can't start with 0
// when loop ends we know length of number based on how many times it has incremented

    if (length % 2 == 0) // we need to swap digits round for even length card numbers
    {
        int digit_temp;
        digit_temp = digit0;
        digit0 = digit1;
        digit1 = digit_temp;
    }

//  printf("Length: %i\n", length);
//  printf("%i%i\n", digit0, digit1);
//  ^ debug: print length and digits to check these are correct

    int check = (sum1 + sum2) % 10;
//  ^ adds the results of the two checks and takes the last digit.
//    if number is valid this should be 0 (checked later)

    int first_2d = (digit0 * 10) + digit1;
// times digit0 by 10 and add digit1 to give us the first 2 digits in one value, used in some of the checks

// debug code = just to check calcs are working
//  printf("sum1: %i\n", sum1);
//  printf("sum2: %i\n", sum2);
//  printf("sum3: %i\n", sum1 + sum2);
//  printf("check: %i\n", check);
//  printf("first two digits: %i\n", first_2d);

// All the various checks take place in the below block
// Iterative boolean expressions, could probable be optimised if you really want
    if (digit0 == 4 && check == 0 && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    else if ((first_2d == 34 || first_2d == 37) && check == 0 && length == 15)
    {
        printf("AMEX\n");
    }
    else if (first_2d >= 51 && first_2d <= 55 && check == 0 && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

}