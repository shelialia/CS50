#include "helpers.h"
#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0;  i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            double average_colour = (blue + red + green) / 3.0;
            int average = round(average_colour);
            {
                image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = average;
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalBlue = image[i][j].rgbtBlue;
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;

            double sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            double sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            double sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            {
                image[i][j].rgbtBlue = sepiaBlue;
                image[i][j].rgbtRed = sepiaRed;
                image[i][j].rgbtGreen = sepiaGreen;
            }
        }
    }
    return;
}

// Reflect image horizontally

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every row
    for (int i = 0; i < height ; i++)
    {
        // Loop through every column in each row (ie. every pixel)
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j]; //store the RGB channel if pixel temporarily in tmp
            image[i][j] = image[i][width - j -
                                   1]; //let the current pixel get the RGB channels of the pixel at the other end of the horizontal line
            image[i][width - j - 1] = tmp; //let the other pixel store the value in tmp
        }
    }
    return;
}

// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width]; //make a copy of the pixel and store it temporarily under copy, so that it does not affect blurring of others
    for (int i = 0; i < height; i++) //loop through each row
    {
        for (int j = 0; j < width; j++) //loop through each column, going through each pixel
        {
            copy[i][j] = image[i][j]; //copy the pixel over
        }
    }

    for (int i = 0; i < height; i++) //loop through each row
    {
        for (int j = 0; j < width; j++) //loop through each pixel
        {
            //initialise the sums to zero first, at the beginning of the loop for each pixel
            float sum_red = 0;
            float sum_blue = 0;
            float sum_green = 0;
            int pixel_count = 0;

            //loop through starting from the top left of the 9x9 box of the pixel in subject
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    //reject any pixels if they are not within the boundaries of the picture
                    if (k < 0 || k > height - 1 || l < 0 || l > width - 1)
                    {
                        //don't use break, instead use continue as it allows the loop to increment by one number and skip this iteration
                        continue;
                    }
                    //add the new colour sum to this one
                    sum_red = sum_red + copy[k][l].rgbtRed;
                    sum_blue = sum_blue + copy[k][l].rgbtBlue;
                    sum_green = sum_green + copy[k][l].rgbtGreen;
                    pixel_count++;
                }
            }
            //we divide a float by an integer, thus avoiding the situation of truncation, where we produce an integer that drops any number after decimal
            //since we use the function round, we expect to get an integer finally
            int final_red = round(sum_red / pixel_count);
            int final_blue = round(sum_blue / pixel_count);
            int final_green = round(sum_green / pixel_count);

            //finally, we assign the pixel (not the copied one) in actuality to the new rgb colours we want
            image[i][j].rgbtBlue = final_blue;
            image[i][j].rgbtRed = final_red;
            image[i][j].rgbtGreen = final_green;
        }
    }
    return;
}
