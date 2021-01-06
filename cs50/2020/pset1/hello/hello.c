//Greets user

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name: "); //Declare name as string and get input from user
    printf("Hello, %s\n", name); //Greet user using previous input
}