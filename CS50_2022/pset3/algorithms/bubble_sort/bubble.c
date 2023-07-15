// This program is an implementation of bubble sort
// The program sorts an array of ints in ascending order
#include <stdio.h>

int main(void)
{
	int numbers[] = {10, 4, 0, 7, 2, 5, 1, 9, 3, 6, 8};
	int swaps, temp;
	for (int i = 0; i < 11; i++)
	{	
		swaps = 0;
		for (int j = 0; j < 10; j++)
		{
			if (numbers[j + 1] < numbers[j])
			{
				// Swap numbers[j] and numbers[j + 1];
				temp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = temp;
				swaps++;
			}
		}
		if (swaps == 0)
			break; 
	}
	// Print the sorted int array
	for (int k = 0; k < 11; k++)
	{
		printf("%i\n", numbers[k]);	
	}
}
