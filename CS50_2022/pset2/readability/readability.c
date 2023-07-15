#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) 
{
	string text = get_string("Text: ");
	int len = strlen(text); // Length of the text string
	// Calculate the number of letters, words, and sentences
	int non_letters = 0, words = 0, sentences = 0;
	for (int i = 0; i < len; i++)
	{
		if (text[i] == ' ' || text[i] == '.' || text[i] == '!' || text[i] == '?' || text[i] == ',' || text[i] == (char) 39)
		{
			non_letters++; // Counts the number of spaces and punctuations to delete them from the letter count
		}
		if (text[i] == ' ' || (text[i] == '.' && text[i + 1] != ' ') || (text[i] == '!' && text[i + 1] != ' ') || (text[i] == '?' && text[i + 1] != ' '))
		{
			words++;
		}
		if (text[i] == '.' || text[i] == '!' || text[i] == '?')
		{
			sentences++;
		}
	}
	int letters = len - non_letters;
	// Calculating the Coleman-Liau index
	float L =  letters * (100.0 / words);
	float S = sentences * (100.0 / words);
	float cl_index = (0.0588 * L) - (0.296 * S) - 15.8;
	// Printing the Coleman-Liau Index
	if (cl_index > 15)	
	{
		printf("Grade 16+\n");
	}
	else if (cl_index < 1)
	{
		printf("Before Grade 1\n");
	}
	else
	{
		printf("Grade %i\n", (int) round(cl_index));
	}
}
