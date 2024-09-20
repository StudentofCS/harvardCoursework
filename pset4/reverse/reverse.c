#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Format: ./reverse input output\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("File %s could not open.\n", argv[1]);
        return 2;
    }

    // Read header
    // TODO #3
    WAVHEADER wheader;

    fread(&wheader, 1, sizeof(WAVHEADER), input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(wheader))
    {
        printf("File is not in a WAV format.\n");
        return 3;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");

    if (output == NULL)
    {
        printf("%s could not open.\n", argv[2]);
        return 4;
    }

    // Write header to file
    // TODO #6
    fwrite(&wheader, 1, sizeof(WAVHEADER), output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(wheader);

    // Write reversed audio to file
    // TODO #8
    int data_size = wheader.subchunk2Size;
    int num_of_blocks = data_size / block_size;
    char *data = malloc(block_size);
    // char *temp_data = malloc(data_size);

    // Set file pointer to end of file
    fseek(input, 0, SEEK_END);

    // Loop that moves point back 1 block size and reads it until all data is read
    for (int i = 0; i < num_of_blocks; i++)
    {
        fseek(input, -block_size, SEEK_CUR);
        fread(data, block_size, 1, input);
        // Reset file pointer to make it ready for the next block to be read
        fseek(input, -block_size, SEEK_CUR);

        // Write data into the output file
        fwrite(data, block_size, 1, output);
    }

    // Deleted after reading instructions on how cs50 wants it to be reversed
    // Loop through the data jumping by block size
    // for (int i = 0; i < data_size;)
    //{
    //    // Loop through the block size byte by byte up to block size
    //    for (int j = 0; j < block_size; j++)
    //        temp_data[i + j] = data[(data_size - i - block_size) + j];
    //
    //    i += block_size;
    //}

    // Close FILEs and release memory
    fclose(input);
    fclose(output);
    free(data);
    // free(temp_data);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    // Variable to test format against
    char wav_test[] = {'W', 'A', 'V', 'E'};

    for (int i = 0; i < sizeof(header.format); i++)
    {
        if (header.format[i] != wav_test[i])
            return 0;
    }

    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.blockAlign;
}