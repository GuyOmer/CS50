/****************************************************************************
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP piece by piece, just because.
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

#define MULTPLIER_MAX 100
#define MULTPLIER_MIN 1


int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: copy multiplier infile outfile \n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    //remember multiplier (N)
    int multi = atoi(argv[1]);

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
       
    //tests multiplier validity
    if(multi < MULTPLIER_MIN ||multi > MULTPLIER_MAX)
    {
        printf("The multiplier %d is invaild.\nmultiplier must be between %d-%d." , multi, MULTPLIER_MIN, MULTPLIER_MAX);
        return 4;
    
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    //Saves old padding, height and width
    int old_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int old_biWidth = bi.biWidth;
    int old_biHeight = bi.biHeight;
    
    //multiplies BITMAPINFOHEADER
    bi.biWidth = bi.biWidth*multi;
    bi.biHeight = bi.biHeight*multi;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //sets new BITMAPINFOHEADER Image size.
    bi.biSizeImage =  bi.biWidth*abs(bi.biHeight)*sizeof(RGBTRIPLE)+padding*abs(bi.biHeight);
    
    //multiplies BITMAPFILEHEADER
    bf.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+bi.biSizeImage;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(old_biHeight); i < biHeight; i++) //Height 1
    {
        // iterate over pixels in scanline
        for(int mi = 0; mi < multi; mi++)                            //Height 3
        {   
            for (int j = 0; j < old_biWidth; j++)                    //Width 1
            {
            //temporary storage
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for(int mj = 0; mj < multi; mj++)                    //Width 2
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                } 
            }
        // skip over padding, if any
        fseek(inptr, old_padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
           fputc(0x00, outptr);
        // resets file read indicator
        if (mi < multi-1)      
            fseek(inptr, -1*(old_padding+(old_biWidth*(sizeof(RGBTRIPLE)))), SEEK_CUR);
        
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
