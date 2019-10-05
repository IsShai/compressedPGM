#ifndef __TREES_H
#define __TREES_H
#include "types.h"

//------  TREE FUNCTIONS---------//
TNODE* createNewTNode(int data, TNODE *left, TNODE *right);  // create new tree node 
void makeEmptyTreeNodeListCell(TreeNodeListCell * lst);  // make empty tree node list cell 
TreeNodeListCell* createTreeNodeListCell(TreeNode* node);  // create tree node lisr cell 
void addTNLC(TreeNode* node, TreeNodeListCell* nodeToAdd); // add tree node list cell 
BOOL isEmptyTreeNodeListCell(TreeNodeListCell* lst); // check if the list is empty 
TreeNode* createNewTreeNodeOfSegment(imgPos position, TreeNodeListCell *next_possible_positions); // create a new tree node of segment 

#endif //__TREES_H
