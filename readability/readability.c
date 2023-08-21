#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // initialise the vairables to an assigned number, words is to 1 because in a sentence, number of words is spaces+1
    int letters = 0;
    int words = 1;
    int sentences = 0;

    // get the text to be input from the user
    string text = get_string("Text: ");

    // create a loop that sieves through every letter in the word
    for (int i = 0; i < strlen(text); i++)
    {
        // using cs50 manual code, if the char is an alphabet, increase letters by one number. text[i] has to have brackets around it because text itself is a string but isalpha only takes in chars
        if (isalpha(text[i]))
        {
            letters++;
        }
        // if a space is detected, 2 spaces means one word is found, increase no. of words by one
        else if (text[i] == ' ')
        {
            words++;
        }
        // end of a sentence has these punctuations.
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

// because int/int gives u an int but in this case we want more precise values ie. a float, so we make either variable a float
    float L =  letters / (float) words * 100;
    float S = sentences / (float) words * 100;

// add the function round in front of the number to be rounded off!!! put the number in brackets
    int index = round(0.0588 * L - 0.296 * S - 15.8);

// just fulfil the instructions given by cs50, rmbr to enter to a new line, if and else if and while loop does not require an ;
    if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
