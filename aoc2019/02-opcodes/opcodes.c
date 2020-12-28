#include <stdio.h>
#include <stdbool.h>



int main(void)
{
    for (int i = 0; i <= 99; i++)
    {
        for(int j = 0; j <= 99; j++)
        {
                int opcodes[] = {1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,6,19,2,19,6,23,1,23,5,27,1,9,27,31,1,31,10,35,2,35,9,39,1,5,39,43,2,43,9,47,1,5,47,51,2,51,13,55,1,55,10,59,1,59,10,63,2,9,63,67,1,67,5,71,2,13,71,75,1,75,10,79,1,79,6,83,2,13,83,87,1,87,6,91,1,6,91,95,1,10,95,99,2,99,6,103,1,103,5,107,2,6,107,111,1,10,111,115,1,115,5,119,2,6,119,123,1,123,5,127,2,127,6,131,1,131,5,135,1,2,135,139,1,139,13,0,99,2,0,14,0};
                int pos = 0, newpos = 0, x = 0, y = 0, output = 0;
                opcodes[1] = i;
                opcodes[2] = j;

                while(opcodes[pos] != 99)
                {
                    //printf("Opcode at position %i is: %i\n", pos, opcodes[pos]);

                    if (opcodes[pos] == 1)
                    {
                        newpos = opcodes[pos + 3];
                        x = opcodes[pos + 1];
                        y = opcodes[pos + 2];
                        //printf("Adding %i (from position %i) + %i (from position %i) and storing result %i at position %i\n\n", opcodes[x], x, opcodes[y], y, opcodes[x] + opcodes[y], newpos);
                        opcodes[newpos] = opcodes[x] + opcodes[y];
                    }

                    if (opcodes[pos] == 2)
                    {
                        newpos = opcodes[pos + 3];
                        x = opcodes[pos + 1];
                        y = opcodes[pos + 2];
                        //printf("Multiplying %i (from position %i) * %i (from position %i) and storing result %i at position %i\n\n", opcodes[x], x, opcodes[y], y, opcodes[x] * opcodes[y], newpos);
                        opcodes[newpos] = opcodes[x] * opcodes[y];
                    }

                    if (opcodes[pos] != 1 && opcodes[pos] != 2 && opcodes[pos] != 99)
                    {
                        //printf("Error parsing opcode at position %i. Value is %i\n", pos, opcodes[pos]);
                        return 1;
                    }

                    pos += 4;

                }

                printf("Reached end of program\n");
                output = opcodes[0];
                printf("Value at position 0 is now: %i\n", opcodes[0]);
                printf("Output value is %i\n", output);

                if (output == 19690720)
                {
                    printf("Correct output obtained.\n");
                    printf("Output is %i, noun is %i, verb is %i\n", output, i, j);
                    printf("100 * noun + verb = %i\n", 100 * i + j);
                    return 0;
                }

                printf("Correct output value not found, noun was %i and verb was %i\n\n", i, j);

        }
    }
}


