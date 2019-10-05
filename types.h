
#ifndef __TYPES_H
#define __TYPES_H
typedef int BOOL;
// DEFINE boolian
#define TRUE 1
#define FALSE 0

#define QUIT 7  // exit for the meue
#define MAX_FILE_NAME 40  // max file name size
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

/*-------------TYPES OF LINKED LISTS---------------*/
typedef struct listNode {
	int* dataPtr;
	struct listNode* next;
}ListNode;

typedef struct list
{
	ListNode* head;
	ListNode* tail;
}List;
/*-------------TYPES OF TREES---------------*/
typedef struct treeNode
{
	unsigned int data;
	struct treeNode *left;
	struct treeNode *right;
}TNODE;

typedef struct tree
{
	TNODE *root;
}Tree;
/*-------------TYPES OF REPRESENT PIC---------------*/
typedef struct _grayImage {

	unsigned short rows, cols;

	unsigned char **pixels;

} grayImage;

typedef unsigned short imgPos[2];
/*-------------TYPES TO SAVE SEGMANT---------------*/
typedef struct _treeNode {

	imgPos position;

	struct _treeNodeListCell *next_possible_positions; // list of locations

} TreeNode;

typedef struct _treeNodeListCell {

	TreeNode * node;

	struct _treeNodeListCell * next;

} TreeNodeListCell;

typedef struct _segment {

	TreeNode * root;

} Segment;
/*-------------TYPES OF LISTS TO STORE LOCATIONS---------------*/
typedef struct imgPosCell {

	imgPos position;

	struct imgPosCell *next, *prev;

} imgPosCell;

typedef struct _imgPosList {

	imgPosCell *head, *tail;

} imgPosList;
#include "func.h"
#include "funcHelpers.h"
#include "lists.h"
#include "trees.h"

#endif //__TYPES_H