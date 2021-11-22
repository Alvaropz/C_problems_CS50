#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // In this function, we add the value of each color (RGB) to a variable from a pixel. Then, divide that number by 3. So we will get the average of that number. Why? Because we need a scale from black to white, the only way to get that value is equalizing the value of each colour to an average. We have to use a float number to get the most precise number. Then, we round it ot get an integer between 0 and 255.
    float avergGrey; 
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            avergGrey = image[h][w].rgbtRed + image[h][w].rgbtBlue + image[h][w].rgbtGreen;
            image[h][w].rgbtRed = round(avergGrey / 3);
            image[h][w].rgbtBlue = round(avergGrey / 3);
            image[h][w].rgbtGreen = round(avergGrey / 3);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
//For the sepia function, we need to use a specific formula to get the brown tone for each color. We need to take each colour and multiply by a specific number, then we add the amount to the other colours. In this case, we might have a number over 255 (which is out of the scale). So we have to tell the program if that happens, set the value to 255 as maximum number we can have.
    float sepiaRed, sepiaBlue, sepiaGreen;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtBlue = sepiaBlue;
            image[h][w].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
// For the reflection function, we need to copy the all values RBG for each pixel of the whole image for the current row in an array. Why? Because we can take those values to modify the original image. Otherwise, we would take the values of the original image and we would modify them over the same image, which would change the values of the original image.
    int arrayLeftRightRed[width];
    int arrayLeftRightBlue[width];
    int arrayLeftRightGreen[width];
    int indexC;
    for (int h = 0; h < height; h++)
    {
        for (int lr = width - 1; lr > -1; lr--)
// First, we copy the values from right to the left in a new array.
        {
            arrayLeftRightRed[lr] = image[h][lr].rgbtRed;
            arrayLeftRightBlue[lr] = image[h][lr].rgbtBlue;
            arrayLeftRightGreen[lr] = image[h][lr].rgbtGreen;
        }
        indexC = width - 1; // Then, we set the index for the width because we are only changing every row.
        for (int w = 0; w < width; w++) 
// Then, we transform the row taking the values from the copied image in the second array and we set those values in the original one.
        {
            image[h][w].rgbtRed = arrayLeftRightRed[indexC];
            image[h][w].rgbtBlue = arrayLeftRightBlue[indexC];
            image[h][w].rgbtGreen = arrayLeftRightGreen[indexC];
            indexC = indexC - 1; 
// Of course, we have to change the index for that row, otherwise, we would always change the first value in that row.
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
// We create three float variables for the average of each colour of that pixel.
    float avergRed, avergBlue, avergGreen;
// Then, we have to create three arrays, one for each color in every pixel in the image, from left to right ant top to the bottom.
    float arrayWHRed[height][width];
    float arrayWHBlue[height][width];
    float arrayWHGreen[height][width];
// Then, we copy each colour value in the new arrays so we will know what values we have to modify later on in the original image.
    for (int al = 0; al < height; al++)
    {
        for (int an = 0; an < width; an++)
        {
            arrayWHRed[al][an] = image[al][an].rgbtRed;
            arrayWHBlue[al][an] = image[al][an].rgbtBlue;
            arrayWHGreen[al][an] = image[al][an].rgbtGreen;
        }
    }
// And here, we have to be careful because we must be aware about all exceptions in this function. Which are the four pixels in each corner (They have only 4 pixels to compare), the pixels on the rows top and bottom and columns left and righ (They have only 6 pixels to compare), and lastly all pixels in the inside square of the image (They have 9 pixels to compare with).
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (w == 0 && h == 0) // First pixel of the image.
            {
                avergRed = arrayWHRed[h][w] + arrayWHRed[h][w + 1] + arrayWHRed[h + 1][w] + arrayWHRed[h + 1][w + 1];
                avergBlue = arrayWHBlue[h][w] + arrayWHBlue[h][w + 1] + arrayWHBlue[h + 1][w] + arrayWHBlue[h + 1][w + 1];
                avergGreen = arrayWHGreen[h][w] + arrayWHGreen[h][w + 1] + arrayWHGreen[h + 1][w] + arrayWHGreen[h + 1][w + 1];
                image[h][w].rgbtRed = round(avergRed / 4);
                image[h][w].rgbtBlue = round(avergBlue / 4);
                image[h][w].rgbtGreen = round(avergGreen / 4);
            }
            if (w == width - 1 && h == 0) // Last pixel of the image in the first row.
            {
                avergRed = arrayWHRed[h][w] + arrayWHRed[h][w - 1] + arrayWHRed[h + 1][w] + arrayWHRed[h + 1][w - 1];
                avergBlue = arrayWHBlue[h][w] + arrayWHBlue[h][w - 1] + arrayWHBlue[h + 1][w] + arrayWHBlue[h + 1][w - 1];
                avergGreen = arrayWHGreen[h][w] + arrayWHGreen[h][w - 1] + arrayWHGreen[h + 1][w] + arrayWHGreen[h + 1][w - 1];
                image[h][w].rgbtRed = round(avergRed / 4);
                image[h][w].rgbtBlue = round(avergBlue / 4);
                image[h][w].rgbtGreen = round(avergGreen / 4);
            }
            if ((w > 0 && w < width - 1) && h == 0) // Any pixel of the first row which is not the first or the last one.
            {
                avergRed = arrayWHRed[h][w] + arrayWHRed[h][w - 1] + arrayWHRed[h][w + 1] + arrayWHRed[h + 1][w - 1] + arrayWHRed[h + 1][w] +
                           arrayWHRed[h + 1][w + 1];
                avergBlue = arrayWHBlue[h][w] + arrayWHBlue[h][w - 1] + arrayWHBlue[h][w + 1] + arrayWHBlue[h + 1][w - 1] + arrayWHBlue[h + 1][w] +
                            arrayWHBlue[h + 1][w + 1];
                avergGreen = arrayWHGreen[h][w] + arrayWHGreen[h][w - 1] + arrayWHGreen[h][w + 1] + arrayWHGreen[h + 1][w - 1] +
                             arrayWHGreen[h + 1][w] + arrayWHGreen[h + 1][w + 1];
                image[h][w].rgbtRed = round(avergRed / 6);
                image[h][w].rgbtBlue = round(avergBlue / 6);
                image[h][w].rgbtGreen = round(avergGreen / 6);
            }
            if (w == 0 && (h > 0 && h < height - 1)) // Any pixel of the first column which is not the first or the last one.
            {
                avergRed = arrayWHRed[h][w] + arrayWHRed[h - 1][w] + arrayWHRed[h + 1][w] + arrayWHRed[h - 1][w + 1] + arrayWHRed[h][w + 1] +
                           arrayWHRed[h + 1][w + 1];
                avergBlue = arrayWHBlue[h][w] + arrayWHBlue[h - 1][w] + arrayWHBlue[h + 1][w] + arrayWHBlue[h - 1][w + 1] + arrayWHBlue[h][w + 1] +
                            arrayWHBlue[h + 1][w + 1];
                avergGreen = arrayWHGreen[h][w] + arrayWHGreen[h - 1][w] + arrayWHGreen[h + 1][w] + arrayWHGreen[h - 1][w + 1] + arrayWHGreen[h][w +
                             1] + arrayWHGreen[h + 1][w + 1];
                image[h][w].rgbtRed = round(avergRed / 6);
                image[h][w].rgbtBlue = round(avergBlue / 6);
                image[h][w].rgbtGreen = round(avergGreen / 6);
            }
            if ((w > 0 && w < width - 1) && (h > 0 && h < height - 1)) 
// Any pixel in the square inside of the image, in other words, any pixel which doesn't belong to the border.
            {
                avergRed = arrayWHRed[h][w] + arrayWHRed[h - 1][w - 1] + arrayWHRed[h - 1][w] + arrayWHRed[h - 1][w + 1] + arrayWHRed[h][w - 1] +
                           arrayWHRed[h][w + 1] + arrayWHRed[h + 1][w - 1] + arrayWHRed[h + 1][w] + arrayWHRed[h + 1][w + 1];
                avergBlue = arrayWHBlue[h][w] + arrayWHBlue[h - 1][w - 1] + arrayWHBlue[h - 1][w] + arrayWHBlue[h - 1][w + 1] + arrayWHBlue[h][w -
                            1] + arrayWHBlue[h][w + 1] + arrayWHBlue[h + 1][w - 1] + arrayWHBlue[h + 1][w] + arrayWHBlue[h + 1][w + 1];
                avergGreen = arrayWHGreen[h][w] + arrayWHGreen[h - 1][w - 1] + arrayWHGreen[h - 1][w] + arrayWHGreen[h - 1][w + 1] +
                             arrayWHGreen[h][w - 1] + arrayWHGreen[h][w + 1] + arrayWHGreen[h + 1][w - 1] + arrayWHGreen[h + 1][w] + arrayWHGreen[h + 1][w + 1];
                image[h][w].rgbtRed = round(avergRed / 9);
                image[h][w].rgbtBlue = round(avergBlue / 9);
                image[h][w].rgbtGreen = round(avergGreen / 9);
            }
            if (w == width - 1 && (h > 0 && h < height - 1)) // Any pixel of the last column which is not the first or the last one.
            {
                avergRed = arrayWHRed[h][w] + arrayWHRed[h - 1][w] + arrayWHRed[h + 1][w] + arrayWHRed[h - 1][w - 1] + arrayWHRed[h][w - 1] +
                           arrayWHRed[h + 1][w - 1];
                avergBlue = arrayWHBlue[h][w] + arrayWHBlue[h - 1][w] + arrayWHBlue[h + 1][w] + arrayWHBlue[h - 1][w - 1] + arrayWHBlue[h][w - 1] +
                            arrayWHBlue[h + 1][w - 1];
                avergGreen = arrayWHGreen[h][w] + arrayWHGreen[h - 1][w] + arrayWHGreen[h + 1][w] + arrayWHGreen[h - 1][w - 1] + arrayWHGreen[h][w -
                             1] + arrayWHGreen[h + 1][w - 1];
                image[h][w].rgbtRed = round(avergRed / 6);
                image[h][w].rgbtBlue = round(avergBlue / 6);
                image[h][w].rgbtGreen = round(avergGreen / 6);
            }
            if ((w > 0 && w < width - 1) && h == height - 1) // Any pixel of the last row which is not the first or the last one.
            {
                avergRed = arrayWHRed[h][w] + arrayWHRed[h][w - 1] + arrayWHRed[h][w + 1] + arrayWHRed[h - 1][w - 1] + arrayWHRed[h - 1][w] +
                           arrayWHRed[h - 1][w + 1];
                avergBlue = arrayWHBlue[h][w] + arrayWHBlue[h][w - 1] + arrayWHBlue[h][w + 1] + arrayWHBlue[h - 1][w - 1] + arrayWHBlue[h - 1][w] +
                            arrayWHBlue[h - 1][w + 1];
                avergGreen = arrayWHGreen[h][w] + arrayWHGreen[h][w - 1] + arrayWHGreen[h][w + 1] + arrayWHGreen[h - 1][w - 1] + arrayWHGreen[h -
                             1][w] + arrayWHGreen[h - 1][w + 1];
                image[h][w].rgbtRed = round(avergRed / 6);
                image[h][w].rgbtBlue = round(avergBlue / 6);
                image[h][w].rgbtGreen = round(avergGreen / 6);
            }
            if (w == 0 && h == height - 1) // First pixel of the imagen in the last row.
            {
                avergRed = arrayWHRed[h][w] + arrayWHRed[h][w + 1] + arrayWHRed[h - 1][w] + arrayWHRed[h - 1][w + 1];
                avergBlue = arrayWHBlue[h][w] + arrayWHBlue[h][w + 1] + arrayWHBlue[h - 1][w] + arrayWHBlue[h - 1][w + 1];
                avergGreen = arrayWHGreen[h][w] + arrayWHGreen[h][w + 1] + arrayWHGreen[h - 1][w] + arrayWHGreen[h - 1][w + 1];
                image[h][w].rgbtRed = round(avergRed / 4);
                image[h][w].rgbtBlue = round(avergBlue / 4);
                image[h][w].rgbtGreen = round(avergGreen / 4);
            }
            if (w == width - 1 && h == height - 1) // Last pixel of the image.
            {
                avergRed = arrayWHRed[h][w] + arrayWHRed[h][w - 1] + arrayWHRed[h - 1][w] + arrayWHRed[h - 1][w - 1];
                avergBlue = arrayWHBlue[h][w] + arrayWHBlue[h][w - 1] + arrayWHBlue[h - 1][w] + arrayWHBlue[h - 1][w - 1];
                avergGreen = arrayWHGreen[h][w] + arrayWHGreen[h][w - 1] + arrayWHGreen[h - 1][w] + arrayWHGreen[h - 1][w - 1];
                image[h][w].rgbtRed = round(avergRed / 4);
                image[h][w].rgbtBlue = round(avergBlue / 4);
                image[h][w].rgbtGreen = round(avergGreen / 4);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
// Variables created to store the X and Y values for the grid for each colour.
    float GxR, GyR, GxB, GyB, GxG, GyG;
// Variable created to put together the values X and Y in a single variable.
    float FGxyR, FGxyB, FGxyG;
// Arrays created to store all values for the Height and the Width for all colours.
    float arrayWHRed[height][width];
    float arrayWHBlue[height][width];
    float arrayWHGreen[height][width];
// First, we copy the three colour values of the whole image for its Height and Width.
    for (int al = 0; al < height; al++)
    {
        for (int an = 0; an < width; an++)
        {
            arrayWHRed[al][an] = image[al][an].rgbtRed;
            arrayWHBlue[al][an] = image[al][an].rgbtBlue;
            arrayWHGreen[al][an] = image[al][an].rgbtGreen;
        }
    }
// Here, we started modifying the original values with the information of the Sobel operator.
// It's improtant to say that for the edges and the corners, we still keep the the centre of the 3x3 grid as reference. But how is that if the pixel, for instance in the upper left corner has only 4 pixels (3 surrounding and the pixel itself), well, we treat the other pixels as a black frame.
// So if the grid is 1, 2, 3, 4, 5, 6, 7, 8 and 9. The values for GxR(B or G) (for the upper left corner would be), (0) * 1, (0) * 0, (0) * 1, (0) * -2, (184) * 0, (184) * 2, (184) * -1, (184) * 0, (184) * 1. Why do I say all of this? Because even if the exercise is easy, I took in a wrong way the reference for this, but we tak always the reference for the central grid in Gx, in other words the value 5 in the grid.
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (w == 0 && h == 0) // First pixel in the first row in the first column.
            {
                GxR = arrayWHRed[h][w] * 0 + arrayWHRed[h][w + 1] * 2 + arrayWHRed[h + 1][w] * 0 + arrayWHRed[h + 1][w + 1] * 1;
                GyR = arrayWHRed[h][w] * 0 + arrayWHRed[h][w + 1] * 0 + arrayWHRed[h + 1][w] * 2 + arrayWHRed[h + 1][w + 1] * 1;
                GxB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h][w + 1] * 2 + arrayWHBlue[h + 1][w] * 0 + arrayWHBlue[h + 1][w + 1] * 1;
                GyB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h][w + 1] * 0 + arrayWHBlue[h + 1][w] * 2 + arrayWHBlue[h + 1][w + 1] * 1;
                GxG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h][w + 1] * 2 + arrayWHGreen[h + 1][w] * 0 + arrayWHGreen[h + 1][w + 1] * 1;
                GyG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h][w + 1] * 0 + arrayWHGreen[h + 1][w] * 2 + arrayWHGreen[h + 1][w + 1] * 1;

            }
            if (w == width - 1 && h == 0) // Last pixel in the first row and last column.
            {
                GxR = arrayWHRed[h][w] * 0 + arrayWHRed[h][w - 1] * -2 + arrayWHRed[h + 1][w] * 0 + arrayWHRed[h + 1][w - 1] * -1;
                GyR = arrayWHRed[h][w] * 0 + arrayWHRed[h][w - 1] * 0 + arrayWHRed[h + 1][w] * 2 + arrayWHRed[h + 1][w - 1] * 1;
                GxB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h][w - 1] * -2 + arrayWHBlue[h + 1][w] * 0 + arrayWHBlue[h + 1][w - 1] * -1;
                GyB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h][w - 1] * 0 + arrayWHBlue[h + 1][w] * 2 + arrayWHBlue[h + 1][w - 1] * 1;
                GxG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h][w - 1] * -2 + arrayWHGreen[h + 1][w] * 0 + arrayWHGreen[h + 1][w - 1] * -1;
                GyG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h][w - 1] * 0 + arrayWHGreen[h + 1][w] * 2 + arrayWHGreen[h + 1][w - 1] * 1;
            }
            if ((w > 0 && w < width - 1) && h == 0) // All pixels in the first row except the first and the last one.
            {
                GxR = arrayWHRed[h][w] * 0 + arrayWHRed[h][w - 1] * -2 + arrayWHRed[h][w + 1] * 2 + arrayWHRed[h + 1][w - 1] * -1 +
                      arrayWHRed[h + 1][w] * 0 + arrayWHRed[h + 1][w + 1] * 1;
                GyR = arrayWHRed[h][w] * 0 + arrayWHRed[h][w - 1] * 0 + arrayWHRed[h][w + 1] * 0 + arrayWHRed[h + 1][w - 1] * 1 + arrayWHRed[h +
                        1][w] * 2 + arrayWHRed[h + 1][w + 1] * 1;
                GxB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h][w - 1] * -2 + arrayWHBlue[h][w + 1] * 2 + arrayWHBlue[h + 1][w - 1] * -1 +
                      arrayWHBlue[h + 1][w] * 0 + arrayWHBlue[h + 1][w + 1] * 1;
                GyB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h][w - 1] * 0 + arrayWHBlue[h][w + 1] * 0 + arrayWHBlue[h + 1][w - 1] * 1 + arrayWHBlue[h
                        + 1][w] * 2 + arrayWHBlue[h + 1][w + 1] * 1;
                GxG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h][w - 1] * -2 + arrayWHGreen[h][w + 1] * 2 + arrayWHGreen[h + 1][w - 1] * -1 +
                      arrayWHGreen[h + 1][w] * 0 + arrayWHGreen[h + 1][w + 1] * 1;
                GyG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h][w - 1] * 0 + arrayWHGreen[h][w + 1] * 0 + arrayWHGreen[h + 1][w - 1] * 1 +
                      arrayWHGreen[h + 1][w] * 2 + arrayWHGreen[h + 1][w + 1] * 1;
            }
            if (w == 0 && (h > 0 && h < height - 1)) // All pixels in the first column except the first and the last one.
            {
                GxR = arrayWHRed[h][w] * 0 + arrayWHRed[h - 1][w] * 0 + arrayWHRed[h - 1][w + 1] * 1 + arrayWHRed[h][w + 1] * 2 +
                      arrayWHRed[h + 1][w] * 0 + arrayWHRed[h + 1][w + 1] * 1;
                GyR = arrayWHRed[h][w] * 0 + arrayWHRed[h - 1][w] * -2 + arrayWHRed[h - 1][w + 1] * -1 + arrayWHRed[h][w + 1] * 0 +
                      arrayWHRed[h + 1][w] * 2 + arrayWHRed[h + 1][w + 1] * 1;
                GxB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h - 1][w] * 0 + arrayWHBlue[h - 1][w + 1] * 1 + arrayWHBlue[h][w + 1] * 2 +
                      arrayWHBlue[h + 1][w] * 0 + arrayWHBlue[h + 1][w + 1] * 1;
                GyB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h - 1][w] * -2 + arrayWHBlue[h - 1][w + 1] * -1 + arrayWHBlue[h][w + 1] * 0 +
                      arrayWHBlue[h + 1][w] * 2 + arrayWHBlue[h + 1][w + 1] * 1;
                GxG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h - 1][w] * 0 + arrayWHGreen[h - 1][w + 1] * 1 + arrayWHGreen[h][w + 1] * 2 +
                      arrayWHGreen[h + 1][w] * 0 + arrayWHGreen[h + 1][w + 1] * 1;
                GyG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h - 1][w] * -2 + arrayWHGreen[h - 1][w + 1] * -1 + arrayWHGreen[h][w + 1] * 0 +
                      arrayWHGreen[h + 1][w] * 2 + arrayWHGreen[h + 1][w + 1] * 1;
            }
            if ((w > 0 && w < width - 1) && (h > 0 && h < height - 1)) // Edge for the inner square inside the image.
            {
                GxR = (arrayWHRed[h - 1][w - 1]) * -1 + (arrayWHRed[h - 1][w]) * 0 + (arrayWHRed[h - 1][w + 1]) * 1 +
                      (arrayWHRed[h][w - 1]) * -2 + (arrayWHRed[h][w]) * 0 + (arrayWHRed[h][w + 1]) * 2 + (arrayWHRed[h + 1][w - 1]) * -1 +
                      (arrayWHRed[h + 1][w]) * 0 + (arrayWHRed[h + 1][w + 1]) * 1;
                GyR = (arrayWHRed[h - 1][w - 1]) * -1 + (arrayWHRed[h - 1][w]) * -2 + (arrayWHRed[h - 1][w + 1]) * -1 +
                      (arrayWHRed[h][w - 1]) * 0 + (arrayWHRed[h][w]) * 0 + (arrayWHRed[h][w + 1]) * 0 + (arrayWHRed[h + 1][w - 1]) * 1 +
                      (arrayWHRed[h + 1][w]) * 2 + (arrayWHRed[h + 1][w + 1]) * 1;
                GxB = (arrayWHBlue[h - 1][w - 1]) * -1 + (arrayWHBlue[h - 1][w]) * 0 + (arrayWHBlue[h - 1][w + 1]) * 1 +
                      (arrayWHBlue[h][w - 1]) * -2 + (arrayWHBlue[h][w]) * 0 + (arrayWHBlue[h][w + 1]) * 2 + (arrayWHBlue[h + 1][w - 1]) * -1 +
                      (arrayWHBlue[h + 1][w]) * 0 + (arrayWHBlue[h + 1][w + 1]) * 1;
                GyB = (arrayWHBlue[h - 1][w - 1]) * -1 + (arrayWHBlue[h - 1][w]) * -2 + (arrayWHBlue[h - 1][w + 1]) * -1 +
                      (arrayWHBlue[h][w - 1]) * 0 + (arrayWHBlue[h][w]) * 0 + (arrayWHBlue[h][w + 1]) * 0 + (arrayWHBlue[h + 1][w - 1]) * 1 +
                      (arrayWHBlue[h + 1][w]) * 2 + (arrayWHBlue[h + 1][w + 1]) * 1;
                GxG = (arrayWHGreen[h - 1][w - 1]) * -1 + (arrayWHGreen[h - 1][w]) * 0 + (arrayWHGreen[h - 1][w + 1]) * 1 +
                      (arrayWHGreen[h][w - 1]) * -2 + (arrayWHGreen[h][w]) * 0 + (arrayWHGreen[h][w + 1]) * 2 + (arrayWHGreen[h + 1][w - 1]) * -1 +
                      (arrayWHGreen[h + 1][w]) * 0 + (arrayWHGreen[h + 1][w + 1]) * 1;
                GyG = (arrayWHGreen[h - 1][w - 1]) * -1 + (arrayWHGreen[h - 1][w]) * -2 + (arrayWHGreen[h - 1][w + 1]) * -1 +
                      (arrayWHGreen[h][w - 1]) * 0 + (arrayWHGreen[h][w]) * 0 + (arrayWHGreen[h][w + 1]) * 0 + (arrayWHGreen[h + 1][w - 1]) * 1 +
                      (arrayWHGreen[h + 1][w]) * 2 + (arrayWHGreen[h + 1][w + 1]) * 1;
            }
            if (w == width - 1 && (h > 0 && h < height - 1)) // All pixels in the last column except the first and the last one.
            {
                GxR = arrayWHRed[h][w] * 0 + arrayWHRed[h - 1][w - 1] * -1 + arrayWHRed[h - 1][w] * 0 + arrayWHRed[h][w - 1] * -2 +
                      arrayWHRed[h + 1][w - 1] * -1 + arrayWHRed[h + 1][w] * 0;
                GyR = arrayWHRed[h][w] * 0 + arrayWHRed[h - 1][w - 1] * -1 + arrayWHRed[h - 1][w] * -2 + arrayWHRed[h][w - 1] * 0 +
                      arrayWHRed[h + 1][w - 1] * 1 + arrayWHRed[h + 1][w] * 2;
                GxB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h - 1][w - 1] * -1 + arrayWHBlue[h - 1][w] * 0 + arrayWHBlue[h][w - 1] * -2 +
                      arrayWHBlue[h + 1][w - 1] * -1 + arrayWHBlue[h + 1][w] * 0;
                GyB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h - 1][w - 1] * -1 + arrayWHBlue[h - 1][w] * -2 + arrayWHBlue[h][w - 1] * 0 +
                      arrayWHBlue[h + 1][w - 1] * 1 + arrayWHBlue[h + 1][w] * 2;
                GxG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h - 1][w - 1] * -1 + arrayWHGreen[h - 1][w] * 0 + arrayWHGreen[h][w - 1] * -2 +
                      arrayWHGreen[h + 1][w - 1] * -1 + arrayWHGreen[h + 1][w] * 0;
                GyG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h - 1][w - 1] * -1 + arrayWHGreen[h - 1][w] * -2 + arrayWHGreen[h][w - 1] * 0 +
                      arrayWHGreen[h + 1][w - 1] * 1 + arrayWHGreen[h + 1][w] * 2;
            }
            if ((w > 0 && w < width - 1) && h == height - 1) // All pixels in the last row except the first and the last one.
            {
                GxR = arrayWHRed[h][w] * 0 + arrayWHRed[h - 1][w - 1] * -1 + arrayWHRed[h - 1][w] * 0 + arrayWHRed[h - 1][w + 1] * 1 +
                      arrayWHRed[h][w - 1]  * -2 + arrayWHRed[h][w + 1] * 2;
                GyR = arrayWHRed[h][w] * 0 + arrayWHRed[h - 1][w - 1] * -1 + arrayWHRed[h - 1][w] * -2 + arrayWHRed[h - 1][w + 1] * -1 +
                      arrayWHRed[h][w - 1]  * 0 + arrayWHRed[h][w + 1] * 0;
                GxB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h - 1][w - 1] * -1 + arrayWHBlue[h - 1][w] * 0 + arrayWHBlue[h - 1][w + 1] * 1 +
                      arrayWHBlue[h][w - 1]  * -2 + arrayWHBlue[h][w + 1] * 2;
                GyB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h - 1][w - 1] * -1 + arrayWHBlue[h - 1][w] * -2 + arrayWHBlue[h - 1][w + 1] * -1 +
                      arrayWHBlue[h][w - 1]  * 0 + arrayWHBlue[h][w + 1] * 0;
                GxG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h - 1][w - 1] * -1 + arrayWHGreen[h - 1][w] * 0 + arrayWHGreen[h - 1][w + 1] * 1 +
                      arrayWHGreen[h][w - 1]  * -2 + arrayWHGreen[h][w + 1] * 2;
                GyG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h - 1][w - 1] * -1 + arrayWHGreen[h - 1][w] * -2 + arrayWHGreen[h - 1][w + 1] * -1 +
                      arrayWHGreen[h][w - 1]  * 0 + arrayWHGreen[h][w + 1] * 0;
            }
            if (w == 0 && h == height - 1) // Last pixel in the first column.
            {
                GxR = arrayWHRed[h][w] * 0 + arrayWHRed[h][w + 1] * 2 + arrayWHRed[h - 1][w] * 0 + arrayWHRed[h - 1][w + 1] * 1;
                GyR = arrayWHRed[h][w] * 0 + arrayWHRed[h][w + 1] * 0 + arrayWHRed[h - 1][w] * -2 + arrayWHRed[h - 1][w + 1] * -1;
                GxB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h][w + 1] * 2 + arrayWHBlue[h - 1][w] * 0 + arrayWHBlue[h - 1][w + 1] * 1;
                GyB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h][w + 1] * 0 + arrayWHBlue[h - 1][w] * -2 + arrayWHBlue[h - 1][w + 1] * -1;
                GxG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h][w + 1] * 2 + arrayWHGreen[h - 1][w] * 0 + arrayWHGreen[h - 1][w + 1] * 1;
                GyG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h][w + 1] * 0 + arrayWHGreen[h - 1][w] * -2 + arrayWHGreen[h - 1][w + 1] * -1;
            }
            if (w == width - 1 && h == height - 1) // Last pixel in the last row and last colummn.
            {
                GxR = arrayWHRed[h][w] * 0 + arrayWHRed[h][w - 1] * -2 + arrayWHRed[h - 1][w] * 0 + arrayWHRed[h - 1][w - 1] * -1;
                GyR = arrayWHRed[h][w] * 0 + arrayWHRed[h][w - 1] * 0 + arrayWHRed[h - 1][w] * -2 + arrayWHRed[h - 1][w - 1] * -1;
                GxB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h][w - 1] * -2 + arrayWHBlue[h - 1][w] * 0 + arrayWHBlue[h - 1][w - 1] * -1;
                GyB = arrayWHBlue[h][w] * 0 + arrayWHBlue[h][w - 1] * 0 + arrayWHBlue[h - 1][w] * -2 + arrayWHBlue[h - 1][w - 1] * -1;
                GxG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h][w - 1] * -2 + arrayWHGreen[h - 1][w] * 0 + arrayWHGreen[h - 1][w - 1] * -1;
                GyG = arrayWHGreen[h][w] * 0 + arrayWHGreen[h][w - 1] * 0 + arrayWHGreen[h - 1][w] * -2 + arrayWHGreen[h - 1][w - 1] * -1;
            }
//Now, we have to get the combined values for each colour. We can get that by obtaining the square of the value and getting the root square of them.
            FGxyR = round(sqrt((GxR * GxR) + (GyR * GyR)));
            FGxyB = round(sqrt((GxB * GxB) + (GyB * GyB)));
            FGxyG = round(sqrt((GxG * GxG) + (GyG * GyG)));
// We might need this, just in case, after the operation, we get values over 255. Remmeber, the biggest value is 255 for colours in a 0-255 scale.
            if (FGxyR > 255)
            {
                FGxyR = 255;
            }
            if (FGxyB > 255)
            {
                FGxyB = 255;
            }
            if (FGxyG > 255)
            {
                FGxyG = 255;
            }
// As final setp, we set the values given by the operation to the original image for each pixel and colour.
            image[h][w].rgbtRed = FGxyR;
            image[h][w].rgbtBlue = FGxyB;
            image[h][w].rgbtGreen = FGxyG;
        }
    }
    return;
}
