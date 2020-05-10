/*
   C for Everyone: Structured programming
   Week 3. Option 1 : Working with lists
   Use the linear linked list code to store a randomly generated set of 100 integers.
   Now write a routine that will rearrange the list in sorted order of these values.
   Note you might want to use bubble sort to do this. Print these values in rows of 5 on the screen.
   Author: Dmitriy Rudakov
   Date: May 10, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Let's define our list */
typedef struct	list {
	int			data;
	struct list	*next;
}				list;

list* create_list(int d)
/* Function, which create the new list */
{
	list *head = malloc(sizeof(list));
	head->data = d;
	head->next = NULL;
	return head;
}

list* add_to_front(int d, list* h)
/* Function, which adds new element to front of the list */
{
	list* head = create_list(d);
	head->next = h;
	return head;
}

list* fill_random_list(int size)
/* Filling our list with random data */
{
	srand(time(NULL));
	list* head = create_list(rand() % size);
	for (int i = 0; i < size - 1; i++)
	{
		head = add_to_front(rand() % (size + i), head);
	}
	return head;
}

list* sort_list(list *root)
/* Function for sorting our list */
{
	list *new_root = NULL;

	while (root != NULL)										/* While not the end of the list */
	{
		list* node = root;
		root = root->next;
		if (new_root == NULL || node->data < new_root->data)	/* checking if the next node->data higher */
		{
			node->next = new_root;
			new_root = node;
		}
		else
		{
			list* current = new_root;
			while (current->next != NULL && !(node->data < current->next->data))
			{
				current = current->next;
			}
			node->next = current->next;							/* and swapping if no */
			current->next = node;
		}
	}
	return new_root;
}

void print_list(list *h, char* title)
/* Function for printing the list */
{
	int row = 0;

	printf("\n\033[%dm%s\033[0m\n", 36, title);		/* Printing the title with different color */
	while (h != NULL)
	{
		printf("%3d", h->data);
		++row;
		if (row == 5)								/* Print these values in rows of 5 */
		{
			printf("\n");
			row = 0;
		}
		else
			printf(", ");
		h = h->next;
	}
}

int	main(void)
{
	list* head = NULL;
	
	head = fill_random_list(100);
	print_list(head, "Initial list :");
	head = sort_list(head);
	print_list(head, "Sorted list :");
	return 0;
}
