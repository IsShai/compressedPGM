#ifndef __LISTS_H
#define __LISTS_H
#include "types.h"


//------  LIST FUNCTIONS---------//

imgPosCell * createNewImgPosCell(imgPos data, imgPosCell* next, imgPosCell* prev); // create new imgPos cell
void makeEmptyImgPosList(imgPosList * lst);  // function get list and make it empty 
BOOL isEmptyImgPosList(imgPosList* lst);  // check if the img pos list is empty


void insertDataToEndImgPosList(imgPosList * lst, imgPos position);  // insert data to the end of the list 
void insertNodeToEndImgPosList(imgPosList* lst, imgPosCell* tail); // insert node to the end of the list 


void printImgPosList(imgPosList* lst);  // print list 
void freeImgPosList(imgPosList* lst); // free img pos list 

#endif //__LISTS_H
