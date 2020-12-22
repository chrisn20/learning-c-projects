// Solution for PSET5 - some code help obtained from Youtube

// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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
// This is determined by the type of hash function used
// E.g. if hashing just first character, 26 buckets are required
// E.g. first two characters 26 * 2
// The final hash function I've implemented here sums all the characters in a word, so number of buckets is 26 * max length of a word
const unsigned int N = 26 * LENGTH;

// Global counter to keep track of words in dictionary
int dict_words = 0;

// Hash table
node *table[N];

// Protoype destroy function - I've added this here instead of the header file, as otherwise it would not know what a node is
void destroy(node *head);


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash word to obtain a hash value
    int hash_index = hash(word);
    node *cursor = table[hash_index];


    // Access linked list at that index in the hash table
    // Traverse linked list, looking for the word (strcasecmp)

    // Repeat until cursor references a null pointer
    while (cursor != NULL)
    {
        // Check if word field in cursor matches word we are looking for
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // Move cursor to next field
        cursor = cursor->next;
    }

    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Take as input a word
    // Output a numberical index between 0 and N-1, inclusive
    // Deterministic - provides same output for same given input

    // Simplest hash, take first letter of word (in lowercase)
    // return tolower(word[0]) % N;

    // Second hash - hash first 2 chars in word
    // return (tolower(word[0]) + tolower(word[1])) % N;

    // Third hash - hash all chars
    int sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;

}





// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }


    // Create buffer to store words in
    char buffer[LENGTH + 1];

    // Read file until reach EOF
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Creates node and copies from buffer to word field in node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n-> word, buffer);
        n->next = NULL;

        // Hash word to get has value
        int hash_index = hash(buffer);

        // Insert node to hash table and hash location
        // Check if there is anything already in the hash table
        // If not, then just insert at that location

        if (table[hash_index] == NULL)
        {
            table[hash_index] = n;
        }
        // If there is already something, insert at start of linked list
        else
        {
            // Point next field to existing entry, then insert node at the start
            n->next = table[hash_index];
            table[hash_index] = n;
        }

        dict_words ++;
    }

    // Make sure file is closed
    fclose(file);

    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Loops through all entries in the table and runs the destroy function against them
    for (int i = 0; i < N; i++)
    {
        destroy(table[i]);
    }

    return true;

}


// Destroys list specified by unload function - uses recursion
void destroy(node *head)
{
    // Free up all list items that have been malloced
    if (head->next == NULL)
    {
        free(head);
        return;
    }

    destroy(head->next);
    free(head);
    return;
}