#include "helpers.h"
#include <math.h>

void copy_image(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width]);
int sorel_score(int gx, int gy);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RGBTRIPLE pixel = image[i][j];
            float avg = (pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0;
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtRed = round(avg);
            image[i][j].rgbtGreen = round(avg); 
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            //swap pixels
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    copy_image(height, width, image, image_copy);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            //get blur score
            float red_total = 0;
            float green_total = 0;
            float blue_total = 0;
            int pixels_in_box = 0;
            for (int row = i - 1; row <= i + 1; row++) {
                if (row == -1 || row == height) {
                    continue;
                }
                for (int column = j - 1; column <= j + 1; column++) {
                    if (column == -1 || column == width) {
                        continue;
                    }
                    red_total += image_copy[row][column].rgbtRed;
                    blue_total += image_copy[row][column].rgbtBlue;
                    green_total += image_copy[row][column].rgbtGreen;
                    pixels_in_box++;
                }
                RGBTRIPLE blur_pixel;
                blur_pixel.rgbtRed = round(red_total / pixels_in_box);
                blur_pixel.rgbtBlue = round(blue_total / pixels_in_box);
                blur_pixel.rgbtGreen = round(green_total / pixels_in_box); 
                image[i][j] = blur_pixel;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //make copy of image map
    RGBTRIPLE image_copy[height][width];
    copy_image(height, width, image, image_copy);

    //hardcode kernal values CHECK
    int gx_kernal[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_kernal[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //iterate through each pixel of image map
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {           
            int red_gy = 0;
            int red_gx = 0;
            int green_gy = 0;
            int green_gx = 0;
            int blue_gy = 0;
            int blue_gx = 0;

            //iterate through pixel's neightbours
            for (int y = 0; y < 3; y++) {
                int y_displacement = y - 1;

                //skip vertical borders
                if ((i + y_displacement) == -1 || (i + y_displacement) == height) {
                    continue;
                }
                for (int x = 0; x < 3; x++) {
                    int x_displacement = x - 1;

                    //skip horizonal borders
                    if ((j + x_displacement) == -1 || (j + x_displacement) == width) {
                        continue;
                    }
                    RGBTRIPLE pixel = image_copy[i + y_displacement][j + x_displacement];
                    int gx_multiplier = gx_kernal[y][x];
                    int gy_multiplier = gy_kernal[y][x];

                    red_gx += (pixel.rgbtRed * gx_multiplier);
                    red_gy += (pixel.rgbtRed * gy_multiplier);
                    green_gx += (pixel.rgbtGreen * gx_multiplier);
                    green_gy += (pixel.rgbtGreen * gy_multiplier);
                    blue_gx += (pixel.rgbtBlue * gx_multiplier);
                    blue_gy += (pixel.rgbtBlue * gy_multiplier);                    
                }                
            }
            //apply sorel
            image[i][j].rgbtRed = sorel_score(red_gx, red_gy);
            image[i][j].rgbtGreen = sorel_score(green_gx, green_gy);
            image[i][j].rgbtBlue = sorel_score(blue_gx, blue_gy);
        }
    }
    return;
}

void copy_image(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width]) {    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copy[i][j] = image[i][j];
        }
    }
    return;
}

int sorel_score(int gx, int gy) {
    float sorel_score = sqrt(gx * gx + gy * gy);
    if (sorel_score > 255) {
        return 255;
    } else if (sorel_score < 0) {
        return 0;
    }
    return round(sorel_score);
}
