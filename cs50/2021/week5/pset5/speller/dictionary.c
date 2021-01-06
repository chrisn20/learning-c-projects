// CS50 Academic Honesty - when going through the CS50x 2020 version of this problem, I received some help for the solution from Youtube.
// I therefore did not submit my solution to the pset at the time
// For this implementation, I have redone the full pset (including doing the new lab) without any outside help
// I am therefore comfortable that it is reasonable for me to submit this version of the pset
// In addition, I have practiced the concepts of linked lists in other problems, including some of the first few days of AoC 2020
// which can be found on my github repository: https://github.com/chrisn20/learning-c-projects/tree/main/aoc2020
// to demonstrate to myself that I fully understood these concepts and could use them for other problems.

// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Global var to keep track of words in dictionary
int size_of_dictionary = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash word to get index for start of list to search through
    int index = hash(word);
    node *cursor = table[index];

    // Use cursor to navigate list and compare against desired word
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash based on first letter in word - not looking to optimise this solution, just to complete pset.
    return tolower(word[0]) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy word into node
        strcpy(n->word, word);

        // Get index for table from hash function
        int index = hash(word);

        // Inserting at beginning of list, so set next to what was there before - if start of list, this will just be NULL
        n->next = table[index];

        // Set index to be new start of list
        table[index] = n;

        // Increment counter to keep track of dictionary size
        size_of_dictionary ++;

    }

    // Dont forget to close file! valgrind --leak-check=full --show-leak-kinds=all was very helpful to pinpoint this as a source of leaks!
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Kept track in global var so just return that
    return size_of_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through table and linked lists
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            // Make sure not to lose track of list when freeing
            node *eraser = cursor;
            cursor = cursor->next;
            free(eraser);
        }


    }
    return true;
}
