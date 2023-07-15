#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int coins = 0;

    //Aks the user for the change owed and ensures the value is a non-negative integer
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    //Converts our float to an int of cents to mitigate precision errors
    int cents = round (change * 100);

    while (cents >= 100)
    {
        cents -= 100;
        coins += 4;
    }
    while (cents >= 25)
    {
        cents -= 25;
        coins++;
    }

    while (cents >= 10)
    {
        cents -= 10;
        coins++;
    }
    while (cents >= 5)
    {
        cents -= 5;
        coins++;
    }
    while (cents >= 1)
    {
        cents -= 1;
        coins++;
    }
    printf("%i\n", coins);
}