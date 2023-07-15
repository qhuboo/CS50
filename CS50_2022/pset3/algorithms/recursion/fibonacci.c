// This program illustrates recursive functions by implementing a fibonacci sequence term generator
#include <stdio.h>

int fibonacci(int n);

int main(void)
{
	// Number of terms to print
	int s = 10;
	for (int i = 0; i < s; i++)
	{
		printf("%i\n", fibonacci(i));
	}
}

int fibonacci(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return fibonacci(n - 1) + fibonacci(n - 2);
}
