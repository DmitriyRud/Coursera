/*
   C for Everyone: Structured programming
   Week 4 Honors Assignment : Files & Arrays 2 binary tree
   1. Open and read a file of integer pairs into an array that is created with the first integer
   telling you how many to read.  
   2. Write a routine that places these values into a binary tree structure.
   3. Then walk the tree “inorder” and print these values to the screen.
   Author: Dmitriy Rudakov
   Date: May 13, 2020
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct	Node
/* Description of node of our binary tree */
{
    int		data;
    struct	Node *left, *right;
}				Node;

Node* newNode(int data)
/* Function which creates the new node */
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

Node* insertLevelOrder(int arr[], Node* root, int i, int n)
/* Function which inserts the nodes to the tree from our array */
{
	if (i < n)
	{
		Node* temp = newNode(arr[i]);
		root = temp;
		/* inserting the left child */
		root->left = insertLevelOrder(arr, root->left, 2 * i + 1, n);
		/* inserting the right child */
		root->right = insertLevelOrder(arr, root->right, 2 * i + 2, n);
	}
	return root;
}

void inOrder(Node* root)
/* Function which prints our tree "inorder" */
{
	if (root != NULL)
	{
		inOrder(root->left);
		printf("%d ",root->data);
		inOrder(root->right);
	}
}

void print_array(int data[], int size, char *title)
/* Function which prints our array to the screen */
{
	printf("%s", title);
	for (int i = 0; i < size - 1; ++i)
		printf("%d, ", data[i]);
	printf("%d\n", data[size - 1]);
}

int main(int argc, char **argv)
{
	FILE	*fp;
	int		how_many;

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
	print_array(data, how_many, "Initial array :\n");		/* Printing array to the screen */
	Node *root = insertLevelOrder(data, root, 0, how_many); /* Inserting our array to binary tree */
	printf("\nBinary tree inorder :\n");
	inOrder(root);											/* Printing binary tree "inorder" */
	printf("\n");
	fclose(fp);												/* Closing our file */
	return 0;
}
