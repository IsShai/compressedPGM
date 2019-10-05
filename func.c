#include "types.h"
void display_progress_bar(int p);
void print_n_chars(int n, int c);
// 
////////////////////////////////////////            Q1           ////////////////////////////////////////
grayImage *readPGM(char *fname)/*Q1 function*/
{//function gets a name of a text file and returns a grayimage file 
	FILE *fp1;
	unsigned short N, M, maxGray, i, j, cols, rows;
	unsigned char **matrix;
	char dummy;
	unsigned char data;
	long int fSize;
	grayImage *res;

	res = (grayImage*)malloc(sizeof(grayImage) * 1);
	checkMemoryAllocation(res);
	fp1 = fopen(fname, "rt");// open file 
	if (fp1 == NULL) {
		perror("Error");
	}
	fSize = fileSize(fp1); 
	while (1)
	{
		dummy = fgetc(fp1);
		if (dummy == '\n')
			break;
	}
	fscanf(fp1, "%hu %hu %hu", &N, &M, &maxGray); // gettig the first values from the text 
	cols = N;
	rows = M;
	res->cols = N;
	res->rows = M;
	res->pixels = (unsigned char**)malloc(M * sizeof(unsigned char*));
	for (i = 0; i < M; i++)
	{
		res->pixels[i]= (unsigned char*)malloc(sizeof(unsigned char)*N);
	}

	i = j = 0;

	while (ftell(fp1)<fSize)                                           //fill Matrix Data from txt
	{

		fscanf(fp1, "%hhu", &data);  // getting the char from the text 
		res->pixels[i][j] = data;
		j++;
		if ((i + 1)*(j) == cols*rows)                                    //end of matrix
			break;

		if (j == cols)                                                  //New Line
		{
			j = 0;
			i++;
		}
	}
	//printMatrix(res->pixels, res->rows, res->cols);  
	printf("\n");
	fclose(fp1);  // closing file 
   return res;
}

////////////////////////////////////////            Q2          ////////////////////////////////////////

Segment findSingleSegment(grayImage *img, imgPos start, unsigned char threshold)
{//Q2 - the function gets a grayimg, position and a threshols and returns 
       // a segment that has all this postion's neighbors that their distance is no larger that threshold 
	Segment newSegment;
	BOOL** bucketMat;
	bucketMat = bucketMatrix(img->rows, img->cols);  // make bucket list 
	newSegment.root = createNewTreeNodeOfSegment(start, NULL);  // create a new tree nodr of segment 
	findSingleSegmentHelper(img, start, start, threshold, bucketMat, newSegment.root);
	freeSegment(img, newSegment.root->position, threshold, newSegment, bucketMat);
	freeBucket(bucketMat, img->rows, img->cols);
	return newSegment;

}

////////////////////////////////////////            Q3          ////////////////////////////////////////
int findAllSegments(grayImage* img, unsigned char threshold, imgPosList** segments)
{//Q3 - the function gets a grayimage and a threshold
//      and returns the number of different segamets, and return by pointer an array of lists of all the segments. 
	int i, j, size = 0;
	imgPos start;
	BOOL** bucketMat;
	Segment seg;
	bucketMat = bucketMatrix(img->rows, img->cols);
	imgPosList temp;

	for (i = 0; i<img->rows; i++) // RUN for rows 
	{
		for (j = 0; j<img->cols; j++)  // run for cols 
		{
			if ((bucketMat[i][j]) == FALSE)  // do it only for a cell that is not on any list yet 
			{
				segments[size] = (imgPosList*)malloc(sizeof(imgPosList));  // malloc the list 
				checkMemoryAllocation(segments[size]);
				makeEmptyImgPosList(segments[size]);  // make an empty list 
				start[0] = i;
				start[1] = j;  // put the rellevant position 
				insertDataToEndImgPosList(segments[size], start);  // insert the first start pos to the list 
				findAllSegmentsHelperNew(img, start, start, threshold, bucketMat, segments[size]);
				size++;
				//////	printf ("\n");
			}
		}
	}
	//printBucket(bucketMat, img->rows, img->cols);
	segments = (imgPosList**)realloc(segments, size * sizeof(imgPosList*));
	freeBucket(bucketMat, img->rows, img->cols);
	return size;  // return the size 
}


////////////////////////////////////////            Q4          ////////////////////////////////////////

