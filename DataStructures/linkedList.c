#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Create a node to add to a list from a given value val
static Node* create_node(int);

List* create_list()
{
	List *ans = (List*)malloc(sizeof(List));
	ans->size = 0;
	ans->start = NULL;
	ans->end = NULL;
	return ans;
}

void add_first(List *self, int val)
{
	Node *add = create_node(val);
	if (self->size == 0)
	{
		self->start = add;
		self->end = add;
	}
	else
	{
		add->next = self->start;
		self->start = add;
	}
	self->size++;
}

void add_last(List *self, int val)
{
	Node *to_add = create_node(val);
	if (self->size == 0)
	{
		self->start = to_add;
		self->end = to_add;
	}
	else
	{
		self->end->next = to_add;
		self->end = to_add;
	}
	self->size++;
}

void print_list(List *self) // prints until the next NULL
{
	printf("[");
	if (!is_empty(self))
	{
		Node *curr = self->start;
		while (curr != NULL)
		{
			if (curr == self->end)
				printf("%d", curr->data);
			else
				printf("%d, ", curr->data);
			curr = curr->next;
		}
	}
	printf("]");
}

void free_list(List *self)
{
	Node *curr = self->start;
	Node *tmp;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}

int get_first(List *self)
{
	Node *first = self->start;
	if (first != NULL)
		return first->data;
	else
	{
		fprintf(stderr, "Error: The first node is empty");
		exit(1);
	}
}

int get_last(List *self)
{
	Node *last = self->end;
	if (last != NULL)
		return last->data;
	else
	{
		fprintf(stderr, "Error: The last node is empty");
		exit(1);
	}
}

void remove_first(List *self)
{
	if (is_empty(self) == true)
		fprintf(stderr, "Error: the list is empty!");
	Node *tmp = self->start;
	if (tmp != NULL)
	{
		self->start = self->start->next;
		free(tmp);
	}
	self->size--;
}

void remove_last(List *self)
{
	if (is_empty(self) == true)
		fprintf(stderr, "Error: the list is empty!");
	Node* curr = NULL;
	Node *tmp = self->end;
	for (curr = self->start; curr->next != self->end; curr = curr->next); // find the node before end
	self->end = curr;
	self->end->next = NULL;
	free(tmp);
	self->size--;
}

void remove_by_value(List *self, int val)
{
	//1. check if the list is empty
	if (is_empty(self) == true)
		fprintf(stderr, "Error: the list is empty!");

	//2. check if the value is in the list
	if (contains(self, val) == false)
	{
		fprintf(stderr, "Error: The value %d isn't in the list!", val);
		exit(1);
	}

	//3. go through the list and take care of all the cases 
	if (self->start->data == val) // case its the first node
	{
		remove_first(self);
	}

	else if (self->end->data == val) // case its the last node
	{
		remove_last(self);
	}

	else if (self->start->data != val && self->end->data != val) // case its not end or start
	{
		Node *remove = NULL;
		for (Node *remove = self->start->next; remove->data == val; remove = remove->next);
		if (remove middle) //middle
		{
			Node *bef_remove = NULL;
			Node *tmp = remove;
			for (bef_remove = self->start->next; bef_remove->next != remove; bef_remove = bef_remove->next);
			bef_remove->next = remove->next;
			free(tmp);
		}
		else if (remove edges) // edges
		{

		}
		else // program dont know what to do
		{
			fprintf(stderr, "Unknown error");
			exit(1);
		}
	}


	//while (curr != NULL)
	//{
	//	else if (self->start->data != val && self->end->data != val)
	//	{

	//	}
	//	else // case the program dont know what to do
	//	{
	//		fprintf(stderr, "Unknown Error");
	//		exit(1);
	//	}
	//}

	//4. save the node and free it

}

int contains(List *self, int val) // search for a val in the list
{
	Node *curr = self->start;
	while (curr != NULL)
	{
		if (curr->data == val)
			return true;
		curr = curr->next;
	}
	return false;
}

int is_empty(List *self)
{
	if (self->size == 0) // empty
		return true;
	else
		return false;
}

List* reverse(List *self)
{
	Node *prev = NULL;
	Node *curr = self->start;
	Node *next;
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	self->start = prev;
	self->end = NULL;
	return self;
}

List* clone(List *self)
{
	//1. check if self is null
	if (is_empty(self))
		return NULL;

	//2. create new list
	List *new_list = (List*)malloc(sizeof(List));
	new_list->start = create_node(self->start->data);

	//3. nodes for iteartion
	Node *curr_node = self->start;
	Node *prev_new_node = new_list->start;
	Node *next_new_node = prev_new_node->next; // NULL

	while (curr_node->next != NULL)
	{
		// copy data
		next_new_node = create_node(curr_node->next->data);
		prev_new_node->next = next_new_node;

		// go to next
		prev_new_node = prev_new_node->next;
		curr_node = curr_node->next;
	}
	//4. update new list -> end
	new_list->end = next_new_node;

	//5. update new list -> size
	new_list->size = self->size;

	//6. return new list
	return new_list;
}

static Node* create_node(int val)
{
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node->data = val;
	new_node->next = NULL;
	return new_node;
}