#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    // Get the user to input a number between 1 and 8 inclusive
    do
    {
        n = get_int("Height: ");
    }
    while ((n < 1) || (n > 8));
    for (int i = 1; i <= n; i++)
    {
        // Outputs spaces
        for (int k = 0; k < n - i; k++)
        {
            printf(" ");
        }
        // Outputs hashes
        for (int j = 0; j < (n - (n - i)); j++)
        {
            printf("#");
        }
        printf("  ");
	for (int j = 0; j < (n - (n - i)); j++)
	{
	    printf("#");
	}
	printf("\n");
    }
}

