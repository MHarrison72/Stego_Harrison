//Author: Michael Harrison
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stego.h"

//hide message in struct data structure
void writeMessage(char *message, PPMImage *img){
        int len = strnlen(message,255)+1,x = 0,c,j,k;
	//Input message length
        for(j=0;j<8;j++){
                if(len&0x80){img->data[x].red |= 0x01;}
                else {img->data[x].red &= 0xFE;}
		len <<= 1;
		j++;
		if(j<8){
                	if(len&0x80){img->data[x].green |= 0x01;}
                	else {img->data[x].green &= 0xFE;}
			len <<= 1;
			j++;
		}
		if(j<8){
                	if(len&0x80){img->data[x].blue |= 0x01;}
                	else {img->data[x].blue &= 0xFE;}
			len <<= 1;
			x++;
		}
	}
	//Input message
	len = strnlen(message,255)+1;
	for(j=0;j<len;j++){
		c = (int)message[j];
		for(k=0;k<8;k++){
			if(c&0x80){img->data[x].blue |= 0x01; x++;}
			else{img->data[x].blue &= 0xFE; x++;}
			c <<= 1;
			k++;
			if(k<8){
                		if(c&0x80){img->data[x].red |= 0x01;}
				else{img->data[x].red &= 0xFE;}
				c <<= 1;
				k++;
			}
			if(k<8){
				if(c&0x80){img->data[x].green |= 0x01;}
				else{img->data[x].green &= 0xFE;}
				c <<= 1;
			}
		}
		j++;
		if(j<len){
			c = (int)message[j];
			for(k=0;k<8;k++){
				if(c&0x80){img->data[x].green |= 0x01;}
				else{img->data[x].green &= 0xFE;}
				c <<= 1;
				k++;
				if(k<8){
                			if(c&0x80){img->data[x].blue |= 0x01; x++;}
					else{img->data[x].blue &= 0xFE; x++;}
					c <<= 1;
					k++;
				}
				if(k<8){
					if(c&0x80){img->data[x].red |= 0x01;}
					else{img->data[x].red &= 0xFE;}
					c <<= 1;
				}
			}
		}
		j++;
		if(j<len){
			c = (int)message[j];
			for(k=0;k<8;k++){
				if(c&0x80){img->data[x].red |= 0x01;}
				else{img->data[x].red &= 0xFE;}
				c <<= 1;
				k++;
				if(k<8){
                			if(c&0x80){img->data[x].green |= 0x01;}
					else{img->data[x].green &= 0xFE;}
					c <<= 1;
					k++;
				}
				if(k<8){
					if(c&0x80){img->data[x].blue |= 0x01; x++;}
					else{img->data[x].blue &= 0xFE; x++;}
					c <<= 1;
				}
			}
		}
	}
	printf("Message hidden in image.\n");
}

//write data structure into viewable ppm
void writePPM(char *filename, PPMImage *img){
        FILE *fp;
        //open file for output
        fp = fopen(filename, "wb");

        if (!fp) {
                fprintf(stderr, "Unable to open file '%s'\n", filename);
                exit(1);
        }

        //write the header file
        //image format
        fprintf(fp, "P6\n");

        //comments
        fprintf(fp, "# Created by Michael Harrison\n");

        //image size
        fprintf(fp, "%d %d\n",img->x,img->y);

        // rgb component depth
        fprintf(fp, "%d\n",255);

        // pixel data
        fwrite(img->data, 3 * img->x, img->y, fp);
        fclose(fp);

	printf("Image Written.\n");
}