grayImage *colorSegments(imgPosList *segments, unsigned int size)
{//Q4  - - the fucntion gets list of segments - from q3, and change the color of each one of them by a furmola

	unsigned char  x, y;
	unsigned short maxRow = 0, maxCol = 0, logSizeRow = 1, logSizeCol = 1;;
	unsigned int i = 0, j = 0;
	imgPosCell* tmp;
	grayImage * res;
	res = (grayImage *)malloc(sizeof(grayImage)*1); // allocate memory 
	checkMemoryAllocation(res);
	for (i = 0; i<size; i++) // run all over the lists
	{
		tmp = segments[i].head;
		while (tmp != NULL) // find the max x and max y, for the deminstion of the matrix 
		{
			x = tmp->position[0]; 
			y = tmp->position[1];
			if (x > maxRow)
				maxRow = x;
			if (y > maxCol)
				maxCol = y;
			tmp = tmp->next;
		}
	}
	if ((maxCol == 0) || (maxRow == 0))
		exit(1);
	maxCol++;  // make it logic size 
	maxRow++;  // make it logic size 

	res->pixels = (unsigned char**)malloc(maxRow*sizeof(int) * sizeof(unsigned char*));  // allocate memory 
	for (i = 0; i < maxRow; i++)
	{
		res->pixels[i] = (unsigned char*)malloc(sizeof(unsigned char)*maxCol);  // allocate memory 
	}

	//printf("\n col: %d, row: %d \n", maxCol, maxRow);
	for (i = 0; i<size; i++) // run all over the lists
	{
		tmp = segments[i].head;
		while (tmp != NULL)
		{
			x = tmp->position[0];
			y = tmp->position[1];
			res->pixels[x][y] = (((double)255 / (size - 1)) * i);  // calc the correct number for this current segment, in this fourmula.
			tmp = tmp->next;  // moce for the next on the list 
		}
	}
	//printMatrix(res->pixels, maxRow, maxCol);
	res->rows = maxRow; // update the grayimg in cols and rows 
	res->cols = maxCol;
	return res;
}

////////////////////////////////////////            Q5          ////////////////////////////////////////


void saveCompressed(char* file_name, grayImage* image, unsigned char max_gray_level)
{//Q5  -- the function gets a name and a grayimage and save in a bin file the compressed file
	FILE* flBin;
	flBin = fopen(file_name, "wb");
	if (flBin == NULL) {
		perror("Error");
	}
	char* suffix = ".txt";
	char* compFileName = (char*)calloc(sizeof(char), strlen(file_name) + strlen(suffix) + 1);
	strcpy(compFileName, file_name);
	strcat(compFileName, suffix);
	unsigned char maxOfBit = maxOfBitByMaxGray(max_gray_level);
	int i, j, k, counter = 0;
	unsigned char byte = 0;
	unsigned char tempNumber;
	fwrite(&image->rows, sizeof(unsigned short), 1, flBin);//Write to the file : rows, cols, max gray level
	fwrite(&image->cols, sizeof(unsigned short), 1, flBin);
	fwrite(&max_gray_level, sizeof(unsigned char), 1, flBin);

	for (i = 0; i < image->rows; i++)
	{
		for (j = 0; j < image->cols; j++)
		{
			tempNumber = convertPix(image->pixels[i][j], max_gray_level);//Conver by the max gray level
			tempNumber <<= (8 - maxOfBit);// move the bits <<-- by the max gray level

			for (k = 1; k <= maxOfBit; k++)//Run all over the byte after the shifting <<--
			{
				byte <<= 1; //make place for new bit from pNew
				if (tempNumber & (1 << 7))// if the byte is: --> 1000 0000 <-- 
					byte += 1;
				counter++;
				tempNumber <<= 1;
				if (counter == 8)//Condition to insert the new compress byte to the file
				{
					fwrite(&byte, sizeof(unsigned char), 1, flBin);//Write the new compress byte to the file
					byte = 0;
					counter = 0;
				}

			}
		}
	}
	if (counter != 0)
	{
		byte <<= (8 - counter);
		fwrite(&byte, sizeof(unsigned char), 1, flBin);//Write the last compress byte to the file
	}

	fclose(flBin);
	free(compFileName);
	return;
}



////////////////////////////////////////            Q6          ////////////////////////////////////////


void convertCompressedImageToPGM(char *compressed_file_name, char* pgm_file_name)
{ //Q6 - the function gets a compressed bin file. and make a pgm picture from it, with the orignal values
	FILE * fp;
	unsigned short cols, rows, numBits;
	unsigned char c, left, right, max, num;
	int count = 0, i, j, limit, maxGray=0;
	unsigned char * matrix, *temp;
	unsigned long long int buff, helper;
	unsigned char** ptr;
	fp = fopen(compressed_file_name, "rb");
	if (fp == NULL) 
		checkMemoryAllocation(fp);
	fread(&rows, sizeof(unsigned short), 1, fp); // get the rows from the bin file 
	fread(&cols, sizeof(unsigned short), 1, fp);  // get the cols from the bin file 
	fread(&max, sizeof(unsigned char), 1, fp); // get the max from the bin file 
	numBits = maxOfBitByMaxGray(max);  // numBits is the max num of bits that compressed 
	temp = (unsigned char*)malloc(sizeof(unsigned char)*numBits);
	checkMemoryAllocation(temp);
	matrix = (unsigned char*)malloc(sizeof(unsigned char)*cols*rows);          // Create Matrix
	checkMemoryAllocation(matrix);
	for (i = 0; i<rows*cols; i++) // make all the matrix with 0 
	{
		matrix[i] = 0;
	}
	for (j = 0; j<(rows*cols) / numBits; j++)
	{
		for (i = 0; i<numBits; i++) /// saving the unsigned char in an array 
		{
			fread(&c, sizeof(unsigned char), 1, fp);
			temp[i] = c;  // store numBits amount of chars 
		}

		buff = 0;
		for (i = 0; i<numBits; i++)  // put all the bits in an long long int 
		{
			buff = buff | temp[i];
			if (i != numBits - 1)
				buff <<= 8;  // make space for the next number 
		}

		limit = 64 - (8 * numBits);

		for (i = 0; i<8; i++)
		{

			helper = buff;
			helper <<= (limit + (i*numBits)); // make all 0 
			helper >>= (limit + (i*numBits));  // make 0 
			helper >>= (64 - limit - numBits) - numBits*i;
			matrix[count] = helper;
			count++;
			if (count == (rows*cols))
			{
				i = 200; // get out from this loop
				j = (rows*cols) + 100;  // get out of the loop
			}
		}

	}
	fclose(fp);  // closing file 
	//printf("\n");
	for (i = 1; i <= rows*cols; i++) // clac the matrix with the new pervious values
	{
		matrix[i - 1] = (matrix[i - 1] * 255.0) / max;
		if (matrix[i - 1] > maxGray)
			maxGray = matrix[i - 1];
	}

	makePGMfileFromArray(matrix, cols, rows, maxGray, pgm_file_name); // make the pgm file 
	free(matrix); // free the allocate memoery 
	return;
}


