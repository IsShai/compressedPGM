#ifndef __FUNC_H
#define __FUNC_H
#include "types.h"

//------  LIST FUNCTIONS---------//

grayImage *readPGM(char *fname); //Q1 - function gets a name of a text file and returns a grayimage file 
Segment findSingleSegment(grayImage *img, imgPos start, unsigned char threshold); //Q2 - the function gets a grayimg, position and a threshols and returns 
                                                                        // a segment that has all this postion's neighbors that their distance is no larger that threshold 
int findAllSegments(grayImage* img, unsigned char threshold, imgPosList** segments);  //Q3 - the function gets a grayimage and a threshold
//      and returns the number of different segamets, and return by pointer an array of lists of all the segments. 
grayImage *colorSegments(imgPosList *segments, unsigned int size);  //Q4  - - the fucntion gets list of segments - from q3, and change the color of each one of them by a furmola
void saveCompressed(char* file_name, grayImage* image, unsigned char max_gray_level);  //Q5  -- the function gets a name and a grayimage and save in a bin file the compressed file
void convertCompressedImageToPGM(char *compressed_file_name, char* pgm_file_name);  //Q6 - the function gets a compressed bin file. and make a pgm picture from it, with the orignal values
void printMenu(); //Q7 - function print the menu. and help the user use all 6 other functions.
#endif //__FUNC_H