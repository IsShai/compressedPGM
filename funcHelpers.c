#include "types.h"

////////////////////////////////////////            Q1   HELPERS        ////////////////////////////////////////
long int fileSize(FILE *file)/*return file size*/
{

	int res;
	fseek(file, 0, SEEK_END);
	res = ftell(file);
	fseek(file, 0, SEEK_SET);

	return res;
}

//if NULL - then not enough place in memory -- close program
void checkMemoryAllocation(void *ptr)
{
	if (ptr == NULL)
	{
		puts("A memory allocation error has been detected");
		exit(1);
	}
}

////////////////////////////////////////            Q2   HELPERS        ////////////////////////////////////////
BOOL** bucketMatrix(unsigned short row, unsigned short col)
{ //function create and return a BOOL** matrix with all False inside 
	int i, j;
	BOOL** mat;
	mat = (BOOL**)malloc((col) * sizeof(int) * sizeof(BOOL*));  // allocate memory 
	checkMemoryAllocation(mat);
	for (i = 0; i < row; i++)  // run for the rows 
	{
		mat[i] = (BOOL*)malloc(row * sizeof(int) * sizeof(BOOL));
		checkMemoryAllocation(mat[i]);
	}
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			mat[i][j] = FALSE;  // make all fileds with 0 

		}

	}
	return mat;
}


void findSingleSegmentHelper(grayImage *img, imgPos root, imgPos newRoot, unsigned char threshold, BOOL** bucket, TreeNode* nodeRoot)
{// q2 helper 
	int i;
	TreeNode* node;
	imgPos* neighbors;
	TreeNodeListCell* tnlc;
	int size;
	neighbors = findRootList(img, root, newRoot, threshold, bucket, &size);// Return the number of the TreeNode's neighbors ...
	if (size == 0) //Stop Condition
		return;
	else
	{
		for (i = 0; i < size; i++)
		{
			if (bucket[neighbors[i][0]][neighbors[i][1]] == FALSE)//Not node in the tree yet...
			{
				node = createNewTreeNodeOfSegment(neighbors[i], NULL);//Process to create new neighbor and push "him" to the end of the list
				tnlc = createTreeNodeListCell(node);
				addTNLC(nodeRoot, tnlc);
				bucket[neighbors[i][0]][neighbors[i][1]] = TRUE;// switch the flag-->> New neighbor join to the neighborhood ;-)
				findSingleSegmentHelper(img, root, neighbors[i], threshold, bucket, node);// Recursive Call
			}
		}
		if (nodeRoot->position[0] == root[0] && nodeRoot->position[1] == root[1])

			if (neighbors != NULL && (nodeRoot->position[0] != root[0] && nodeRoot->position[1] != root[1]))
				free(neighbors);
		
				bucket[nodeRoot->position[0]][nodeRoot->position[1]] = TRUE;
	}
}

void printBucket(BOOL** bucket, unsigned short row, unsigned short col)
{// print the bucket
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (bucket[i][j] == TRUE)
				printf("[%d]", bucket[i][j]);
			else
				printf(" %d ", bucket[i][j]);
		}
		printf("\n");
	}
	return;
}

void freeSegment(grayImage *img, imgPos start, unsigned char threshold, Segment seg, BOOL** bucket)
{ // free allocated memory of the segment
	freeSegmentHelper(img, start, threshold, bucket, seg.root);
	free(seg.root);
	printBucket(bucket, img->rows, img->cols);
	freeBucket(bucket, img->rows, img->cols);
	return;
}

void freeBucket(BOOL** bucket, unsigned short row, unsigned short col)
{// free all bucket allocated memory 
	int i;
	for (i = 0; i < row; i++)
		free(bucket[i]);
	free(bucket);
}
void freeMatrix(unsigned char** mat, unsigned short row, unsigned short col)
{// fun free matrix - all allocated memory 
	int i;
	for (i = 0; i < row; i++)
		free(mat[i]);
	free(mat);
}


