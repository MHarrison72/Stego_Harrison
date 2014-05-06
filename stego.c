//Author: Michael Harrison
#include <stdio.h>
#include <string.h>
#include "stego.h"

int main(int argc, char **argv){
	PPMImage *image;
	char readName[25], writeName[25], message[255], *c;
	int x=0;

	printf("Please enter name of input file:\n");
	fgets(readName,sizeof(readName),stdin);
	c = strchr(readName,'\n');
	if(c!=NULL){*c='\0';}
	image = readPPM(readName);

    	readMessage(image);

	printf("Please enter messsage to be written(Max Characters 255): \n");
	fgets(message,sizeof(message),stdin);
	c = strchr(message,'\n');
	if(c!=NULL){*c='\0';}
	writeMessage(message,image);

	printf("Please enter name of output file: \n");
    	fgets(writeName,sizeof(writeName),stdin);
	c = strchr(writeName,'\n');
	if(c!=NULL){*c='\0';}
	writePPM(writeName,image);

    	return 0;
}
