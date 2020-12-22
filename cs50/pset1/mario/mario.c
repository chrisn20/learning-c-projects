//Mario - more. Started off doing mario less, and once that worked, it was easy to add the spaces and replicate hashes on the other side
//Probably possible to make other side hashes neater, but not sure if worth it at this point :)

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x;

    do
    {
        x = get_int("x: "); //capture integer input from user
    }
    while (x < 1 || x > 8); //checks that input is between 1 and 8 inclusive

    for (int i = 0; i < x; i++) // make x number of lines - whole block repeats x times
    {
        for (int j = 0; j < x - i - 1 ; j++) //generates spaces at the start of the line.
//Number of spaces is dependent on how many lines there are total (x), which line the program is on (i), and there will always be -1 dots compared to line
        {
            printf(" ");
        }

        for (int k = 0 ; k < i + 1; k++) //generates first block of hashes to form pyramid
//number of hashes is equal to the line this is on (i), but since we start counting at 0 we have to add + 1 to the loop condition
        {
            printf("#");
        }

        printf("  "); // prints spaces between the sets of blocks/hashes

        for (int l = 0; l < i + 1; l++) //generates second block of hashes of the pyramid
//works exact same way as above, so probably could be collapsed into one loop block - perhaps one to revisit.
        {
            printf("#");
        }

        printf("\n"); //prints a newline at the end of the row
    }

}