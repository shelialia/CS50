#include <stdio.h>
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
}