imgPos* findRootList(grayImage* img, imgPos rootStart, imgPos start, unsigned char threshold, BOOL** bucket, int* neighbors)
{// fun returns an array with all the possiable neighbors
	*neighbors = 0;
	imgPos* des = (imgPos*)malloc(8 * sizeof(imgPos));
	checkMemoryAllocation(des);
	if (des == NULL)
	{
		puts("A memory allocation error has been detected");
		exit(1);
	}
	bucket[start[0]][start[1]] = TRUE;
	imgPos newRoot;
	unsigned short maxRow = img->rows;
	unsigned short maxCol = img->cols;
	/*-----CASE 1---------*/
	//
	// run all the casses to check for spasific coordinate 
	if (start[0] != 0 && start[1] != 0)
	{
		newRoot[0] = start[0] - 1;
		newRoot[1] = start[1] - 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				des[*neighbors][0] = newRoot[0];
				des[*neighbors][1] = newRoot[1];
				*neighbors = *neighbors + 1;
			}
		}
	}
	/*-----CASE 2---------*/
	if (start[0] != 0)
	{
		newRoot[0] = start[0] - 1;
		newRoot[1] = start[1];
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				des[*neighbors][0] = newRoot[0];
				des[*neighbors][1] = newRoot[1];
				*neighbors = *neighbors + 1;
			}
		}
	}
	/*-----CASE 3---------*/
	if (start[1] + 1 < maxCol && start[0] != 0)
	{
		newRoot[0] = start[0] - 1;
		newRoot[1] = start[1] + 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				des[*neighbors][0] = newRoot[0];
				des[*neighbors][1] = newRoot[1];
				*neighbors = *neighbors + 1;
			}
		}
	}
	/*-----CASE 4---------*/
	if (start[1] + 1 < maxCol)
	{
		newRoot[0] = start[0];
		newRoot[1] = start[1] + 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				des[*neighbors][0] = newRoot[0];
				des[*neighbors][1] = newRoot[1];
				*neighbors = *neighbors + 1;
			}
		}
	}
	/*-----CASE 5---------*/
	if (start[0] + 1 < maxRow&&start[1] + 1 < maxCol)
	{
		newRoot[0] = start[0] + 1;
		newRoot[1] = start[1] + 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				des[*neighbors][0] = newRoot[0];
				des[*neighbors][1] = newRoot[1];
				*neighbors = *neighbors + 1;
			}
		}
	}
	/*
	-----CASE 6---------*/
	if (start[0] + 1 < maxRow)
	{
		newRoot[0] = start[0] + 1;
		newRoot[1] = start[1];
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				des[*neighbors][0] = newRoot[0];
				des[*neighbors][1] = newRoot[1];
				*neighbors = *neighbors + 1;
			}
		}
	}
	/*-----CASE 7---------*/
	if (start[0] + 1 < maxRow&&start[1] != 0)
	{
		newRoot[0] = start[0] + 1;
		newRoot[1] = start[1] - 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				des[*neighbors][0] = newRoot[0];
				des[*neighbors][1] = newRoot[1];
				*neighbors = *neighbors + 1;
			}
		}
	}
	/*-----CASE 8---------*/
	if (start[1] != 0)
	{
		newRoot[0] = start[0];
		newRoot[1] = start[1] - 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				des[*neighbors][0] = newRoot[0];
				des[*neighbors][1] = newRoot[1];
				*neighbors = *neighbors + 1;
			}
		}
	}

	if (*neighbors != 0)
	{
		des = (imgPos*)realloc(des, (*neighbors) * sizeof(imgPos));
		return des;
	}
	free(des);
	des = NULL;
	return des;
}


