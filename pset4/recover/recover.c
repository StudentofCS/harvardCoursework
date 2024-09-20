#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check if two inputs were made
    if (argc != 2)
    {
        printf("The correct format is: ./recover [forensic image]\n");
        return 1;
    }

    // Open file and ensure it is a valid file
    FILE *fimage = fopen(argv[1], "r");

    if (fimage == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    // Create a buffer of block_size
    int block_size = 512;
    unsigned char buffer[block_size];

    // Counter variable for naming JPGs
    int counter = 0;
    char output[8];

    // Unsigned char variable to compare 0xe to the first 4 digits in the 4th byte
    unsigned char jpg_byte1 = 0xff;
    unsigned char jpg_byte2 = 0xd8;
    unsigned char jpg_byte3 = 0xff;
    unsigned char jpg_byte4 = 0xe;
    unsigned char first_4_bits;

    // Create jpg file but don't assign yet
    FILE *jpg = NULL;

    while (fread(&buffer, 1, block_size, fimage) == block_size)
    {
        // Checks if signature for the start of a new jpeg is found
        first_4_bits = buffer[3] >> 4;
        if ((jpg_byte1 & buffer[0]) == jpg_byte1 && (jpg_byte2 & buffer[1]) == jpg_byte2 && (jpg_byte3 & buffer[2]) == jpg_byte3 &&
            (jpg_byte4 & first_4_bits) == jpg_byte4)
        {
            // If there is an open jpg file already, close it and start a new one
            if (jpg != NULL)
            {
                fclose(jpg);
                jpg = NULL;
            }

            // Add counter total to the filename
            sprintf(output, "%03d.jpg", counter);

            // Increase counter for the next jpg file name
            counter++;

            // Open new file with correct naming convention. Copy buffer.
            jpg = fopen(output, "a");

            if (jpg == NULL)
            {
                printf("JPG is null when trying to open.\n");
                return 3;
            }

            fwrite(buffer, 1, block_size, jpg);
        }
        // If there's an open jpg file and no new file signature, continue to copy buffer
        else if (jpg != NULL)
            fwrite(buffer, 1, block_size, jpg);
    }

    // Close files
    fclose(fimage);
    fclose(jpg);
    return 0;
}