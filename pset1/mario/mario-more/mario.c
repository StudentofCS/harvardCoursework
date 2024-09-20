#include <cs50.h>
#include <stdio.h>

// Stating function build
bool build(int height);


int main(void)
{
    // Obtain height from user between 1 and 8, inclusive.
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Input height into build function
    build(height);
}

// Build function will create two mirrored pyramids with a double space inbetween that has the height the same size as base

bool build(int height)
{
    int high = height;
    int base = height;

    do
    {
        // Start with height - 1 spaces per line, and decrease until zero
        for (int i = base - 1; i > 0; i--)
        {
            printf(" ");
        }
        // Start with 1 block and increase until height # of blocks per line
        for (int j = base - 1; j < high; j++)
        {
            printf("#");
        }
        // Double space gap between pyramids
        printf("  ");
        // Start with 1 block and increase until height # of blocks per line
        for (int k = base - 1; k < high; k++)
        {
            printf("#");
        }
        printf("\n");
        base--;
    }
    while (base > 0);

    return true;
}
