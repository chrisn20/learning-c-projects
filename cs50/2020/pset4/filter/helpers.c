#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE rgbtAverage = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Remember to divide by a float to get a float for rounding
            rgbtAverage = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3.0);
            image[i][j].rgbtBlue = rgbtAverage;
            image[i][j].rgbtGreen = rgbtAverage;
            image[i][j].rgbtRed = rgbtAverage;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaBlue = 0, sepiaGreen = 0, sepiaRed = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // Make sure RGB values don't exceed 255
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ptemp;
    // Only need to repeat for half width
    int x = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < x; j++)
        {
            ptemp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = ptemp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int cells, totalRed, totalBlue, totalGreen;
    RGBTRIPLE box[3][3];

    // Create a copy of the original so that we can reference original values
    RGBTRIPLE imgcopy[height][width];
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            imgcopy[a][b] = image[a][b];
        }
    }

    // Main loop - iterate through all cells in the box array and capture a running total of cells counted and RGB values
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            cells = 0;
            totalRed = 0;
            totalBlue = 0;
            totalGreen = 0;

            // Create a 3x3 array to calculate box blur values - reset array every loop
            for (int k = 0; k < 3; k ++)
            {
                for (int l = 0; l < 3; l ++)
                {
                    box[k][l].rgbtRed = 0;
                    box[k][l].rgbtBlue = 0;
                    box[k][l].rgbtGreen = 0;
                }
            }

            // Loop through all possible surrounding cells and make sure they are part of the image
            // If co-ordinates go out of bounds, it simply skips counting them
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                box[0][0] = imgcopy[i - 1][j - 1];
                cells ++;
                totalRed = totalRed + box[0][0].rgbtRed;
                totalBlue = totalBlue + box[0][0].rgbtBlue;
                totalGreen = totalGreen + box[0][0].rgbtGreen;
            }

            if (i - 1 >= 0)
            {
                box[0][1] = imgcopy[i - 1][j];
                cells ++;
                totalRed = totalRed + box[0][1].rgbtRed;
                totalBlue = totalBlue + box[0][1].rgbtBlue;
                totalGreen = totalGreen + box[0][1].rgbtGreen;
            }

            if (i - 1 >= 0 && j + 1 < width)
            {
                box[0][2] = imgcopy[i - 1][j + 1];
                cells ++;
                totalRed = totalRed + box[0][2].rgbtRed;
                totalBlue = totalBlue + box[0][2].rgbtBlue;
                totalGreen = totalGreen + box[0][2].rgbtGreen;
            }

            if (j - 1 >= 0)
            {
                box[1][0] = imgcopy[i][j - 1];
                cells ++;
                totalRed = totalRed + box[1][0].rgbtRed;
                totalBlue = totalBlue + box[1][0].rgbtBlue;
                totalGreen = totalGreen + box[1][0].rgbtGreen;
            }

            box[1][1] = imgcopy[i][j];
            cells ++;
            totalRed = totalRed + box[1][1].rgbtRed;
            totalBlue = totalBlue + box[1][1].rgbtBlue;
            totalGreen = totalGreen + box[1][1].rgbtGreen;

            if (j + 1 < width)
            {
                box[1][2] = imgcopy[i][j + 1];
                cells ++;
                totalRed = totalRed + box[1][2].rgbtRed;
                totalBlue = totalBlue + box[1][2].rgbtBlue;
                totalGreen = totalGreen + box[1][2].rgbtGreen;
            }

            if (i + 1 < height && j - 1 >= 0)
            {
                box[2][0] = imgcopy[i + 1][j - 1];
                cells ++;
                totalRed = totalRed + box[2][0].rgbtRed;
                totalBlue = totalBlue + box[2][0].rgbtBlue;
                totalGreen = totalGreen + box[2][0].rgbtGreen;
            }

            if (i + 1 < height)
            {
                box[2][1] = imgcopy[i + 1][j];
                cells ++;
                totalRed = totalRed + box[2][1].rgbtRed;
                totalBlue = totalBlue + box[2][1].rgbtBlue;
                totalGreen = totalGreen + box[2][1].rgbtGreen;
            }

            if (i + 1 < height && j + 1 < width)
            {
                box[2][2] = imgcopy[i + 1][j + 1];
                cells ++;
                totalRed = totalRed + box[2][2].rgbtRed;
                totalBlue = totalBlue + box[2][2].rgbtBlue;
                totalGreen = totalGreen + box[2][2].rgbtGreen;
            }

            // Since we kept track of the number of cells, we can use these to get average
            // Remember to round a cast cells as a float
            image[i][j].rgbtRed = round(totalRed / (float) cells);
            image[i][j].rgbtGreen = round(totalGreen / (float) cells);
            image[i][j].rgbtBlue = round(totalBlue / (float) cells);



        }
    }
    return;
}
