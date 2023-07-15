#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Asks the user for the start size and ensures it is at least 9
    int ssize;
    do
    {
        ssize = get_int("Start size: ");

    }
    while (ssize < 9);

    //Asks the user for the desired end size and ensures it is at least as large as the start size
    int esize;
    do
    {
        esize = get_int("End size: ");
    }
    while (esize < ssize);

    int years = 0;

    //Calculates the new size of the population until surpassing the end size and adds 1 to the years counter per iteration
    while (ssize < esize)
    {
        ssize = ssize + (ssize / 3) - (ssize / 4);
        years++;
    }

    printf("Years: %i\n", years);  //Prints the number of years (the number of times the while loop iterated)
}