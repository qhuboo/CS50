#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int error = 0;
    if (argc == 2)
    {
        for (int p = 0, l = strlen(argv[1]); p < l; p++)
        {
            if (argv[1][p] >= 'a' && argv[1][p] <= 'z')
            {
                for (int j = p + 1; j < l; j++)
                {
                    if (argv[1][p] == argv[1][j] || argv[1][p] == tolower(argv[1][j]))
                    {
                        error++;
                    }
                    else
                    {
                        ;
                    }
                }
            }
            else if (argv[1][p] >= 'A' && argv[1][p] <= 'Z')
            {
                for (int j = p + 1; j < l; j++)
                {
                    if (argv[1][p] == argv[1][j] || argv[1][p] == toupper(argv[1][j]))
                    {
                        error++;
                    }
                    else
                    {
                        ;
                    }
                }
            }
            else
            {
                error++;
            }
        }
        if (strlen(argv[1]) == 26)
        {
            if (error == 0)
            {
                string plaintext = get_string("plaintext: ");
                for (int i = 0, n = strlen(plaintext); i < n; i++)
                {
                    if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
                    {
                        int lower = plaintext[i] - 97;
                        plaintext[i] = tolower(argv[1][lower]);
                    }
                    else
                    {
                        ;
                    }
                    if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
                    {
                        int upper = plaintext[i] - 65;
                        plaintext[i] = toupper(argv[1][upper]);
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
                printf("./substitution key\n");
                return 1;
            }
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("./substitution key\n");
        return 1;
    }
}