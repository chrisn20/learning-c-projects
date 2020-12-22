//Cash for Pset1 - resubmit as optimised
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        change = get_float("Change owed: $"); //capture input from user
    }
    while (change < 0); // checks that input is positive value

    int cents = round(change * 100); // avoid float errors & for easy division

    int quarters = cents / 25; // number of quarters = cents divided by 25
    int remain = cents % 25; // store remainder to keep track
//    printf("Quarters: %i, Remainder: %i\n", quarters, remain);
//    ^used for debugging to check maths

    int dimes = remain / 10;
    remain = remain % 10; // update remainder
//    printf("Dimes: %i, Remainder: %i\n", dimes, remain);

    int nickles = remain / 5;
    remain = remain % 5;
//    printf("Nickles: %i, Remainder: %i\n", nickles, remain);

    int pennies = remain;
    remain = pennies % 1;
//    printf("Pennies: %i, Remainder: %i\n", pennies, remain);

    printf("%i\n", quarters + dimes + nickles + pennies); //jobs a good'un

}