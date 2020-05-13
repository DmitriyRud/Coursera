/*
   C for Everyone: Structured programming
   Week 4 Assignment : Files & Arrays (Option 1)
   1. Open and read a file of integers into an array that is created with the first integer
   telling you how many to read.
   2. Then compute their average as a double and their max  as an int.
   3. Print all this out neatly to the screen and to an output file named answer-hw3.

   Author: Dmitriy Rudakov
   Date: May 13, 2020
*/

#include <stdio.h>
#include <stdlib.h>

double get_average(int data[], int size)
/* Function to calculate average of array data */
{
	double res = 0;

	for(int i = 1; i <= size; ++i)
		res += ((double)data[i - 1] - res)/i;
	return res;
}

int get_max(int data[], int size)
/* Function to calculate max element of data array */
{
	int max = data[0];
	
	for(int i = 1; i < size; ++i)
		if (data[i] > max)
			max = data[i];
	return max;
}

void print_array(int data[], int size, char *title)
/* Function which prints our array to the screen */
{
	printf("%s", title);
	for (int i = 0; i < size - 1; ++i)
		printf("%d, ", data[i]);
	printf("%d\n", data[size - 1]);
}

void print_tofile(FILE *ifp, int data[], int size, char *title)
/* Function which prints our array to the file */
{
	fprintf(ifp, "%s", title);
	for (int i = 0; i < size - 1; ++i)
	{
		fprintf(ifp, "%d, ", data[i]);
	}
	fprintf(ifp, "%d\n", data[size - 1]);
}

int main(int argc, char **argv)
{
	FILE	*fp, *fp2;
	int		how_many;
	double	average = 0.0;
	int		max;

	if (argc < 2)										/* If no arguments we will ask to add it */
	{
		printf("Usage: week3 <filename>\n");
		return 1;
	}
	fp = fopen(argv[1], "r");							/* Opening the file to read from */
	if (fp == NULL)
	{
		printf("Error opening the file \"%s\"\n", argv[1]);
		return 2;
	}
	fscanf(fp, "%d", &how_many);							/* Reading the size of data array */
	int data[how_many];
	for(int i = 0; i < how_many; ++i)						/* Reading our array */
		fscanf(fp, "%d", &data[i]);
	average = get_average(data, how_many);					/* Calculating the average */
	max = get_max(data, how_many);							/* Calculating the max element */
	print_array(data, how_many, "Initial array :\n");		/* Printing array to the screen */
	fp2 = fopen("answer-hw3", "w+");						/* Opening the file to write result */
	print_tofile(fp2, data, how_many, "Initial array :\n");/* Printing the array to file */
	printf("Average is : %f\n", average);					/* Printing average to the screen */
	fprintf(fp2, "Average is : %f\n", average);				/* Printing average to the file */
	printf("Max is : %d\n", max);							/* Printing max element to the screen */
	fprintf(fp2, "Max is : %d\n", max);						/* Printing max element to the file */

	fclose(fp);												/* Closing our files */
	fclose(fp2);
	return 0;
}
