#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
    	n = get_int("Start size: ");
    }
    while (n < 9);

    int e;
    do
    {
    	e = get_int("End size: ");
    }
    while (e < n);
	
    int years = 0;
    while (n < e)
    {
    	n = n + (n/3) - (n/4);
	years++;
    }

    printf("Years: %i\n", years);

}
