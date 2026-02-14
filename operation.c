#include "header.h"

//function for purforming arthamatic operations
int do_operation(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char operator, Dlist **result_head, Dlist **result_tail, Sign *S)
{
	switch(operator)
    	{
        	case '+' : if(S->num1_sign == S->num2_sign)	//in addition if both signs are same then add numbers
			   {
				   if(add_lists(head1, tail1, head2, tail2, result_head, result_tail) == FAILURE)
				   	return FAILURE;
			   }
			   else					//else subtract numbers
			   {
				   if(compare_dll(head1, head2) == 1)	//if num1 >= num2 
				   {
					   if(subtract_lists(head1, tail1, head2, tail2, result_head, result_tail) == FAILURE)
				   		   return FAILURE;
				   }
				   else					//if num1 < num2
				   {
					   if(subtract_lists(head2, tail2, head1, tail1, result_head, result_tail) == FAILURE)
						   return FAILURE;
				   }
			   }
  	                   break;

        	case '-' : if(S->num1_sign == S->num2_sign)	//in subtraction if both signs are same then subtract numbers
			   {
				   if(compare_dll(head1, head2) == 1)	//if num1 >= num2
				   {
					   if(subtract_lists(head1, tail1, head2, tail2, result_head, result_tail) == FAILURE)
				   		   return FAILURE;
				   }
				   else					//if num1 < num2
				   {
					   if(subtract_lists(head2, tail2, head1, tail1, result_head, result_tail) == FAILURE)
						   return FAILURE;
				   }
			   }
			   else					//else add numbers
			   {
				   if(add_lists(head1, tail1, head2, tail2, result_head, result_tail) == FAILURE)
				   	return FAILURE;
			   }

                   	   break;

        	case 'x' : if(multiply_lists(head1, tail1, head2, tail2, result_head, result_tail) == FAILURE)
				   return FAILURE;
                   	   break;

        	case '/' : if(divide_lists(head1, tail1, head2, tail2, result_head, result_tail) == FAILURE)
				   return FAILURE;
                   	   break;
        	
		case '%' : if(modulus_lists(head1, tail1, head2, tail2, result_head, result_tail) == FAILURE)
				   return FAILURE;
                   	   break;
    	}
    	return SUCCESS;
}

//function of addition
int add_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **result_head, Dlist **result_tail)
{
    	int carry = 0, data;
    	Dlist *temp1 = *tail1;
    	Dlist *temp2 = *tail2;

    	while(temp1 != NULL || temp2 != NULL)		//run loop upto any one list is not empty
    	{
		int d1 = temp1 ? temp1->data : 0;	//for num1 data and num2 data
		int d2 = temp2 ? temp2->data : 0;

		data = d1 + d2 + carry;			//add data of num1, num2 and carry
		carry = data / 10;			//initialize carry
		data = data % 10;			//update data
		
		//update result DLL with data
		if(insert_at_first(result_head, result_tail, data) == FAILURE)
			return FAILURE;
		
		//if temp is not NULL then update it
		if(temp1)
			temp1 = temp1->prev;
		if(temp2)
			temp2 = temp2->prev;
	}
	
	//if carry is non 0 value then assign it
    	if(carry != 0)
    	{
		if(insert_at_first(result_head, result_tail, carry) == FAILURE)
			return FAILURE;
    	}
	
	remove_start_zero(result_head, result_tail);	//finally remove starting 0's of result
    	
	return SUCCESS;
}

//function for subtraction
int subtract_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **result_head, Dlist **result_tail)
{
	int borrow = 0, data;
	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;

	while(temp1 != NULL || temp2 != NULL)		//loop run until temp1 true
	{
		int d1 = temp1 ? temp1->data : 0;	//update d1 and d2
		int d2 = temp2 ? temp2->data : 0;

		data = d1 - d2 - borrow;		//update data
		
		if(data < 0)				//if data is negative num then add 10 to it
		{
			data += 10;
			borrow = 1;
		}
		else
		{
			borrow = 0;
		}

		//update result DLL with data
		if(insert_at_first(result_head, result_tail, data) == FAILURE)
			return FAILURE;
		
		//update temp if it is not NULL
		if(temp1)
			temp1 = temp1->prev;
		if(temp2)
			temp2 = temp2->prev;

	}
	
	//finally remove starting 0's of result DLL
	remove_start_zero(result_head, result_tail);
	
	return SUCCESS;
}

