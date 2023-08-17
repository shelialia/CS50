#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    // Make sure every character in argv[1] is a digit
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key");
            return 1;
        }
    }

// Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

// Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");

    {
        for (int j = 0; j < strlen(plaintext); j++)
        {
            // For each character in the plaintext:
            if (isupper(plaintext[j]))
            {
                printf("%c", (((plaintext[j] - 65 + key) % 26) + 65));
            }

            // Rotate the character if it's a letter
            if (islower(plaintext[j]))
            {
                printf("%c", (((plaintext[j] - 97 + key) % 26) + 97));
            }
            else if (!isalpha(plaintext[j]))
            {
                printf("%c", plaintext[j]);
            }
        }
        printf("\n");
    }

}
