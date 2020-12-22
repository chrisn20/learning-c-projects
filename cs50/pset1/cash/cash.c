// More advanced version of cash, using techniques from later versions
// Not for pset submission, just refreshing knowledge
#include <stdio.h>
#include <cs50.h>
#include <math.h>

typedef struct
{
    string name;
    int value;
}
coin;


int main(void)
{
    coin coins[4] = {[0].name = "quarter", [0].value = 25, [1].name = "dime", [1].value = 10, [2].name = "nickle", [2].value = 5, [3].name = "penny", [3].value = 1};

    // Get input from user
    float change = -1;
    do
        {
            change = get_float("Change owed: $");
        }
    while (change < 0);
    
    int cents = round(change * 100), total = 0;
    
    for (int i = 0, remain = cents; i < 4; i++)
        {
            total = total + (remain / coins[i].value);
            remain = remain % coins[i].value;
        }
    
    printf("%i \n", total);

}