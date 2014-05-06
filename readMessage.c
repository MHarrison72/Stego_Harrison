//Author: Michael Harrison
#include <stdio.h>
#include <stdlib.h>
#include "stego.h"

//read message from struct data structure
void readMessage(PPMImage *img){
	int length = 0, c = 0, x = 0,i,j,k;
	//read length of message
	for(i=0;i<8;i++){
		length = length<<1;
		if(i==0||i==3||i==6){length = length|(img->data[x].red&0x01);}
		else if(i==1||i==4||i==7){length = length|(img->data[x].green&0x01);}
		else if(i==2||i==5){length = length|(img->data[x].blue&0x01); x++;}
	}
	//read message
	char message[length];
	i=length;
	for(j=0;j<length;j++){
		c = 0;
		for(k=0;k<8;k++){
			c = c<<1;
			if(k==0||k==3||k==6){c = c|(img->data[x].blue&0x01); x++;}
                	if(k==1||k==4||k==7){c = c|(img->data[x].red&0x01);}
			if(k==2||k==5){c = c|(img->data[x].green&0x01);}
		}
		message[j] = (char)c;
		j++;
		if(j<length){
			c = 0;
                	for(k=0;k<8;k++){
                        	c = c<<1;
                        	if(k==0||k==3||k==6){c = c|(img->data[x].green&0x01);}
                        	if(k==1||k==4||k==7){c = c|(img->data[x].blue&0x01); x++;}
                        	if(k==2||k==5){c = c|(img->data[x].red&0x01);}
                	}
                	message[j] = (char)c;
		}
		j++;
		if(j<length){
			c = 0;
                	for(k=0;k<8;k++){
                        	c = c<<1;
                        	if(k==0||k==3||k==6){c = c|(img->data[x].red&0x01);}
                        	if(k==1||k==4||k==7){c = c|(img->data[x].green&0x01);}
                        	if(k==2||k==5){c = c|(img->data[x].blue&0x01); x++;}
                	}
                	message[j] = (char)c;
		}
	}
	message[length] = '\0';
	printf("Decoded message:\n");
	printf("%s\n",message);
}

//extracts image data from ppm into struct data structure
PPMImage *readPPM(char *filename){
	char buff[16];
        PPMImage *img;
	FILE *fp;
	int c, rgb_comp_color;

        //open PPM file for reading
        fp = fopen(filename, "rb");
        if (!fp) {
             	fprintf(stderr, "Unable to open file '%s'\n", filename);
             	exit(1);
        }

        //read image format
        if (!fgets(buff, sizeof(buff), fp)) {
             	perror(filename);
             	exit(1);
        }

	//check the image format
    	if (buff[0] != 'P' || buff[1] != '6') {
        	fprintf(stderr, "Invalid image format (must be 'P6')\n");
        	exit(1);
	}

	//alloc memory for image
    	img = (PPMImage *)malloc(sizeof(PPMImage));
    	if (!img) {
         	fprintf(stderr, "Unable to allocate memory\n");
         	exit(1);
	}

    	//check for comments
    	c = getc(fp);
    	while (c == '#') {
    		while (getc(fp) != '\n') ;
         		c = getc(fp);
    	}

    	ungetc(c, fp);
    	//read image size information
    	if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         	fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         	exit(1);
    	}

    	//read rgb component
    	if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         	fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         	exit(1);
    	}

    	//check rgb component depth
    	if (rgb_comp_color!= 255) {
        	 fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
        	 exit(1);
    	}

    	while (fgetc(fp) != '\n') ;

    	//memory allocation for pixel data
    	img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));
    	if (!img) {
         	fprintf(stderr, "Unable to allocate memory\n");
         	exit(1);
    	}

    	//read pixel data from file
    	if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
         	fprintf(stderr, "Error loading image '%s'\n", filename);
         	exit(1);
    	}
	printf("Image Loaded.\n");
    	fclose(fp);
    	return img;
}
