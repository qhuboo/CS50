#include <stdio.h>

int main(void)
{
	FILE *ptr = fopen("file.txt", "r");
	char ch;
	while ((ch = fgetc(ptr)) != EOF);
	{
		printf("%c", ch);	
	}
	printf("\n");
}	
