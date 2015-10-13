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

int logger(int i, int mi, int j, int mj,FILE* inptr/**, RGBTRIPLE triple**/);


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
    
    int old_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int old_biWidth = bi.biWidth;
    int old_biHeight = bi.biHeight;
    
    //multiplies BITMAPINFOHEADER
    bi.biWidth = bi.biWidth*multi;
    bi.biHeight = bi.biHeight*multi;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //Sets new BITMAPINFOHEADER Image size.
    bi.biSizeImage = abs(bi.biHeight) * bi.biWidth;
    //(bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight); 
    
    //multiplies BITMAPFILEHEADER
    bf.bfSize = bf.bfSize*multi;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(old_biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for(int mi = 0; mi < multi; mi++)
        {   
            for (int j = 0; j < old_biWidth; j++)       //Height 2
            {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for(int mj = 0; mj < multi; mj++)   //Width 2
                {
                    //temporary storage
                    //RGBTRIPLE triple;

                    // read RGB triple from infile
                    //fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    int itest=logger(i,mi,j,mj,inptr/**,triple**/);
                    printf("%d, ",itest);
                } 
            }
        // skip over padding, if any
        fseek(inptr, old_padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
           fputc(0x00, outptr);
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


    int logger(int i, int mi, int j, int mj,FILE* inptr/**, RGBTRIPLE triple**/)
    {
        FILE* logger= fopen("log.txt","a");
        if(log==NULL)
            printf("Couldn't create log.txt");
            
        fprintf(logger, "Height: %d\nMutli Height: %d\nWidth: %d\nMulti Width: %d\nIndicator Position: %ld\n", i,mi,j,mj,ftell(inptr));
        //fwrite(&triple, sizeof(RGBTRIPLE), 1, logger);
        fprintf(logger,"\n-----------------\n");
        return ftell(inptr);
    }
