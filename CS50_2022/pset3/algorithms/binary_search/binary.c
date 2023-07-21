// This program illustrates the use of binary search
#include <stdio.h>

int main(void)
{
	int numbers[] = {6, 7, 8, 9, 10, 11, 14, 15, 17, 19, 22, 23, 25, 28, 30};
	int target = 15;
	int start = 0;
	int end = 14;
	int middle;
	
	while (start <= end)
	{	
		middle = (start + end) / 2;
		if (numbers[middle] == target)
		{
			printf("Found!\n");
			return 0;
		}
		else if (target < numbers[middle])
			end = middle - 1;
		else
			start = middle + 1;
	}
	printf("Not found!\n");
}	
