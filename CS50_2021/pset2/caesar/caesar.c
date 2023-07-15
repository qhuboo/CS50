#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    int error = 0; //The number of key characters that are not decimal digits
    if (argc == 2)
    {
        for (int p = 0, l = strlen(argv[1]); p < l; p++)
        {
            if (argv[1][p] >= 48 && argv[1][p] <= 57)
            {
                ;
            }
            else
            {
                error++;
            }
        }
        if (error == 0)
        {
            string plaintext = get_string("plaintext: ");
            for (int i = 0, n = strlen(plaintext); i < n; i++)
            {
                if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
                {
                    int lower = plaintext[i] - 97;
                    lower = (lower + atoi(argv[1])) % 26;
                    plaintext[i] = (char)(97 + lower);
                }
                else
                {
                    ;
                }
                if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
                {
                    int upper = plaintext[i] - 65;
                    upper = (upper + atoi(argv[1])) % 26;
                    plaintext[i] = (char)(65 + upper);
                }
                else
                {
                    ;
                }
            }
            printf("ciphertext: %s\n", plaintext);
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}