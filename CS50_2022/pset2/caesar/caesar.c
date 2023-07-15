#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_number(string s);
char rotate(char c, int k);

int main(int argc, string argv[]) 
{
	if (argc == 2 && is_number(argv[1]))
	{
		int key = atoi(argv[1]);
		string plaintext = get_string("plaintext:  ");
		int len = strlen(plaintext);
		char ciphertext [len];
		printf("ciphertext: ");
		// Rotation
		for (int i = 0; i < len; i++)   
		{       
			// Only rotates alphabetical characters
			if (isalpha(plaintext[i]))
			{
				ciphertext[i] = rotate(plaintext[i], key);
				printf("%c", ciphertext[i]);
			}
			else
			{
				ciphertext[i] = plaintext[i];
				printf("%c", ciphertext[i]);
			}
        }
		printf("\n");
	}
	else
	{
		printf("./caesar key\n");
		return 1;
	}
}

// Checks whether a string is all numbers
int is_number(string s)
{	
	// Defaults to true(1) and iterates through the string and returns false(0)
	// as soon as a non digit number is detected in the string 	
	int check = 1;
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		if (isdigit(s[i]) == 0)
		{
			return 0;
		}
	}
	return check;		
}

// Rotates letters k letters and wraps around
char rotate(char c, int k)
{
	if (isupper(c))
	{
		int upper = ((int) c - 'A' + k) % 26;
		return 'A' + upper;
	}
	else
	{
		int lower = ((int) c - 'a' + k) % 26;
		return 'a' + lower;
	}
}
