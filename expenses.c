// Solver for Advent of Code 2020 - Day 1 - Expenses
// Built to be dynamic and handle any input file (assuming same format), even though that is beyond scope of problem
// Problem to solve: from given input, find the 3 (1st part of problem looks for 2) values that add to 2020 and multiply them to get the result

// Includes
#include <stdio.h>
#include <stdbool.h>

// Prototypes
int size_file(FILE *file);
bool load_file(FILE *file, int size, int array[]);
bool find_value(int size, int array[], int *x, int *y, int *z);

int main(int argc, char *argv[])
{

    // Check for correct usage
    if (argc != 2)
    {
        printf("Usage: ./expenses INPUT\n");
        return 1;
    }

    // Open file and make sure it works
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Error loading input file\n");
        return 1;
    }

    // Get size of file e.g. number of lines
    int size = size_file(file);
    if (size <= 0)
    {
        printf("Error parsing file\n");
        return 1;
    }

    // Create array of size
    int array[size];

    // Copy file into array
    bool loaded = load_file(file, size, array);
    if (!loaded)
    {
        printf("Errory populating array\n");
        return 1;
    }

    // We want to find the position of the 3 values in the array that add to 2020, represented by x, y, and z
    int x = 0, y = 0, z = 0;

    // Pass everything to the find value function
    bool value = find_value(size, array, &x, &y, &z);
    if (!value)
    {
        printf("Could not find 3 values values adding to 2020\n");
        return 1;
    }

    // Get our result by looking up values in those positions from the array and getting the product
    int result = array[x] * array[y] * array[z];
    printf("Result: %i\n", result);

    // Cleanup
    fclose(file);
    return 0;
}

int size_file(FILE *file)
{
    int buffer = 0, size = 0;

    while (fscanf(file, "%i", &buffer) != EOF)
    {
        size ++;
    }

    return size;
}

bool load_file(FILE *file, int size, int array[])
{
    int buffer = 0;
    rewind(file);
    for (int i = 0; i < size; i++)
    {
        fscanf(file, "%i", &buffer);
        array[i] = buffer;
    }
    return true;
}

// Function to find 3 values that sum to 2020. Returns true if found, and updates x,y,z to the positions of the values in the array
// Uses 3 iterative loops - so pretty inefficient! How could this be improved?
bool find_value(int size, int array[], int *x, int *y, int *z)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 1; j < size; j++)
        {
            for (int k = 2; k < size; k++)
            {
                // Condition is that the values add to 2020, and they should all be from different positions
                if (array[i] + array[j] + array[k] == 2020 && i != j && i != k && j != k)
                {
                    // x, y, z, are updated to give the position of the values in the array
                    *x = i;
                    *y = j;
                    *z = k;
                    return true;
                }
            }
        }
    }
    return false;
}