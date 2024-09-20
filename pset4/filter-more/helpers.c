#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Variable to store the average
    float pixel_average;
    float rgb_total;

    // Get the average of the RGB in each pixel of image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rgb_total = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;

            pixel_average = round(rgb_total / 3);

            image[i][j].rgbtRed = pixel_average;

            image[i][j].rgbtGreen = pixel_average;

            image[i][j].rgbtBlue = pixel_average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary array to store the reverse of image arrays
    RGBTRIPLE temp_array[height][width];

    // Reverse the x-axis of the image to the temp array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_array[i][j] = image[i][width - 1 - j];
        }
    }

    // Copy the reflected image in temp array back to original image
    memcpy(image, temp_array, height * width * sizeof(BYTE) * 3);

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Counter of valid pixels
    int counter;

    // Sum of RGB for all valid pixels
    float r_total;
    float g_total;
    float b_total;

    // Temporary array to store the blurred pixels of image
    RGBTRIPLE temp_array[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset counter and totals of all valid pixels
            counter = 0;
            r_total = 0;
            g_total = 0;
            b_total = 0;

            // Check if pixels surrounding original pixel are valid
            for (int k = i - 1; k < (i + 2); k++)
            {
                for (int l = j - 1; l < (j + 2); l++)
                {
                    // If pixel is valid, add their RGB values and tick the counter
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {

                        r_total += image[k][l].rgbtRed;

                        g_total += image[k][l].rgbtGreen;

                        b_total += image[k][l].rgbtBlue;

                        counter++;
                    }
                }
            }

            // Save the average of all the pixel colors onto the temp array
            temp_array[i][j].rgbtRed = round(r_total / counter);

            temp_array[i][j].rgbtGreen = round(g_total / counter);

            temp_array[i][j].rgbtBlue = round(b_total / counter);
        }
    }

    // Copy the reflected image in temp array back to original image
    memcpy(image, temp_array, height * width * sizeof(BYTE) * 3);

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Sobel algorithm total of RGB for all valid pixels
    float r_total;
    float g_total;
    float b_total;

    // Variables for x and y colors
    float redx;
    float redy;
    float greenx;
    float greeny;
    float bluex;
    float bluey;

    // Temporary array to store the blurred pixels of image
    RGBTRIPLE temp_array[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset all variables
            r_total = 0;
            g_total = 0;
            b_total = 0;

            redx = 0;
            redy = 0;
            greenx = 0;
            greeny = 0;
            bluex = 0;
            bluey = 0;

            // Check if pixels surrounding original pixel are valid
            for (int k = i - 1; k < (i + 2); k++)
            {
                for (int l = j - 1; l < (j + 2); l++)
                {
                    // If pixel is valid, add their weighted RGB
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        // Assign the correct weights for each pixel
                        // Top left pixel on weighted grid
                        if (k == (i - 1) && l == (j - 1))
                        {
                            // Values for Gx grid
                            redx += image[k][l].rgbtRed * -1;
                            greenx += image[k][l].rgbtGreen * -1;
                            bluex += image[k][l].rgbtBlue * -1;

                            // Values for Gy grid
                            redy += image[k][l].rgbtRed * -1;
                            greeny += image[k][l].rgbtGreen * -1;
                            bluey += image[k][l].rgbtBlue * -1;
                        }

                        // Top middle pixel on weighted grid
                        if (k == (i - 1) && l == j)
                        {
                            // Values for Gy grid
                            redy += image[k][l].rgbtRed * -2;
                            greeny += image[k][l].rgbtGreen * -2;
                            bluey += image[k][l].rgbtBlue * -2;
                        }

                        // Top right pixel on weighted grid
                        if (k == (i - 1) && l == (j + 1))
                        {
                            // Values for Gx grid
                            redx += image[k][l].rgbtRed;
                            greenx += image[k][l].rgbtGreen;
                            bluex += image[k][l].rgbtBlue;

                            // Values for Gy grid
                            redy += image[k][l].rgbtRed * -1;
                            greeny += image[k][l].rgbtGreen * -1;
                            bluey += image[k][l].rgbtBlue * -1;
                        }

                        // Middle left pixel on weighted grid
                        if (k == i && l == (j - 1))
                        {
                            // Values for Gx grid
                            redx += image[k][l].rgbtRed * -2;
                            greenx += image[k][l].rgbtGreen * -2;
                            bluex += image[k][l].rgbtBlue * -2;
                        }

                        // Middle right pixel on weighted grid
                        if (k == i && l == (j + 1))
                        {
                            // Values for Gx grid
                            redx += image[k][l].rgbtRed * 2;
                            greenx += image[k][l].rgbtGreen * 2;
                            bluex += image[k][l].rgbtBlue * 2;
                        }

                        // Bottom left pixel on weighted grid
                        if (k == (i + 1) && l == (j - 1))
                        {
                            // Values for Gx grid
                            redx += image[k][l].rgbtRed * -1;
                            greenx += image[k][l].rgbtGreen * -1;
                            bluex += image[k][l].rgbtBlue * -1;

                            // Values for Gy grid
                            redy += image[k][l].rgbtRed;
                            greeny += image[k][l].rgbtGreen;
                            bluey += image[k][l].rgbtBlue;
                        }

                        // Bottom middle pixel on weighted grid
                        if (k == (i + 1) && l == j)
                        {
                            // Values for Gy grid
                            redy += image[k][l].rgbtRed * 2;
                            greeny += image[k][l].rgbtGreen * 2;
                            bluey += image[k][l].rgbtBlue * 2;
                        }

                        // Bottom right pixel on weighted grid
                        if (k == (i + 1) && l == (j + 1))
                        {
                            // Values for Gx grid
                            redx += image[k][l].rgbtRed;
                            greenx += image[k][l].rgbtGreen;
                            bluex += image[k][l].rgbtBlue;

                            // Values for Gy grid
                            redy += image[k][l].rgbtRed;
                            greeny += image[k][l].rgbtGreen;
                            bluey += image[k][l].rgbtBlue;
                        }
                    }
                }
            }

            // Save the average of all the pixel colors onto the temp array
            r_total = round(sqrt(pow(redx, 2) + pow(redy, 2)));

            g_total = round(sqrt(pow(greenx, 2) + pow(greeny, 2)));

            b_total = round(sqrt(pow(bluex, 2) + pow(bluey, 2)));

            // If the variable is greater than 255, make it 255
            if (r_total > 255)
                r_total = 255;

            if (g_total > 255)
                g_total = 255;

            if (b_total > 255)
                b_total = 255;

            // Save the result of the Sobel algorithm for each color onto the temp array
            temp_array[i][j].rgbtRed = r_total;

            temp_array[i][j].rgbtGreen = g_total;

            temp_array[i][j].rgbtBlue = b_total;
        }
    }
    // Copy the reflected image in temp array back to original image
    memcpy(image, temp_array, height * width * sizeof(BYTE) * 3);

    return;
}
