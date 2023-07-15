#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculating the average value of all three colors and setting each pixel to that value
            int average =  round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
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
            // Storing the original values before manipulation
            uint8_t originalRed = image[i][j].rgbtRed;
            uint8_t originalBlue = image[i][j].rgbtBlue;
            uint8_t originalGreen = image[i][j].rgbtGreen;
            // Calculating sepia values and storing them in an uint16_t to avoid integer overflow
            // when detecting a value greater than 255
            uint16_t sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            uint16_t sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            uint16_t sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            // Checking for values greater than 255 and capping them at 255
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            // Setting each pixel to sepia values
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Calculates up to what value the row pixels will switch
    // If width is even then switch every row pixel
    int width_t;
    if (fmod(width, 2) == 0)
    {
        width_t = round(width / 2.0);
    }
    // If width is odd then switch every row pixel except the middle one
    else
    {
        width_t = (width / 2.0) - 0.5;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width_t; j++)
        {
            // Swap values
            uint8_t tmpBlue = image[i][j].rgbtBlue;
            uint8_t tmpGreen = image[i][j].rgbtGreen;
            uint8_t tmpRed = image[i][j].rgbtRed;

            // Here 1 is subtracted from width since the last index of an array is array size - 1
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;

            image[i][width - 1 - j].rgbtBlue = tmpBlue;
            image[i][width - 1 - j].rgbtGreen = tmpGreen;
            image[i][width - 1 - j].rgbtRed = tmpRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    float average_blue, average_green, average_red;
    float sum_blue, sum_green, sum_red, divisor;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize and then reset all sums and counter
            sum_blue = 0, sum_green = 0, sum_red = 0, divisor = 0;
            average_blue = 0, average_green = 0, average_red = 0;
            // Square 1
            if ((i - 1) >= 0 && (j - 1) >= 0)
            {
                sum_blue += copy[i - 1][j - 1].rgbtBlue;
                sum_green += copy[i - 1][j - 1].rgbtGreen;
                sum_red += copy[i - 1][j - 1].rgbtRed;
                divisor++;
            }
            // Square 2
            if ((i - 1) >= 0)
            {
                sum_blue += copy[i - 1][j].rgbtBlue;
                sum_green += copy[i - 1][j].rgbtGreen;
                sum_red += copy[i - 1][j].rgbtRed;
                divisor++;
            }
            // Square 3
            if ((i - 1) >= 0 && (j + 1) < width)
            {
                sum_blue += copy[i - 1][j + 1].rgbtBlue;
                sum_green += copy[i - 1][j + 1].rgbtGreen;
                sum_red += copy[i - 1][j + 1].rgbtRed;
                divisor++;
            }
            // Square 4
            if ((j - 1) >= 0)
            {
                sum_blue += copy[i][j - 1].rgbtBlue;
                sum_green += copy[i][j - 1].rgbtGreen;
                sum_red += copy[i][j - 1].rgbtRed;
                divisor++;
            }
            // Square 5
            if (1)
            {
                sum_blue += copy[i][j].rgbtBlue;
                sum_green += copy[i][j].rgbtGreen;
                sum_red += copy[i][j].rgbtRed;
                divisor++;
            }
            // Square 6
            if ((j + 1) < width)
            {
                sum_blue += copy[i][j + 1].rgbtBlue;
                sum_green += copy[i][j + 1].rgbtGreen;
                sum_red += copy[i][j + 1].rgbtRed;
                divisor++;
            }
            //Square 7
            if ((i + 1) < height && (j - 1) >= 0)
            {
                sum_blue += copy[i + 1][j - 1].rgbtBlue;
                sum_green += copy[i + 1][j - 1].rgbtGreen;
                sum_red += copy[i + 1][j - 1].rgbtRed;
                divisor++;
            }
            //Square 8
            if ((i + 1) < height)
            {
                sum_blue += copy[i + 1][j].rgbtBlue;
                sum_green += copy[i + 1][j].rgbtGreen;
                sum_red += copy[i + 1][j].rgbtRed;
                divisor++;
            }
            //Square 9
            if ((i + 1) < height && (j + 1) < width)
            {
                sum_blue += copy[i + 1][j + 1].rgbtBlue;
                sum_green += copy[i + 1][j + 1].rgbtGreen;
                sum_red += copy[i + 1][j + 1].rgbtRed;
                divisor++;
            }

            // Calculate the averages of each color
            average_blue = round(sum_blue / divisor);
            average_green = round(sum_green / divisor);
            average_red = round(sum_red / divisor);

            // Set the current pixel to those averages
            image[i][j].rgbtBlue = average_blue;
            image[i][j].rgbtGreen = average_green;
            image[i][j].rgbtRed = average_red;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    // Initializing Gx variables
    float gx_sum_blue, gx_sum_green, gx_sum_red;
    // Initializing Gy variables
    float gy_sum_blue, gy_sum_green, gy_sum_red;
    // Initializing Final Sums representing sqrt(Gx^2 + Gy^2)
    float final_sum_blue, final_sum_green, final_sum_red;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset all Gx variables
            gx_sum_blue = 0, gx_sum_green = 0, gx_sum_red = 0;
            // Reset all Gy variables
            gy_sum_blue = 0, gy_sum_green = 0, gy_sum_red = 0;
            // Reset all final sums
            final_sum_blue = 0, final_sum_green = 0, final_sum_red = 0;

            // Square 1
            if ((i - 1) >= 0 && (j - 1) >= 0)
            {
                // Calculate Gx
                gx_sum_blue += copy[i - 1][j - 1].rgbtBlue * -1;
                gx_sum_green += copy[i - 1][j - 1].rgbtGreen * -1;
                gx_sum_red += copy[i - 1][j - 1].rgbtRed * -1;

                // Calculate Gy
                gy_sum_blue += copy[i - 1][j - 1].rgbtBlue * -1;
                gy_sum_green += copy[i - 1][j - 1].rgbtGreen * -1;
                gy_sum_red += copy[i - 1][j - 1].rgbtRed * -1;
            }
            // Square 2
            if ((i - 1) >= 0)
            {
                // Calculate Gx
                gx_sum_blue += copy[i - 1][j].rgbtBlue * 0;
                gx_sum_green += copy[i - 1][j].rgbtGreen * 0;
                gx_sum_red += copy[i - 1][j].rgbtRed * 0;

                // Calculate Gy
                gy_sum_blue += copy[i - 1][j].rgbtBlue * -2;
                gy_sum_green += copy[i - 1][j].rgbtGreen * -2;
                gy_sum_red += copy[i - 1][j].rgbtRed * -2;
            }
            // Square 3
            if ((i - 1) >= 0 && (j + 1) < width)
            {
                // Calculate Gx
                gx_sum_blue += copy[i - 1][j + 1].rgbtBlue * 1;
                gx_sum_green += copy[i - 1][j + 1].rgbtGreen * 1;
                gx_sum_red += copy[i - 1][j + 1].rgbtRed * 1;

                // Calculate Gy
                gy_sum_blue += copy[i - 1][j + 1].rgbtBlue * -1;
                gy_sum_green += copy[i - 1][j + 1].rgbtGreen * -1;
                gy_sum_red += copy[i - 1][j + 1].rgbtRed * -1;
            }
            // Square 4
            if ((j - 1) >= 0)
            {
                // Calculate Gx
                gx_sum_blue += copy[i][j - 1].rgbtBlue * -2;
                gx_sum_green += copy[i][j - 1].rgbtGreen * -2;
                gx_sum_red += copy[i][j - 1].rgbtRed * -2;

                // Calculate Gy
                gy_sum_blue += copy[i][j - 1].rgbtBlue * 0;
                gy_sum_green += copy[i][j - 1].rgbtGreen * 0;
                gy_sum_red += copy[i][j - 1].rgbtRed * 0;
            }
            // Square 5
            if (1)
            {
                // Calculate Gx
                gx_sum_blue += copy[i][j].rgbtBlue * 0;
                gx_sum_green += copy[i][j].rgbtGreen * 0;
                gx_sum_red += copy[i][j].rgbtRed * 0;

                // Calculate Gy
                gy_sum_blue += copy[i][j].rgbtBlue * 0;
                gy_sum_green += copy[i][j].rgbtGreen * 0;
                gy_sum_red += copy[i][j].rgbtRed * 0;
            }
            // Square 6
            if ((j + 1) < width)
            {
                // Calculate Gx
                gx_sum_blue += copy[i][j + 1].rgbtBlue * 2;
                gx_sum_green += copy[i][j + 1].rgbtGreen * 2;
                gx_sum_red += copy[i][j + 1].rgbtRed * 2;

                // Calculate Gy
                gy_sum_blue += copy[i][j + 1].rgbtBlue * 0;
                gy_sum_green += copy[i][j + 1].rgbtGreen * 0;
                gy_sum_red += copy[i][j + 1].rgbtRed * 0;
            }
            //Square 7
            if ((i + 1) < height && (j - 1) >= 0)
            {
                // Calculate Gx
                gx_sum_blue += copy[i + 1][j - 1].rgbtBlue * -1;
                gx_sum_green += copy[i + 1][j - 1].rgbtGreen * -1;
                gx_sum_red += copy[i + 1][j - 1].rgbtRed * -1;

                // Calculate Gy
                gy_sum_blue += copy[i + 1][j - 1].rgbtBlue * 1;
                gy_sum_green += copy[i + 1][j - 1].rgbtGreen * 1;
                gy_sum_red += copy[i + 1][j - 1].rgbtRed * 1;
            }
            //Square 8
            if ((i + 1) < height)
            {
                // Calculate Gx
                gx_sum_blue += copy[i + 1][j].rgbtBlue * 0;
                gx_sum_green += copy[i + 1][j].rgbtGreen * 0;
                gx_sum_red += copy[i + 1][j].rgbtRed * 0;

                // Calculate Gy
                gy_sum_blue += copy[i + 1][j].rgbtBlue * 2;
                gy_sum_green += copy[i + 1][j].rgbtGreen * 2;
                gy_sum_red += copy[i + 1][j].rgbtRed * 2;
            }
            //Square 9
            if ((i + 1) < height && (j + 1) < width)
            {
                // Calculate Gx
                gx_sum_blue += copy[i + 1][j + 1].rgbtBlue * 1;
                gx_sum_green += copy[i + 1][j + 1].rgbtGreen * 1;
                gx_sum_red += copy[i + 1][j + 1].rgbtRed * 1;

                // Calculate Gy
                gy_sum_blue += copy[i + 1][j + 1].rgbtBlue * 1;
                gy_sum_green += copy[i + 1][j + 1].rgbtGreen * 1;
                gy_sum_red += copy[i + 1][j + 1].rgbtRed * 1;
            }

            final_sum_blue = round(sqrt((gx_sum_blue * gx_sum_blue) + (gy_sum_blue * gy_sum_blue)));
            final_sum_green = round(sqrt((gx_sum_green * gx_sum_green) + (gy_sum_green * gy_sum_green)));
            final_sum_red = round(sqrt((gx_sum_red * gx_sum_red) + (gy_sum_red * gy_sum_red)));
            
            if (final_sum_blue > 255)
            {
                final_sum_blue = 255;
            }
            if (final_sum_green > 255)
            {
                final_sum_green = 255;
            }
            if (final_sum_red > 255)
            {
                final_sum_red = 255;
            }

            // Set the current pixel to those averages
            image[i][j].rgbtBlue = final_sum_blue;
            image[i][j].rgbtGreen = final_sum_green;
            image[i][j].rgbtRed = final_sum_red;
        }
    }
    return;
}