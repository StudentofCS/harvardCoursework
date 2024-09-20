#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int block;

    // Check for input range of 1-8
    do
    {
        block = get_int("What's the height of the block from 1-8? ");
    }
    while (block < 1 || block > 8);


    int check = block;

    //Loop the code until done
    do
    {
        // Make block - 1 blank spaces per line. Subtracting 1 for each line
        for (int i = check - 1 ; i > 0; i--)
        {
            printf(" ");
        }
        // Make block - (block -1) blocks per line before making a line break. Adding a block each line
        for (int b = check - 1; b < block; b++)
        {
            printf("#");
        }
        printf("\n");
        check--;
    }
    while (check > 0);
}