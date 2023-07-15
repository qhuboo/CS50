// This program is an implementation of selection sort
// The program sorts an array of ints in ascending order

#include <stdio.h>

int main(void)
{
	int numbers[] = {10, 4, 0, 7, 2, 5, 1, 9, 3, 6, 8};
	int min, min_indx, temp;
	for (int i = 0; i < 10; i++)
	{	
		min = numbers[i];
		min_indx = i;
		for (int j = i + 1; j < 11; j++)
		{
			if (numbers[j] < min)
			{
				min = numbers[j];
				min_indx = j;
			}
		}
		// Swaps values
		temp = numbers[i];
		numbers[i] = min;
		numbers[min_indx] = temp;
	}
	// Print the sorted int array	
	for (int k = 0; k < 11; k++)
	{
		printf("%i\n", numbers[k]);
	}
}
