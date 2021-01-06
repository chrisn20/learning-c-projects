// Implement Caesar Cipher for CS50 PSET2

// Includes
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


// Declare functions
int check_key(string);


// Main

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int valid_key = check_key(argv[1]);
    if (valid_key != 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

// checking the key is valid means it should only contain digits, so we can convert to an int
    int key = atoi(argv[1]);

// use key to set rotation value. Mod 26 ensures it wraps around for key values > 26
    int rot = key % 26;

//    printf("Key valid, key value: %i\n", key);
//    printf("With the key, caesar will rotate characters by %i letters\n", rot);

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");
    int n = 0;
    while (plaintext[n] != '\0')
    {
        if (islower(plaintext[n]) != 0)
        {
            // if rotation would take character beyond z, check and wrap back around
            if (plaintext[n] + rot > 'z')
            {
                printf("%c", (plaintext[n] + rot) - 26);
            }
            else
            {
                printf("%c", plaintext[n] + rot);
            }
        }

        // probably neater way of doing this but *shrug* it works
        else if (isupper(plaintext[n]) != 0)
        {
            if (plaintext[n] + rot > 'Z')
            {
                printf("%c", (plaintext[n] + rot) - 26);
            }
            else
            {
                printf("%c", plaintext[n] + rot);
            }
        }
        else
        {
            printf("%c", plaintext[n]);
        }

        n ++;
    }
    printf("\n");

    return 0;


}

int check_key(string input)
{
    int i = 0, digits = 0, no_digit = 0;
    while (input[i] != '\0')
    {
        if (isdigit(input[i]) != 0)
        {
            digits ++;
        }
        else
        {
            no_digit ++;
        }
        i ++;
    }
    if (digits > 0 && no_digit == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
