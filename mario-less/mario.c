#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
// For each row
    for (int row = 0; row < height; row++)
    {
        // Introduce spaces to the left
        for (int space = 0; space < height - 1 - row; space++)
        {
            printf(" ");
        }
        // Introduce hashes to the right
        for (int column = 0; column <= row; column++)
        {
            printf("#");
        }
        // Move to next row
        printf("\n");
    }

}