void freeSegmentHelper(grayImage *img, imgPos root, unsigned char threshold, BOOL** bucket, TreeNode* nodeRoot)
{// free segment helper. Rec
	TreeNodeListCell* curr;
	int counter = 0;
	if (nodeRoot->next_possible_positions == NULL)
	{
		bucket[nodeRoot->position[0]][nodeRoot->position[1]] = FALSE;
		free(nodeRoot->next_possible_positions);
		free(nodeRoot);
		return;
	}
	else
	{
		curr = nodeRoot->next_possible_positions;

		while (curr->next != NULL)
		{
			curr = curr->next;
			 freeSegmentHelper(img, root, threshold, bucket, curr->node);
		}
		curr = nodeRoot->next_possible_positions;
			freeSegmentHelper(img, root, threshold, bucket, curr->node);
		bucket[nodeRoot->position[0]][nodeRoot->position[1]] = FALSE;
		free(nodeRoot->next_possible_positions->node);
			free(nodeRoot->next_possible_positions);
			free(nodeRoot);

	}


}

void printMatrix(unsigned char** str, unsigned short rows, unsigned short  cols)
{// print a matrix
	int i, j;
	printf("++++++++++cols is: %hhu, rows is : %hhu \n", cols, rows);
	for (i = 0; i<rows; i++) // run for the rows
	{
		for (j = 0; j<cols; j++) // run for the lines  
			printf("%3hhu ", (str[i][j])); // print the value 
										   //printf("%3d ", (str[i][j])); // print the value
		printf("\n");  // new line 
	}

}
////////////////////////////////////////            Q3   HELPERS        ////////////////////////////////////////

