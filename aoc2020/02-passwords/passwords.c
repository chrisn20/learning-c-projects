// Solution for Advent of Code 2020 - Day 02
// Problem Part 1: From given input of password, and associated policy, determine how many passwords are valid
// Problem Part 2: Different policy


// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define expected max length of password - starting large, if for any reason there are memory issues, can reduce
#define LENGTH 50

// Prototype structure for storing input
typedef struct node
{
    int min;
    int max;
    char policy;
    char password[LENGTH + 1];
    struct node *next;
} node;

// Create empty list
node *list;

// Function prototypes
bool load(const char *input);
int check_passwords(node *head);
int check_passwords2(node *head);
void unload(node *head);

// Start of main
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./passwords INPUT\n");
        return 1;
    }

    // Load file and check for success
    if (!load(argv[1]))
    {
        printf("Could not load input\n");
        return 1;
    }

    int valid_pass = check_passwords(list);
    printf("Number of valid passwords (part 1): %i\n", valid_pass);
    int valid_pass2 = check_passwords2(list);
    printf("Number of valid passwords (part 2): %i\n", valid_pass2);

    unload(list);
    return 0;
}

bool load(const char *input)
{
    FILE *file = fopen(input, "r");
    if(!file)
    {
        return false;
    }

    char min_s[3], max_s[3], policy_s[2], password[LENGTH + 1];
    char buffer[10 + LENGTH + 1];

    while (fgets(buffer, 10 + LENGTH + 1, file) != NULL)
    {
        strcpy(min_s, strtok(buffer,"-"));
        strcpy(max_s, strtok( NULL, " " ));
        strcpy(policy_s, strtok( NULL, ":" ));
        strcpy(password, strtok( NULL, "\n" ));

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        n->min = atoi(min_s);
        n->max = atoi(max_s);
        n->policy = policy_s[0];
        strcpy(n->password, password + 1);
        n->next = list;
        list = n;

    }
    fclose(file);
    return true;
}

int check_passwords(node *head)
{
    node *cursor = head;
    int valid_p = 0;

    while (cursor != NULL)
    {
        int length = strlen(cursor->password), num_chars = 0;
        for (int i = 0; i < length; i++)
        {
            if (cursor->password[i] == cursor->policy)
            {
                num_chars ++;
            }
        }
        if (num_chars <= cursor->max && num_chars >= cursor->min)
        {
            valid_p ++;
        }

        cursor = cursor -> next;
    }

    return valid_p;
}

int check_passwords2(node *head)
{
    node *cursor = head;
    int valid_p = 0;

    while (cursor != NULL)
    {
        if (!(cursor->password[(cursor->min) - 1] == cursor->policy) != !(cursor->password[(cursor->max) - 1] == cursor->policy))
        {
            valid_p ++;
        }
        cursor = cursor -> next;
    }

    return valid_p;

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

