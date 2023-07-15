// This program illustrates recursion by implementing the collatz algorithm
// The program calculates the number of steps it takes for the collatz algorithm to get back
// to 1 given an input positive integer s. 
#include <stdio.h>

int collatz(int n);

int main(void)
{
	int s = 27;
	int steps = collatz(s);
	printf("Steps: %i\n", steps);
}

int collatz(int n)
{
	if (n == 1)
		return 0;
	else if ((n % 2) == 0)
		return 1 + collatz(n / 2);
	else
		return 1 + collatz((3 * n) + 1);
}
