#include <stdio.h>

// This program is an example of linear search. It initializes a int array of size 7 with 0 in one
// of the array locations and employs linear search in order to find where exactly.
// Alternetaviley, you can change the array so that 0 is not contained in any locations thus illustrating
// how the algorithm may respond when the search is not successful.
// We name the int array lockers to illustrate the point.

int main(void)
{
	int lockers[] = {2, 4, 1, 9, 0, 3, 7};
	for (int i = 0; i < 7; i++)
	{
		if (lockers[i] == 0)
		{
			printf("Found!\n");
			return 0;
		}
	}
	printf("Not Found!\n");
	return 1;
}
