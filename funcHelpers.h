
#ifndef __FUNCHELPERS_H
#define __FUNCHELPERS_H
#include "types.h"


//------  TREE FUNCTIONS---------//
//q1
long int fileSize(FILE *file); // fun returns the size of the file
void checkMemoryAllocation(void *ptr); // function check if the allcation memory was successfully created 
//q2
BOOL** bucketMatrix(unsigned short row, unsigned short col);  // function teturn true is in the cell x,y there is false
void findSingleSegmentHelper(grayImage *img, imgPos root, imgPos newRoot, unsigned char threshold, BOOL** bucket, TreeNode* nodeRoot);// q2 helper 
void printBucket(BOOL** bucket, unsigned short row, unsigned short col); // print the bucket
void freeSegment(grayImage *img, imgPos start, unsigned char threshold, Segment seg, BOOL** bucket); // free allocated memory of the segment
void freeBucket(BOOL** bucket, unsigned short row, unsigned short col); // free all bucket allocated memory 
imgPos* findRootList(grayImage* img, imgPos rootStart, imgPos start, unsigned char threshold, BOOL** bucket, int* neighbors); // fun returns an array with all the possiable neighbors
void freeSegmentHelper(grayImage *img, imgPos root, unsigned char threshold, BOOL** bucket, TreeNode* nodeRoot);// free segment helper. Rec

//q3
imgPosCell* findRootListNew(imgPosList* lst, grayImage* img, imgPos rootStart, imgPos start, unsigned char threshold, BOOL** bucket, int* neighbors);
void findAllSegmentsHelperNew(grayImage *img, imgPos root, imgPos newRoot, unsigned char threshold, BOOL** bucket, imgPosList* lst);// q3 recursion helper.
void RunRightAndDown(grayImage* img, imgPos pos, imgPos originalRoot, unsigned char threshold, BOOL** bucket, imgPosList* lst,int* counter);// run to the right and down the lines on the spasific lines. for more possabile neighberhoods- and adds them to the list

//q5
unsigned char convertPix(unsigned char pix, unsigned char max_gray_level); // calc the new value with the formula
unsigned char maxOfBitByMaxGray(unsigned char max_gray_level);  //function get a number, and returns the max of bit he requires. 

//q6
void makePGMfileFromArray(unsigned char* ptr, unsigned short cols, unsigned short rows, unsigned short max, char* pgm_file_name); // function get an array, rows, cols and max gray level. and create a pgm picture.
void printMatrix(unsigned char** str, unsigned short rows, unsigned short  cols); // print a matrix
//q7
grayImage* case1Menu(grayImage* image,char* fileName);  // menu case1 
void case2Menu(grayImage* image, char* fileName, imgPosList** segments, int* numOfSegments); // menu case2
grayImage* case3Menu(imgPosList** segments, imgPosList* coolList, int numOfSegments); // menu case3 
void case4Menu(grayImage* coloredImage, char* fileName); // menu case4
void case5Menu(grayImage* image); // menu case5
void case6Menu(); // menu case6 
unsigned char maxGrayLevelOfPGMPic(grayImage* image); // finds the pixale with the max gray level
void freeGrayImage(grayImage* img); // fun free all gray image allocated memory 
void freeMatrix(unsigned char** mat, unsigned short row, unsigned short col); // fun free matrix - all allocated memory 



void insertFromTreeNLCToList(grayImage *img, imgPos root, unsigned char threshold, BOOL** bucket, TreeNode* nodeRoot, imgPosList* lst); // insert from tree node list to list.
#endif //__FUNCHELPERS_H