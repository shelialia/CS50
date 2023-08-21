#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row (Down)
    for (int i = 0; i < height ; i++)
    {
        // In each row, Loop through each column (from left to right)
        for (int j = 0; j < width ; j++)
        {
            // If the pixel is black in colour
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtBlue == 0x00 && image[i][j].rgbtGreen == 0x00)
            {
                // Change it to green colour
                image[i][j].rgbtGreen = 0xFF;
            }
        }
    }

}
