// Solver for Advent of Code 2019 Day 01

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Create structure for linked list
typedef struct node
{
    int module;
    struct node *next;
} node;

// Create empty list
node *list;

// Prototypes
bool load(const char *input);
int calc_fuel(int);
void unload(node *head);


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./01 input\n");
        return 1;
    }

    // Get input file
    char *input = argv[1];

    // Load file and check for success
    bool loaded = load(input);
    if (!loaded)
    {
        printf("Could not load input\n");
        return 2;
    }

    // Start summing up fuel requirements, and create cursor for navigating list
    int sum_fuel = 0;
    node *cursor = list;

    while (cursor != NULL)
    {
        sum_fuel += calc_fuel(cursor->module);
        cursor = cursor->next;
    }

    printf("Fuel required: %i\n", sum_fuel);

    // Unload the list
    unload(list);

    return 0;

}

bool load(const char *input)
{
    // Open file and check for success
    FILE *file = fopen(input, "r");
    if (!file)
    {
        return false;
    }

    // Read file and populate list
    int buffer = 0;

    while (fscanf(file, "%i", &buffer) != EOF)
    {
        // Malloc new node and check not null
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Write buffer value to module field and insert at start of list
        n->module = buffer;
        n->next = list;
        list = n;
    }

    // Close/clean up and return
    fclose(file);
    return true;
}


int calc_fuel(int module)
{
    // If fuel requirements are less than 0, return 0 (base case)
    if ((int) trunc(module / 3.0) - 2 <= 0)
    {
        return 0;
    }
    // Else keep calculating fuel requirements recursively
    module = (int) trunc(module / 3.0) - 2;
    return module += calc_fuel(module);
}


void unload(node *head)
{
    // Free up all list items that have been malloced
    if (head->next == NULL)
    {
        free(head);
        return;
    }

    unload(head->next);
    free(head);
    return;
}