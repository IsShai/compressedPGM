#include "types.h"

TNODE* createNewTNode(int data, TNODE *left, TNODE *right)
{// create new tree node 
	TNODE *res;
	res = (TNODE*)malloc(sizeof(TNODE));
	checkMemoryAllocation(res);
	res->data = data;
	res->left = left;
	res->right = right;
	return res;
}

void makeEmptyTreeNodeListCell(TreeNodeListCell * lst)  // function get list and make it empty 
{
	lst = NULL;
}

TreeNodeListCell* createTreeNodeListCell(TreeNode* node)
{
	TreeNodeListCell* res;
	res = (TreeNodeListCell*)malloc(sizeof(TreeNodeListCell));
	checkMemoryAllocation(res);
	res->node = node;
	res->next = NULL;
	return res;

}


void addTNLC(TreeNode* node, TreeNodeListCell* nodeToAdd)
{ // add tree node list cell 
	TreeNodeListCell* curr;
	if (node->next_possible_positions == NULL)
	{
		node->next_possible_positions = nodeToAdd;
	}
	else {

		for (curr = node->next_possible_positions; curr->next != NULL; curr = curr->next);
		curr->next = nodeToAdd;
	}


}

BOOL isEmptyTreeNodeListCell(TreeNodeListCell* lst)  // function return true if the list is empty, else return false 
{ // check if the list is empty 
	if (lst == NULL)
		return TRUE;
	else
		return FALSE;

}

TreeNode* createNewTreeNodeOfSegment(imgPos position, TreeNodeListCell *next_possible_positions)
{// create a new tree node of segment 
	TreeNode* res;
	res = (TreeNode*)malloc(sizeof(TreeNode));
	checkMemoryAllocation(res);
	if (res == NULL)
	{
		puts("A memory allocation error has been detected");
		exit(1);
	}
	res->position[0] = position[0];  // put the x val
	res->position[1] = position[1]; // put the y val
	res->next_possible_positions = next_possible_positions;  
	return res;
}