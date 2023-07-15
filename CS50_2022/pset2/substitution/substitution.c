#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) 
{
	// Checks whether there are two command line arguments	
	if (argc == 2)
	{		
		// Checks whether the key contains 26 characters
		int len_key =  strlen(argv[1]);
		if (len_key != 26)
		{
			printf("Key must contain 26 characters.\n");
			return 1;
		}
		// Iterates through the key checking for repeat letters and non-alphabetical characters
		for (int i = 0; i < len_key; i++)
		{
			for (int j = i + 1; j < len_key; j++)
			{
				if (toupper(argv[1][i]) == argv[1][j] || tolower(argv[1][i]) == argv[1][j])
				{
					printf("Key should contain every letter exactly one.\n");
					return 1;
				}
				if (isalpha(argv[1][i]) == 0)
				{
					printf("Key should only contain alphabetical letters.\n");
					return 1;
				}
			}
		}
		// Asks user for plaintext and does the substitution for alphabetical letters
		string plaintext = get_string("Plaintext: ");
        int len_plain = strlen(plaintext);
        char ciphertext[len_plain];
		printf("ciphertext: ");
		for (int i = 0; i < len_plain; i++)
		{
			if (isupper(plaintext[i]))
        	{
				int upper = plaintext[i] - 65;
        		ciphertext[i] = toupper(argv[1][upper]);
            	printf("%c", ciphertext[i]);
        	}
        	else if (islower(plaintext[i]))
        	{
				int lower = plaintext[i] - 97; 
        		ciphertext[i] = tolower(argv[1][lower]);
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
		printf("./subtitution key\n");
		return 1;
	}
}
