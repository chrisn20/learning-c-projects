// For CS50 PSET2 - takes input and return grade level using Coleman-Liau Index
// Includes
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

// Declare functions - all calculations are done outside of Main
int count_letters(string);
int count_spaces(string);
int count_sentences(string);
int assess_grade(int, int, int);


int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
//    printf("Letters: %i\n", letters); - used for debug

// The number of words is number of spaces + 1 (since first word doesn't have a space)
    int words = count_spaces(text) + 1;
//    printf("Words: %i\n", words); - used for debug

    int sentences = count_sentences(text);
//    printf("Sentences: %i \n", sentences); - used for debug

    int grade = assess_grade(letters, words, sentences);

// Condition statement for printing output - could probably be moved to assess_grade function, but seems ok here too.
    if (grade < 1)
    {
        printf("Before Grade 1");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", grade);
    }
    printf("\n");

}

// Function for counting letters
int count_letters(string input)
{
    int n = 0, letters = 0;
    while (input[n] != '\0')
    {
        // Using upper case letters to make check easier.
        if (toupper(input[n]) >= 'A' && toupper(input[n]) <= 'Z')
        {
            letters++;
        }
        n++;
    }
    return letters;
}

// Function for counting spaces
int count_spaces(string input)
{
    int n = 0, spaces = 0;
    while (input[n] != '\0')
    {
        if (input[n] == ' ')
        {
            spaces ++;
        }
        n++;
    }
    return spaces;
}

// Function for counting sentences
int count_sentences(string input)
{
    int n = 0, sentences = 0;
    while (input[n] != '\0')
    {
        if (input[n] == '.' || input[n] == '!' || input[n] == '?')
        {
            sentences++;
        }
        n++;
    }
    return sentences;
}

// Function implementing Coleman-Liau
int assess_grade(int letters, int words, int sentences)
{
    float index, L, S;
    // to calculate L and S need to cast words as a float, otherwise output would still be an int
    L = letters / ((float) words / 100);
    S = sentences / ((float) words / 100);
    index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);
    return grade;
}