imgPosCell* findRootListNew(imgPosList* lst, grayImage* img, imgPos rootStart, imgPos start, unsigned char threshold, BOOL** bucket, int* neighbors)
{// fun returns an array with all the possiable neighbors
	*neighbors = 0;
	bucket[start[0]][start[1]] = TRUE;
	imgPos newRoot;
	unsigned short maxRow = img->rows;
	unsigned short maxCol = img->cols;

	/*-----CASE 1---------*/
	// run all the casses to check for spasific coordinate 
	if (start[0] != 0 && start[1] != 0)
	{
		newRoot[0] = start[0] - 1;
		newRoot[1] = start[1] - 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				bucket[newRoot[0]][newRoot[1]] == TRUE;
				insertDataToEndImgPosList(lst, newRoot);
				*neighbors = *neighbors + 1;
				RunRightAndDown(img, newRoot, rootStart, threshold, bucket, lst, neighbors);
			}
		}
	}
	/*-----CASE 2---------*/
	if (start[0] != 0)
	{
		newRoot[0] = start[0] - 1;
		newRoot[1] = start[1];
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				bucket[newRoot[0]][newRoot[1]] == TRUE;
				insertDataToEndImgPosList(lst, newRoot);
				*neighbors = *neighbors + 1;
				RunRightAndDown(img, newRoot, rootStart, threshold, bucket, lst, neighbors);
			}
		}
	}
	/*-----CASE 3---------*/
	if (start[1] + 1 < maxCol && start[0] != 0)
	{
		newRoot[0] = start[0] - 1;
		newRoot[1] = start[1] + 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				bucket[newRoot[0]][newRoot[1]] == TRUE;
				insertDataToEndImgPosList(lst, newRoot);
				*neighbors = *neighbors + 1;
				RunRightAndDown(img, newRoot, rootStart, threshold, bucket, lst, neighbors);
			}
		}
	}
	/*-----CASE 4---------*/
	if (start[1] + 1 < maxCol)
	{
		newRoot[0] = start[0];
		newRoot[1] = start[1] + 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				bucket[newRoot[0]][newRoot[1]] == TRUE;
				insertDataToEndImgPosList(lst, newRoot);
				*neighbors = *neighbors + 1;
				RunRightAndDown(img, newRoot, rootStart, threshold, bucket, lst, neighbors);
			}
		}
	}
	/*-----CASE 5---------*/
	if (start[0] + 1 < maxRow&&start[1] + 1 < maxCol)
	{
		newRoot[0] = start[0] + 1;
		newRoot[1] = start[1] + 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				bucket[newRoot[0]][newRoot[1]] == TRUE;
				insertDataToEndImgPosList(lst, newRoot);
				*neighbors = *neighbors + 1;
				RunRightAndDown(img, newRoot, rootStart, threshold, bucket, lst, neighbors);
			}
		}
	}
	/*
	-----CASE 6---------*/
	if (start[0] + 1 < maxRow)
	{
		newRoot[0] = start[0] + 1;
		newRoot[1] = start[1];
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				bucket[newRoot[0]][newRoot[1]] == TRUE;
				insertDataToEndImgPosList(lst, newRoot);
				*neighbors = *neighbors + 1;
				RunRightAndDown(img, newRoot, rootStart, threshold, bucket, lst, neighbors);
			}
		}
	}
	/*-----CASE 7---------*/
	if (start[0] + 1 < maxRow&&start[1] != 0)
	{
		newRoot[0] = start[0] + 1;
		newRoot[1] = start[1] - 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				bucket[newRoot[0]][newRoot[1]] == TRUE;
				insertDataToEndImgPosList(lst, newRoot);
				*neighbors = *neighbors + 1;
				RunRightAndDown(img, newRoot, rootStart, threshold, bucket, lst, neighbors);
			}
		}
	}
	/*-----CASE 8---------*/
	if (start[1] != 0)
	{
		newRoot[0] = start[0];
		newRoot[1] = start[1] - 1;
		if (abs((img->pixels[rootStart[0]][rootStart[1]] - img->pixels[newRoot[0]][newRoot[1]])) <= threshold)
		{
			if (bucket[newRoot[0]][newRoot[1]] == FALSE)
			{
				bucket[newRoot[0]][newRoot[1]] == TRUE;
				insertDataToEndImgPosList(lst, newRoot);
				*neighbors = *neighbors + 1;
				RunRightAndDown(img, newRoot, rootStart, threshold, bucket, lst, neighbors);
			}
		}
	}

	if (*neighbors != 0)
	{	
		return lst->tail;
	}
	
	return NULL;
}
//---------------------------------------------------------------------------
void findAllSegmentsHelperNew(grayImage *img, imgPos root, imgPos newRoot, unsigned char threshold, BOOL** bucket, imgPosList* lst)
{// q3 recursion helper.
	int i;
	imgPosCell* curr;
	int size;
	curr = findRootListNew(lst,img, root, newRoot, threshold, bucket, &size);// Return the number of the TreeNode's neighbors ...
	if (size == 0) //Stop Condition
		return;
	else
	{
		for (i = 0; i < size-1; i++)
		{
			curr = curr->prev;//Back to the first neighbor to check...<<---
		}
		for (i = 0; i < size; i++)
		{
				findAllSegmentsHelperNew(img, root, curr->position, threshold, bucket, lst);// Recursive Call
			curr = curr->next;//Next to the new one--->>
		}
		bucket[lst->tail->position[0]][lst->tail->position[1]] = TRUE;
	}
}

//-------------------------------------------------------------------
void RunRightAndDown(grayImage* img, imgPos pos, imgPos originalRoot, unsigned char threshold, BOOL** bucket, imgPosList* lst, int* counter)
{// run to the right and down the lines on the spasific lines. for more possabile neighberhoods- and adds them to the list
	int x, y;
	x = pos[1];
	y = pos[0];
	x++;
	imgPos temp;
	temp[0] = y;
	temp[1] = x;
	while ((x < img->cols) && (abs((img->pixels[originalRoot[0]][originalRoot[1]] - img->pixels[y][x])) <= threshold) && (bucket[y][x] == FALSE))
	{
		bucket[y][x] = TRUE;
		insertDataToEndImgPosList(lst, temp);
		*counter = *(counter) + 1;
		x++;
		temp[1] = x;
	}
	x = pos[1];
	y++;
	temp[0] = y;
	temp[1] = x;
	while ((y < img->rows) && (abs((img->pixels[originalRoot[0]][originalRoot[1]] - img->pixels[y][x])) <= threshold) && (bucket[y][x] == FALSE))
	{
		bucket[y][x] = TRUE;
		insertDataToEndImgPosList(lst, temp);
		*counter = *(counter) + 1;
		y++;
		temp[0] = y;
	}

	return;
}


