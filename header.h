#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node		//structure for node
{
	int data;
	struct node *prev;
	struct node *next;
}Dlist;

typedef struct num_sign		//structure for nums sign
{
	int num1_sign;
	int num2_sign;
	int res_sign;
}Sign;

int validate_operator(char *num);
int validate_num(char *num);
int convert_str_to_dll(Dlist **head, Dlist **tail, char *num);
int insert_at_first(Dlist **head, Dlist **tail, int data);
int insert_at_last(Dlist **head, Dlist **tail, int data);
void remove_start_zero(Dlist **head, Dlist **tail);
int compare_dll(Dlist **head1, Dlist **head2);

int do_operation(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char operator, Dlist **result_head, Dlist **result_tail, Sign *S);
int add_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **result_head, Dlist **result_tail);
int subtract_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **result_head, Dlist **result_tail);
int multiply_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **result_head, Dlist **result_tail);
int divide_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **result_head, Dlist **result_tail);
int modulus_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **result_head, Dlist **result_tail);

void print_list(Dlist *head);
void delete_list(Dlist **head, Dlist **tail);

#endif
