#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string input_text = get_string("Text: ");

    int spaces = 0;
    int sentences = 0;
    int shit = 0;
    for (int i = 0, n = strlen(input_text); i < n; i++)
    {
        if (input_text[i] == ' ')
        {
            spaces++; //Counts the number of spaces as proxy for number of words
        }
        if (input_text[i] == '.' || input_text[i] == '!' || input_text[i] == '?')
        {
            sentences++; //Counts the number of punctuations as proxy for number of sentences
        }
        if (input_text[i] == ',' || input_text[i] == ';' || input_text[i] == (char) 39  || input_text[i] == '-')
        {
            shit++; //To stop these characters from being counted as letters
        }
    }

    int letters = strlen(input_text) - spaces - shit - sentences;
    int words = spaces + 1; //Number of words (1 is added accounting the last space that wont be counted)
    float L = (letters / (float) words) * 100; //Average number of letters per 100 words
    float S = (sentences / (float) words) * 100; //Average number of sentences per 100 words
    int index = round(0.0588 * L - 0.296 * S - 15.8); //Coleman-Liau Index

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}