// Implement Substitution Cipher for CS50 PSET2 - based on my code for caesar

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
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int valid_key = check_key(argv[1]);
    if (valid_key != 1)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

// convert all characters in input to lowercase and store as key
    string key = argv[1];
    int i = 0;
    while (key[i] != '\0')
    {
        key[i] = tolower(key[i]);
        i ++;
    }

// check for unique characters key should have 26 unique
// note I used google/stackoverflow to get the structure of how to do this check
    int unique = 0;
    // loop for each character in the string
    for (i = 0; i < 26; i ++)
    {
        bool dupe = false;
        // loop for each previous character
        for (int j = 0; j < i; j++)
        {
            // compare
            if (key[j] == key[i])
            {
                dupe = true;
                break;
            }
        }
        if (!dupe)
        {
            unique ++;
        }
    }
    if (unique != 26)
    {
        printf("Key must not contain duplicates\n");
        return 1;
    }


//  printf("Key valid, key value: %s\n", key);


    string plaintext = get_string("plaintext: ");


    printf("ciphertext: ");
    int n = 0, sub_char = 0;
    while (plaintext[n] != '\0')
    {
        if (islower(plaintext[n]) != 0)
        {
            // print char from key array equal to plaintext
            sub_char = plaintext[n] - 'a';
            printf("%c", key[sub_char]);
        }


        else if (isupper(plaintext[n]) != 0)
        {
            // same as above for need to convert back to uppercase
            sub_char = plaintext[n] - 'A';
            printf("%c", toupper(key[sub_char]));

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
    int i = 0, alpha = 0, no_alpha = 0;
    while (input[i] != '\0')
    {
        if (isalpha(input[i]) != 0)
        {
            alpha ++;
        }
        else
        {
            no_alpha ++;
        }
        i ++;
    }
    if (alpha == 26 && no_alpha == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
