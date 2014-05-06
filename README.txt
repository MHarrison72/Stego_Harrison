Author: Michael Harrison
Created on Ubuntu

stego.h
	-Header file contaning struct and function definitions.
stego.c
	-Main program taking filenames and message as user input.
readMessage.c
	-readPPM organizes ppm data into array of structs for easy access.
	-readMessage pulls a hidden message from the least significant bits of RGB data
writeMessage.c
	-writePPM prints array of structs into a valid ppm file
	-writeMessage hides a hidden message in the least significant bits of RGB data


Complie w/ "gcc stego.c stego.h readMessage.c writeMessage.c"

