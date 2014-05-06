//Author: Michael Harrison
#ifndef STRUCTS
#define STRUCTS
typedef struct {
     	unsigned char red,green,blue;
} PPMPixel;

typedef struct {
	int x, y;
     	PPMPixel *data;
} PPMImage;
#endif

PPMImage *readPPM(char *filename);
void readMessage(PPMImage *img);

void writeMessage(char *message, PPMImage *img);
void writePPM(char *filename, PPMImage *img);