////////////////////////////////////////            Q5   HELPERS        ////////////////////////////////////////

unsigned char maxOfBitByMaxGray(unsigned char max_gray_level) //function get a number, and returns the max of bit he requires. 
{
	return (log(max_gray_level) / log(2)) + 1; // find the maximum of number of bits. 
}


unsigned char convertPix(unsigned char pix, unsigned char max_gray_level)
{// calc the new value with the formula
	unsigned char res;
	res = (pix * max_gray_level) / 255;
	return res;
}


////////////////////////////////////////            Q6   HELPERS        ////////////////////////////////////////

void makePGMfileFromArray(unsigned char* ptr, unsigned short cols, unsigned short rows, unsigned short max, char* pgm_file_name)
{/// function get an array, rows, cols and max gray level. and create a pgm picture.
	char* suffix = ".pgm";
	char* PGMFileNameNew = (char*)calloc(sizeof(char), strlen(pgm_file_name) + strlen(suffix) + 1);
	strcpy(PGMFileNameNew, pgm_file_name);
	strcat(PGMFileNameNew, suffix);
	char space = ' ', newLine = '\n';
	FILE* fp;
	int count = 0;
	unsigned int i, j;
	fp = fopen(PGMFileNameNew, "w");
	if (fp == NULL) {
		perror("Error");
	}
	fprintf(fp, "%s%c%hu%c%hu%c%hu%c", "P2", newLine, cols, space, rows, newLine, max, newLine); // put the P2, COLS ROWS, AND MAX
	for (i = 0; i<rows; i++)
	{
		for (j = 0; j<cols; j++)
		{
			if (j == 0)
				fprintf(fp, "%hu", ptr[count]);  // insert the array into val into pgm 
			else
				fprintf(fp, " %hu", ptr[count]);  // insert the array val into the pgm 
			count++;
		}
			fprintf(fp, "%c", newLine);
	}

	fclose(fp); //closing file 
	free(PGMFileNameNew);
}

////////////////////////////////////////            Q7   HELPERS        ////////////////////////////////////////

void freeGrayImage(grayImage* img)// fun free all gray image allocated memory 
{
	int i, j;
	for (i = 0; i < img->rows; i++) // run for rows
		free(img->pixels[i]); // free

	free(img->pixels); // free img

	return;
}


grayImage* case1Menu(grayImage* image,char* fileName)
{// menu case1 
	
	char* suffix = ".pgm";
	if (image != NULL)
	{
		freeGrayImage(image);
		image = NULL;
	}
	printf("\nPlease enter the PGM file name (without the suffix '.pgm'), and then press enter: \n");
	scanf("%s", fileName);
	strcat(fileName, suffix);
	image = readPGM (fileName);
	if (image != NULL)
		printf("\nThe file uploaded successfully!!!\n\n");
	return image;
}

void case2Menu(grayImage* image, char* fileName, imgPosList** segments, int* numOfSegments)
{// menu case2
	unsigned char threshold;
	printf("\nPlease enter THRESHOLD (between 0-255) for the segments:\n");
	scanf("%hhu", &threshold);
	*(numOfSegments) = findAllSegments(image, threshold, segments);
	return;
}

