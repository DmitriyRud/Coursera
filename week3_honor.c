/*
   C for Everyone: Structured programming
   Week 3 Honors Assignment : Removing duplicate values from doubly linked list
   Modify the singly linked list to be a doubly linked list. Now write a routine that removes all
   duplicate data in the doubly linked list. The data will be integers generated at random from [0,49].
   Initially have a list of 200 elements.

   Sort the list by its data field. Remove adjacent elements of the sorted list with the same value.
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
	struct list	*prev;
}				list;

list* create_list(int d)
/* Function, which create the new list */
{
	list *head = malloc(sizeof(list));
	head->data = d;
	head->next = NULL;
	head->prev = NULL;
	return head;
}

list* add_to_front(int d, list* h)
/* Function, which adds new element to front of the list */
{
	list* head = create_list(d);
	head->next = h;
	h->prev = head;
	return head;
}

list* fill_random_list(int size)
/* Filling our list with random data */
{
	srand(time(NULL));
	list* head = create_list(rand() % 49);
	for (int i = 0; i < size - 1; i++)
	{
		head = add_to_front(rand() % 49, head);
	}
	return head;
}

void clear_list(list *lst)
/* Function for deleting duplicate nodes */
{
    list *t, *p, *i, *prev;
    for(p = lst; p != NULL; p = p->next){
        prev = p;
        for(i = p->next; i != NULL; ){
            if(i->data == p->data){
                t = prev->next = i->next;
                free(i);
                i = t;
                continue;
            }
            prev = i;
            i    = i->next;
        }
    }
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
			current->prev = node;
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
		printf("%2d", h->data);
		++row;
		if (row == 25)								/* Print these values in rows of 25 */
		{
			printf("\n");
			row = 0;
		}
		else if (h->next != NULL)
			printf(", ");
		h = h->next;
	}
	printf("\n");
}

int	main(void)
{
	list* head = NULL;
	
	head = fill_random_list(200);
	print_list(head, "Initial list :");
	head = sort_list(head);
	print_list(head, "Sorted list :");
	clear_list(head);
	print_list(head, "Duplicates deleted :");

	return 0;
}
