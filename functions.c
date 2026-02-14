#include "header.h"

//function for convert structure to DLL
int convert_str_to_dll(Dlist **head, Dlist **tail, char *num)
{
	int i=0;
	if(num[0] == '-' || num[0] == '+')
	{
		i++;
	}

    	for(i; num[i]; i++)	//insert data in DLL
    	{
        	if(insert_at_last(head, tail, num[i] - '0') == FAILURE)
			return FAILURE;
    	}
	remove_start_zero(head, tail);	//remove if unwanted 0's are present at before num

    	return SUCCESS;
}

//function for insert at first
int insert_at_first(Dlist **head, Dlist **tail, int data)
{
	Dlist *new = malloc(sizeof(Dlist));
	if(!new)
	{
		return FAILURE;
	}

	new->data = data;
	new->prev = NULL;

	if(*head == NULL)
	{
		new->next = NULL;
		*head = new;
		*tail = new;
	}
	else
	{
		new->next = *head;
		(*head)->prev = new;
		*head = new;
	}
	return SUCCESS;
}

//function for insert at last
int insert_at_last(Dlist **head, Dlist **tail, int data)
{
	Dlist *new = malloc(sizeof(Dlist));
	if(!new)
	{
		return FAILURE;
	}

	new->data = data;
	new->next = NULL;

	if(*head == NULL)
	{
		new->prev = NULL;
		*head = new;
		*tail = new;
	}
	else
	{
		new->prev = *tail;
		(*tail)->next = new;
		*tail = new;
	}
	return SUCCESS;
}

//function for remove starting zeros of DLL
void remove_start_zero(Dlist **head, Dlist **tail)
{
	//run a loop upto first data is not zero and if only 1 node is remaining
	while(*head != *tail && (*head)->data == 0)
	{
		Dlist *temp = *head;	//update the head and free the temp
		*head = temp->next;
		(*head)->prev = NULL;
		free(temp);
	}
}

//function of compare 2 DLL which is have grater number
int compare_dll(Dlist **head1, Dlist **head2)
{
	int c1 = 0, c2 = 0;
	Dlist *temp1 = *head1;
	Dlist *temp2 = *head2;

	while(temp1 != NULL)	//count num1 nodes
	{
		c1++;
		temp1 = temp1->next;
	}
	while(temp2 != NULL)	//count num2 nodes
	{
		c2++;
		temp2 = temp2->next;
	}

	if(c1 > c2)		//if num1 is bigger return 1
	{
		return 1;
	}
	else if(c1 < c2)	//if num2 is bigger return -1
	{
		return -1;
	}
	else			//if both nodes are same then compare data by data
	{
		temp1 = *head1;
		temp2 = *head2;
		while(temp1 != NULL)
		{
			if( (temp1->data) > (temp2->data) )	//if num1 data is bigger return 1
				return 1;
			else if( (temp1->data) < (temp2->data) )//if num2 data is bigger return -1
				return -1;
			else					//else update links
			{
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
		return 1;	//if both data are same return 1
	}
}

//function of printing list
void print_list(Dlist *head)
{
    	if(head == NULL)
    	{
        	printf("List is empty\n");
    	}
    	else
    	{
        	while(head != NULL)
        	{
            		printf("%d", head->data);
            		head = head->next;
        	}
    	}
}

//function of free the entire list
void delete_list(Dlist **head, Dlist **tail)
{
    	while(*head != NULL)
	{
		Dlist *temp = *head;
		if(*head == *tail)
    		{
        		*head = NULL;
			*tail = NULL;
			free(temp);
    		}
		else
		{
			*head = temp->next;
			free(temp);
		}
	}
}
