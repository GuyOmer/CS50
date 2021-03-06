/****************************************************************************
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

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

    
    //open info file
    FILE* info = fopen("info.csv","w");
    if (info == NULL)
    {
        fclose(info);
        fprintf(stderr, "Could not create info.csv.\n");
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
    
    //multiplies BITMAPINFOHEADER
    bi.biWidth = bi.biWidth*multi;
    bi.biHeight = bi.biHeight*multi;

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    fprintf(info,"\n%d,\n",padding);
    
    //Sets new BITMAPINFOHEADER Image size.
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight); 
    
    //multiplies BITMAPFILEHEADER
    bf.bfSize = bf.bfSize*multi;
    
    //char* bfa[5] = {"bf.bfType", "bf.bfSize", "bf.bfReserved1", "bf.bfReserved2", "bf.bfOffBits"};
    //char* bia[11] = {"bi.bfOffBits", "bi.biWidth" ,"bi.biHeight", "bi.biPlanes" ,"bi.biBitCount", "bi.biCompression", "bi.biSizeImage", "bi.biXPelsPerMeter", "bi.biYPelsPerMeter", "bi.biClrUsed", "bi.biClrImportant"};
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, info);
    fputc(0x2C, info);
    fputc(0x0A, info);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, info);
    fputc(0x2C, info);
    fputc(0x0A, info);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {   
            for(int mi = i; mi < multi; mi++)
            {
                for(int mj = j; mj < multi; mj++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    fwrite(&triple, sizeof(RGBTRIPLE),1,info);
                    fputc(0x2C, info);
                }
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
                fputc(0x00, outptr);
            fputc(0x0A, info);
            
            
            }
        }

    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
    
    //close info
    fclose(info);

    // that's all folks
    return 0;
}
