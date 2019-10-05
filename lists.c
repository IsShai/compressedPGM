#include "types.h"

void freeImgPosList(imgPosList* lst)
{ // free the allocate memory 
	imgPosCell *curr;
	imgPosCell * next;
	curr = lst->head;
	next = NULL;

	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	lst->head = lst->tail = NULL;
}


imgPosCell * createNewImgPosCell(imgPos data, imgPosCell* next, imgPosCell* prev)
{ // create new list node 
	imgPosCell* res;
	res = (imgPosCell*)malloc(sizeof(imgPosCell));
	checkMemoryAllocation(res);
	res->position[0] = data[0];
	res->position[1] = data[1];
	res->next = next;
	res->prev = prev;
	return res;

}
void makeEmptyImgPosList(imgPosList * lst)   
{// function get list and make it empty 
	lst->head = lst->tail = NULL;
}
void insertDataToEndImgPosList(imgPosList * lst, imgPos position)
{// insert data to the end of the list 
	imgPosCell* newTail;
	newTail = createNewImgPosCell(position, NULL, NULL);
	insertNodeToEndImgPosList(lst, newTail);

}

void insertNodeToEndImgPosList(imgPosList* lst, imgPosCell* tail)  // insert data to the end of the list 
{
	if (isEmptyImgPosList(lst) == TRUE)
	{
		tail->next = tail->prev = NULL;
		lst->head = lst->tail = tail;

	}
	else
	{
		tail->prev = lst->tail;
		tail->next = NULL;
		lst->tail->next = tail;
		lst->tail = tail;
	}

}

BOOL isEmptyImgPosList(imgPosList* lst)  // function return true if the list is empty, else return false 
{
	if (lst->head == NULL)
		return TRUE;
	else
		return FALSE;

}

/*----------------------------------*/


/*----------------------------------*/

void printImgPosList(imgPosList* lst)   // print the list 
{
	imgPosCell* tmp;
	tmp = lst->head;

	while (tmp != NULL)
	{
		printf("[%d,%d] -->> ", tmp->position[0], tmp->position[1]);
		tmp = tmp->next;
	}

}