//function of multiplication
int multiply_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **result_head, Dlist **result_tail)
{
	//if any one num is 0 then add 0 and return
	if( ((*head1 == *tail1) && ((*head1)->data == 0)) || ((*head2 == *tail2) && (*head2)->data == 0 )) 
	{
		insert_at_first(result_head, result_tail, 0);
		return SUCCESS;
	}

	int data, count = 0;
	insert_at_first(result_head, result_tail, 0);		//initialize res with 0
	Dlist *temp2 = *tail2;
	
	while(temp2 != NULL)					//run loop until num2 not null
	{
		//take one temparary linked list for storing data of 1 loop
		Dlist *temp_head = NULL;
		Dlist *temp_tail = NULL;
		Dlist *temp1 = *tail1;
		
		int carry = 0;
		while(temp1 != NULL)				//run loop until num1 not null
		{
			data = (temp1->data * temp2->data) + carry;//initialize data
			
			carry = data / 10;			//update data and carry
			data = data % 10;

			if(insert_at_first(&temp_head, &temp_tail, data) == FAILURE)
				return FAILURE;
			temp1 = temp1->prev;
		}
    		if(carry != 0)					//if carry not zero then add it in temp list
    		{
			if(insert_at_first(&temp_head, &temp_tail, carry) == FAILURE)
				return FAILURE;
    		}

		//add last 0 count times for accurate multiplication
		for(int i=0; i<count; i++)
		{
			insert_at_last(&temp_head, &temp_tail, 0);
		}
		
		//add the prev and current temp data
		Dlist *new_res_head = NULL, *new_res_tail = NULL;
		if(add_lists(result_head, result_tail, &temp_head, &temp_tail, &new_res_head, &new_res_tail) == FAILURE)
			return FAILURE;
		
		//delete the result linked list and update it 
		delete_list(result_head, result_tail);
		*result_head = new_res_head;
		*result_tail = new_res_tail;

		delete_list(&temp_head, &temp_tail);
		count++;					//increment the count by 1
		temp2 = temp2->prev;
	}

	remove_start_zero(result_head, result_tail);
	return SUCCESS;
}

//function for division
int divide_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **result_head, Dlist **result_tail)
{
	//if num2 is 0 we can't do operation
	if( (*head2 == *tail2) && ((*head2)->data == 0) )
		return FAILURE;

	//if num1 is 0 or num1 is lessthan num2 add 0 in result 
	if( ((*head1 == *tail1) && ((*head1)->data == 0)) || (compare_dll(head1, head2) == -1) )
	{
		insert_at_first(result_head, result_tail, 0);
		return SUCCESS;
	}
	
	//inc linked list for add 1 in the result
	Dlist *inc_h = NULL;
	Dlist *inc_t = NULL;
	insert_at_first(&inc_h, &inc_t, 1);
	insert_at_first(result_head, result_tail, 0);

	while(compare_dll(head1, head2) == 1)	//run loop until num1 is >= num2
	{
		//teke temp result for storing output of subtraction
		Dlist *res_h = NULL;
		Dlist *res_t = NULL;

		//subtract the num1 with num2
		if(subtract_lists(head1, tail1, head2, tail2, &res_h, &res_t) == FAILURE)
			return FAILURE;
		
		//update the head1 list with result list
		delete_list(head1, tail1);
		*head1 = res_h;
		*tail1 = res_t;
		
		//temp linked list for result count storing
		Dlist *res_c_h = NULL;	
		Dlist *res_c_t = NULL;	
		
		//update count by 1
		if(add_lists(result_head, result_tail, &inc_h, &inc_t, &res_c_h, &res_c_t) == FAILURE)
			return FAILURE;

		//update the result head with res count list
		delete_list(result_head, result_tail);
		*result_head = res_c_h;
		*result_tail = res_c_t;
	}
	
	delete_list(&inc_h, &inc_t);
	
	remove_start_zero(result_head, result_tail);
	return SUCCESS;
}

//function for find modulus
int modulus_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **result_head, Dlist **result_tail)
{
	if((*head1 == *tail1) && (*head1)->data == 0)		//if num1 data is 0 add result with 0 and return 
	{
		insert_at_first(result_head, result_tail, 0);
		return SUCCESS;
	}

	//if num2 is 0 then we can't do operation
	if((*head2 == *tail2) && (*head2)->data == 0)
		return FAILURE;
	
	//copy num1 data into result list
	Dlist *temp = *head1;
	while(temp)
	{
		insert_at_last(result_head, result_tail, temp->data);
		temp = temp->next;
	}

	//run loop until num1 >= num2
	while(compare_dll(result_head, head2) == 1)
	{
		//temp result for storing sub of num
		Dlist *res_h = NULL;
		Dlist *res_t = NULL;

		//subtract result list with num2 list
		if(subtract_lists(result_head, result_tail, head2, tail2, &res_h, &res_t) == FAILURE)
			return FAILURE;
		
		//update the result DLL with temp result list
		delete_list(result_head, result_tail);
		*result_head = res_h;
		*result_tail = res_t;
	}
	
	remove_start_zero(result_head, result_tail);
	return SUCCESS;
}