grayImage* case3Menu(imgPosList** segments, imgPosList* coolList, int numOfSegments)
{// menu case3
	grayImage* imageAfterColored;
	coolList = (imgPosList*)malloc(numOfSegments * sizeof(imgPosList));
	for (int i = 0; i<numOfSegments; i++)
	{
		coolList[i] = *(segments[i]);
	}
	imageAfterColored = colorSegments(coolList, numOfSegments);
	return imageAfterColored;
}
void case4Menu(grayImage* coloredImage, char* fileName)
{// menu case4
	unsigned char max_gray_level;
	char* suffix = "_CompressedColoredImg.bin";
	char* compressedFileName = (char*)calloc(sizeof(char), strlen(fileName) + strlen(suffix) + 1); // the new size + '/0'
	strcpy(compressedFileName, fileName);
	strcat(compressedFileName, suffix);
	printf("Please enter the MAX GRAY level to compress the image by the new gray level: \n");
	scanf("%hhu", &max_gray_level);
	saveCompressed(compressedFileName, coloredImage, max_gray_level);
	printf("\nThe COLORED image has been COMPRESSED and SAVED!\n");
	printf("the name of the new COMPRESSED file is:\n %s \n", compressedFileName);
	free(compressedFileName);
	return;

}
void case5Menu(grayImage* image)
{// menu case5
	char* suffix = ".bin";
	char compressedFileName[MAX_FILE_NAME];
	unsigned char max_gray_level;
	printf("\nPlease enter name for the NEW compress file, and then press enter: \n");
	scanf("%s", compressedFileName);
	char* compressedBin = (char*)calloc(sizeof(char), strlen(compressedFileName) + strlen(suffix) + 1);
	strcpy(compressedBin, compressedFileName);
	strcat(compressedBin, suffix);
	printf("\nPlease enter the MAX GRAY level to compress the image by the new gray level: \n");
	scanf("%hhu", &max_gray_level);
	saveCompressed(compressedBin, image, max_gray_level);
	free(compressedBin);
	return;

}
void case6Menu()
{// menu case6
	char* suffix = ".bin";
	char compressedFileName[MAX_FILE_NAME];
	char newPGMfileName[MAX_FILE_NAME];
	printf("\nPlease enter name of the compressed file (without the suffix '.bin')\n to convert it to PGM format, and then press enter: \n");
	scanf("%s", compressedFileName);
	char* compressedBin = (char*)calloc(sizeof(char), strlen(compressedFileName) + strlen(suffix) + 1);
	strcpy(compressedBin, compressedFileName);
	strcat(compressedBin, suffix);
	printf("\nPlease enter name for the NEW PGM file, and then press enter: \n");
	scanf("%s", newPGMfileName);
	convertCompressedImageToPGM(compressedBin, newPGMfileName);
	printf("\n A NEW PGM file has been create!!!\n");
	free(compressedBin);
	return;
}



unsigned char maxGrayLevelOfPGMPic(grayImage* image)
{// finds the pixale with the max gray level
	unsigned char max = image->pixels[0][0];
	int i, j;
	for (i = 0; i < image->rows; i++)
	{
		for (j = 0; j < image->cols; j++)
		{
			if (image->pixels[i][j] > max)
				max = image->pixels[i][j];
		}
	}
	return max;
}



void insertFromTreeNLCToList(grayImage *img, imgPos root, unsigned char threshold, BOOL** bucket, TreeNode* nodeRoot, imgPosList* lst)
{// insert from tree node list to list.
	TreeNodeListCell* curr;
	if (nodeRoot->next_possible_positions == NULL)
	{
		bucket[nodeRoot->position[0]][nodeRoot->position[1]] = TRUE;
		insertDataToEndImgPosList(lst, nodeRoot->position);
		return;
	}
	else
	{
		curr = nodeRoot->next_possible_positions;

		while (curr->next != NULL)
		{
			curr = curr->next;
			insertFromTreeNLCToList(img, root, threshold, bucket, curr->node,lst);
		}
		curr = nodeRoot->next_possible_positions;
		insertFromTreeNLCToList(img, root, threshold, bucket, curr->node, lst);
		bucket[nodeRoot->position[0]][nodeRoot->position[1]] = TRUE;

		insertDataToEndImgPosList(lst, nodeRoot->position);
	}
}


//-------------------------------------------------------------------------------
