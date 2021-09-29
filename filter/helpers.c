#include "helpers.h"
#include <stdio.h>
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int h = 0;h<height;h++)
    {
        for(int w = 0;w<width;w++)
        {
            float red = image[h][w].rgbtRed;
            float blue = image[h][w].rgbtBlue;
            float green = image[h][w].rgbtGreen;
            int average_rgb = round((red + blue + green)/3);
            image[h][w].rgbtRed = image[h][w].rgbtBlue = image[h][w].rgbtGreen = average_rgb;
        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for(int h = 0;h<height;h++)
    {
        for(int w = 0;w<width/2;w++)
        {
            RGBTRIPLE buffer = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = buffer;

        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int h = 0;h<height;h++)
    {
        for(int w = 0;w<width;w++)
        {
            float sumR = 0,sumB = 0,sumG =0;
            int counter = 0;
            int row[]={h-1,h,h+1};
            int col[]={w-1,w,w+1};
            
            for(int i = 0;i < 3;i++)
            {
                for(int j = 0;j < 3;j++)
                {
                    int RR = row[i];
                    int CC = col[j];
                    if(RR >= 0 && RR < height && CC >= 0 && CC < width)
                    {
                        RGBTRIPLE pixel = image[RR][CC];
                        sumR += pixel.rgbtRed;
                        sumB += pixel.rgbtBlue;
                        sumG += pixel.rgbtGreen;
                        counter++;
                        
                    }
                }
            }
            temp[h][w].rgbtRed = round(sumR/counter); 
            temp[h][w].rgbtBlue = round(sumB/counter);
            temp[h][w].rgbtGreen = round(sumG/counter);
        }
        
    }
    for(int i = 0;i<height;i++)
    {
        for(int j = 0; j<width;j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] ={
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    }; 
    int Gy[3][3] ={
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    }; 
    RGBTRIPLE temp[height][width];
    for(int h = 0;h<height;h++)
    {
        for(int w = 0;w<width;w++)
        {
            float GxR = 0,GxG = 0,GxB = 0;
            float GyR = 0,GyG = 0,GyB = 0;
            int row[]={h-1,h,h+1};
            int col[]={w-1,w,w+1};
            for(int i = 0;i<3;i++)
            {
                for(int j = 0;j<3;j++)
                {
                    int RR = row[i];
                    int CC = col[j];
                    if(RR >= 0 && RR <height && CC >= 0&& CC < width)
                    {
                        GxR += Gx[i][j] * image[RR][CC].rgbtRed;
                        GxG += Gx[i][j] * image[RR][CC].rgbtGreen;
                        GxB += Gx[i][j] * image[RR][CC].rgbtBlue;
                        
                        GyR += Gy[i][j] * image[RR][CC].rgbtRed;
                        GyG += Gy[i][j] * image[RR][CC].rgbtGreen;
                        GyB += Gy[i][j] * image[RR][CC].rgbtBlue;
                    }
                }
            }
            int finalred = round(sqrt(GxR * GxR + GyR * GyR));
            int finalblue = round(sqrt(GxB * GxB + GyB * GyB));
            int finalgreen = round(sqrt(GxG * GxG + GyG * GyG));
            
            temp[h][w].rgbtRed = finalred > 255 ? 255:finalred;
            temp[h][w].rgbtBlue = finalblue > 255 ? 255:finalblue;
            temp[h][w].rgbtGreen = finalgreen > 255 ? 255:finalgreen;
            
            
            
        }
    }
    for(int i = 0;i<height;i++)
    {
        for(int j = 0;j<width;j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    
    return;
}
