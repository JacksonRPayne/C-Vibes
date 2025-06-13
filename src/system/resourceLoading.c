#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct BMPFile{
    int32_t width;
    int32_t height;
    unsigned char* pixelBuffer;    
}BMPFile;


/* Bitmap file format
 *
 * SECTION
 * Address:Bytes	Name
 *
 * HEADER:
 *	  0:	2		"BM" magic number
 *	  2:	4		file size
 *	  6:	4		junk
 *	 10:	4		Starting address of image data
 * BITMAP HEADER:
 *	 14:	4		header size
 *	 18:	4		width  (signed)
 *	 22:	4		height (signed)
 *	 26:	2		Number of color planes
 *	 28:	2		Bits per pixel
 *	[...]
 * [OPTIONAL COLOR PALETTE, NOT PRESENT IN 32 BIT BITMAPS]
 * BITMAP DATA:
 *	DATA:	X	Pixels
 */

// Loads 32 bit bitmap v4 files into a pixel buffer (includes heap allocation)
void bmpLoadFromFile(BMPFile* bmpFile, const char* filename){

    FILE* file = fopen(filename, "rb");

    // File path not found
    if(!file){
        printf("ERROR: Bitmap file could not be located. Path: %s\n", filename);
        fclose(file);
        return;
    }

    // Magic number "BM" not found
    if(fgetc(file) != 'B' || fgetc(file) != 'M'){
        printf("ERROR: Invalid bitmap file (didn't contain magic number BM\n");
        fclose(file);
        return;
    }

    // Skips over file size info and junk
    fseek(file, 8, SEEK_CUR);

    // Finds the byte offset of the pixel data from start of file
    uint32_t pixelDataOffset;
    fread(&pixelDataOffset, 4, 1, file);

    // Skips file header size
    fseek(file, 4, SEEK_CUR);

    // Read image width and height
    int32_t width;
    fread(&width, 4, 1, file);
    int32_t height;
    fread(&height, 4, 1, file);

    // Skip color planes
    fseek(file, 2, SEEK_CUR);

    // Check file has correct bit depth (expecting 32)
    uint16_t bitDepth;
    fread(&bitDepth, 2, 1, file);
    if(bitDepth != 32){
        printf("ERROR: incorrect bit depth. Expected 32, got %d\n", bitDepth);
    }

    // Allocate pixel buffer
    int32_t pixelCount = width * height;
    int32_t bytesPerPixel = bitDepth / 8;

    unsigned char* pixels = malloc(pixelCount * bytesPerPixel);
    if(!pixels){
        printf("ERROR: failed to allocate pixels for bmp file\n");
        free(pixels);
        fclose(file);
        return;
    }

    // Read pixels into buffer
    fseek(file, pixelDataOffset, SEEK_SET);
    size_t pixelsRead = fread(pixels, bytesPerPixel, pixelCount, file);
    if(pixelsRead != pixelCount){
        printf("ERROR: only read %llu pixels of bmp file\n", pixelsRead);
        fclose(file);
        return;
    }

    bmpFile->width = width;
    bmpFile->height =height;
    bmpFile->pixelBuffer = pixels;

    fclose(file);
}

void bmpFree(BMPFile* bmpFile){
    free(bmpFile->pixelBuffer);
}