#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    //Check if the user input is 2 words long
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //Ensure that forensic image opened is valid
    //Open forensic image file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error: Forensic image not found\n");
        return 1;
    }

    typedef uint8_t BYTE;
    BYTE buffer[512];
    int BLOCK_SIZE = 512;
    int i = 0;
    char outfilename[10];
    FILE *outfile = NULL;

//Read the file until the end of the memory card
//Read 512 bytes into the buffer


    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // if it is the start of a new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if it is not the first jpeg we have found, then we close the outfile from previous loops run
            if (i != 0)
            {
                fclose(outfile);
            }
            //regardless, we generate a new file name
            sprintf(outfilename, "%03i.jpg", i);
            // open new file, allow file to be written to with "w"
            outfile = fopen(outfilename, "w");
            // if there is nothing in the file, we close it
            if (outfile == NULL)
            {
                fclose(outfile);
                return 1;
            }

            // write bytes to a file. copying the file data over
            fwrite(buffer, BLOCK_SIZE, 1, outfile);
            i++;
        }

        // if this jpeg has been found before, we keep writing into it
        else if (i != 0)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outfile);

        }
    }
    // close the files
    fclose(file);
    fclose(outfile);
    return 0;
}
