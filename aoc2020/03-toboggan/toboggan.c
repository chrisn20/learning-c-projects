// Solver for Advent of Code Day 3 - Toboggan
// Part 1: Traversing input at a slope of right 3, down 1, how many trees are encountered?
// Trees are marked by #s
// Part 2: 5 different slopes are given. Find the product of trees found accross those 5 slopes.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool read(FILE *file, int *length, int *size);
bool load(FILE *file, int length, int size, char *array[]);
int find_trees(int length, int size, char *array[], int x, int y);
bool unload(int size, char *array[]);

int main(int argc, char *argv[])
{
    // Check for usage
    if (argc != 2)
    {
        printf("Usage: ./toboggan INPUT\n");
        return 1;
    }

    // Create file pointer and check not NULL
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Could not open file\n");
        return 1;
    }

    // Read file once to get length and size
    int length = 0, size = 0;
    if (!read(file, &length, &size))
    {
        printf("Could not open file\n");
        return 1;
    }

    // Make sure length and size are not 0
    if (length == 0 || size == 0)
    {
        printf("Error parsing file\n");
        return 2;
    }

    // Create an array of size and load file into it
    char *map[size];
    if (!load(file, length, size, map))
    {
        printf("Error loading file into array\n");
        return 3;
    }

    // Part 1
    int x = 3, y = 1;
    int trees = find_trees(length, size, map, x, y);
    printf("Part 1 - Number of trees: %i\n", trees);

    // Part 2
    // Store slopes into a mini array to reference easily
    int vectors[5][2] =
    {
        {1, 1},
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2},
    };
    trees = 1;

    for (int i = 0; i < 5; i ++)
    {
        trees *= find_trees(length, size, map, vectors[i][0], vectors[i][1]);

    }
    printf("Part 2 - Number of trees: %i\n", trees);

    // Clean up
    fclose(file);
    if (!unload(size, map))
    {
        printf("Error freeing array. This may leak memory!\n");
        return 5;
    }

    return 0;
}

bool read(FILE *file, int *length, int *size)
{
    // Counters to track length of line and size of file
    int counter_l = 0, counter_s = 0;

    // First just scan 1 line to until end of line and increment counter to get line length
    while (fgetc(file) != '\n')
    {
        counter_l ++;
    }

    // Any issues, quit function
    if (counter_l == 0)
    {
        return false;
    }

    // We've read 1 line so can set line counter to 1. Create a single char buffer for next part
    counter_s = 1;
    char c = 0;

    // Keep reading file until reaching EOF
    // Increment counter anytime a newline is found
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            counter_s++;
        }
    }

    // If the counter hasn't incremented, something has gone wrong, so quit
    if (counter_s <= 1)
    {
        return false;
    }

    // Update the length and size variables in main and reset file
    // The size counter was coming up 1 short, so need to add 1 otherwise not full file will be loaded
    *length = counter_l;
    *size = counter_s + 1;
    rewind(file);
    return true;
}

bool load(FILE *file, int length, int size, char *array[])
{
    for (int i = 0; i < size; i++)
    {
        // We are managing an array of char* (essentialy an array of pointers that point to strings)
        // So to load a string into the array, we first need to malloc an area of memory to store the string
        // and then store the pointer to that string within the array
        array[i] = malloc(length + 1);
        if (array[i] == NULL)
        {
            return false;
        }
        fscanf(file, "%s", array[i]);
    }

    return true;
}


int find_trees(int length, int size, char *array[], int x, int y)
{
    int trees = 0;
    // The increment for j is modded over the length so that it will rollover gracefully
    for (int i = 0, j = 0; i <= size; i += y, j = (j + x) % (length))
    {
        if (array[i][j] == '#')
        {
            trees ++;
        }

    }

    return trees;
}

bool unload(int size, char *array[])
{
    for (int i = 0; i < size; i++)
    {
        free(array[i]);
    }
    return true;
}

