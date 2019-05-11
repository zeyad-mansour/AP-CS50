/*Layout-
Open the file.
Update the outfile's header info
Read infile's scanline pixel by pixel
Resize horizontally
Address the padding adjustments
resize vertically
REMEMBER TO REFERENCE TO COPY.C
*/

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 0 || n > 100) //n, the scale factor, must be between 0 and 100
    {
        return 5;
    }

    char *infile = argv[2];
    char *outfile = argv[3];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        return 2;
    }
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        return 3;
    }

    BITMAPFILEHEADER bf, r_bf; //must be equal to headers outfile
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    r_bf = bf;

    BITMAPINFOHEADER bi, r_bi; //same as header infile
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    r_bi = bi;

    r_bi.biWidth = bi.biWidth * n;
    r_bi.biHeight = bi.biHeight * n;

    if (bi.biSize != 40 || bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        return 4;
    }


    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = (4 - (r_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    r_bf.bfSize = 54 + abs(r_bi.biHeight) * r_bi.biWidth * 3 + abs(r_bi.biHeight) *  out_padding;
	r_bi.biSizeImage = ((((r_bi.biWidth * r_bi.biBitCount) + 31) & ~31) / 8) * abs(r_bi.biHeight);

    fwrite(&r_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&r_bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < n; j++)
        {

            for (int k = 0; k < bi.biWidth; k++)
            {
                RGBTRIPLE triple;

                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for (int x = 0; x < n; x++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }


            }

            // add padding
            for (int y = 0; y < out_padding; y++)
            {
                fputc(0x00, outptr);
            }

            if (j < n - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }

        }

        fseek(inptr, padding, SEEK_CUR);
    }
    fclose(inptr);
    fclose(outptr);
    return 0;
}