////////////////////////////////////////            Q7          ////////////////////////////////////////

void printMenu()
{
	char ch;
	int choice = 0, numOfSegments;
	char fileName[MAX_FILE_NAME];
	char dump [MAX_FILE_NAME];
	imgPosList** segments = NULL;
	grayImage* image = NULL, *imageAfterColered = NULL;
	imgPosList * coolList = NULL;
	printf("Welcome to the Final project menu!!\n\n\n");
	do
	{
		printf("\n\nPLEASE ENTER YOUR CHOISE:  \n\n");
		printf("1.Read an image file in PGM format\n\n");
		printf("2.Find all segments\n\n");
		printf("3.Color all segments\n\n");
		printf("4.Save the colored image in a compressed format\n\n");
		printf("5.Compress and save the original image in a compressed format\n\n");
		printf("6.Convert a compressed image to PGM format\n\n");
		printf("7.Press 7 for EXIT \n\n");
		scanf("%d", &choice);
	

		switch (choice)
		{
		case 1:
			image = case1Menu(image, fileName);
			sleep(1);
			system("clear");
			break;
		case 2:
			if (image == NULL)
			{
				printf("\nYou didn't insert PGM file yet...\n");
				image = case1Menu(image, fileName);
			}
			if (segments != NULL) {
				freeImgPosList(*segments);
				free(segments);
				segments = NULL;
			}
			segments = (imgPosList**)malloc((image->cols*image->rows) * sizeof(imgPosList*));
			case2Menu(image, fileName, segments, &numOfSegments);
			printf("\nAll the segments found!!\n");
			sleep(1);
			system("clear");
			break;
		case 3:
			if (imageAfterColered != NULL) {
				freeGrayImage(imageAfterColered);
				free(imageAfterColered);
			}
				imageAfterColered = NULL;
				if (coolList != NULL) {
					freeImgPosList(coolList);
					free(coolList);
					coolList = NULL;
				}
			imageAfterColered = case3Menu(segments, coolList, numOfSegments);
			printf("\nAll the segments has been colored!\n");
			sleep(1);
			system("clear");
			break;
		case 4:
			case4Menu(imageAfterColered, fileName);
			sleep(2);
			system("clear");
			break;
		case 5:
			case5Menu(image);
			printf("\nThe original image has been COMPRESSED and SAVED!\n");
			sleep(2);
			system("clear");
			break;
		case 6:
			case6Menu();
			printf("\nThe COMPRESSED image CONVERTED to PGM format (bin-->>PGM)\n");
			sleep(2);
			system("clear");
			break;
		case 0:
			printf("\nERROR!! wrong selection!! Please choose number between 1 to 7...\n");
			scanf("%s", dump);
			sleep(2);
			system("clear");
			break;

		case QUIT:
			if (image != NULL) {
				freeGrayImage(image);
				free(image);
			}
			if (imageAfterColered != NULL) {
				freeGrayImage(imageAfterColered);
				free(imageAfterColered);
				}
				if (segments != NULL) {
					freeImgPosList(*segments);
					free(segments);
				}
				if (coolList != NULL) {
					freeImgPosList(coolList);
					free(coolList);
				}
			printf ("\n\t\t\tFinal Project\n\t\tName: Lior Ben Yehuda 305346660\n\t\tName: Shai Hassan 200175131\n\t\tDate: 18.06.2017\n");

				exit(7);
					

		default:
			printf("\nERROR!! wrong selection!! Please choose number between 1 to 7...\n");
			printf("\nWe will back to the MAIN MENU in 2 SECONEDS...");
			sleep(2);
			system("clear");
			}
		} while (choice != 7);
	
	return;
}



