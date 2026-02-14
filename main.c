#if 0

Name          : V Pavan Kumar Naik
ID            : 25021_097
Description   : APC Project
sample input  : 12 + 12
sample output : 24

#endif

#include "header.h"
int main(int argc, char *argv[])
{
	Dlist *head1 = NULL;			//declare head and tail of num1, num2 and result
	Dlist *tail1 = NULL;
	
	Dlist *head2 = NULL;
	Dlist *tail2 = NULL;

	Dlist *result_head = NULL;
	Dlist *result_tail = NULL;
	
	Sign S;					//it is for sign of numbers

	if(argc != 4)				//check if argv is 4 or not
	{
		printf("Invalid Arguments\n./a.out <number1> <operator> <number2>\n");
		return 0;
	}

	if(validate_num(argv[1]) == FAILURE)	//validate num1
	{
		printf("Operand 1 failed\n");
		return 0;
	}
	if(argv[1][0] == '-')			//assign num1 sign
		S.num1_sign = -1;
	else
		S.num1_sign = 1;

	if(validate_num(argv[3]) == FAILURE)	//validate num2
	{
		printf("Operand 2 failed\n");
		return 0;
	}
	if(argv[3][0] == '-')			//assign num2 sign
		S.num2_sign = -1;
	else
		S.num2_sign = 1;
	
	if(validate_operator(argv[2]) == FAILURE)	//validate operator
	{
		printf("Operator failed\n");
		return 0;
	}

	convert_str_to_dll(&head1, &tail1, argv[1]);	//convert num1 string to DLL 
	convert_str_to_dll(&head2, &tail2, argv[3]);	//convert num2 string to DLL
	
	//purform the operation of 2 numbers
	if(do_operation(&head1, &tail1, &head2, &tail2, argv[2][0], &result_head, &result_tail, &S) == FAILURE)
	{
		printf("ERROR: Do operation failed\n");
		delete_list(&head1, &tail1);
		delete_list(&head2, &tail2);
		return 0;
	}
	
	//for result sign
	if(argv[2][0] == 'x' || argv[2][0] == '/')	//if operator is 'x' or '/'
	{
		S.res_sign = S.num1_sign * S.num2_sign;
	}
	else if(argv[2][0] == '%')			//if operator is '%'
	{
		S.res_sign = S.num1_sign;
	}
	else if(compare_dll(&head1, &head2) == 1)	//if operator is '+' or '-' and num1 >= num2
	{
		S.res_sign = S.num1_sign;
	}
	else						//if operator is '+' or '-' and num1 < num2
	{
		if(argv[2][0] == '-')
			S.res_sign = -(S.num2_sign);
		else
			S.res_sign = (S.num2_sign);
	}

	//for printing inputs and output with sign
	printf("%s ", argv[1]);
	printf("%s ", argv[2]);
	printf("%s\n", argv[3]);

	if(S.res_sign == -1 && (*result_head).data != 0)
		printf("-");
	print_list(result_head);
	printf("\n");
	
	//delete the all 3 DLL
	delete_list(&head1, &tail1);
	delete_list(&head2, &tail2);
	delete_list(&result_head, &result_tail);

	return 0;
}

int validate_num(char *num)
{
	int i=0;
	if(num[0] == '-' || num[0] == '+')	//if num have sign skip it
		i++;
	if(num[i] == '\0')			//if no digits are found return failure
		return FAILURE;

	for(i; num[i]; i++)
	{
		if(num[i] < '0' || num[i] > '9')//if num digit is lessthan 0 or graterthan 9 it is failure 
		{
			return FAILURE;
		}
	}
	return SUCCESS;
}

int validate_operator(char *op)
{
	if(op[1] != '\0')	//if multiple operators are found return failure
	{
		return FAILURE;
	}

	//if only arthamatic operators are valid
	if(op[0] == '+' || op[0] == '-' || op[0] == 'x' || op[0] == '/' || op[0] == '%')
	{
		return SUCCESS;
	}
	return FAILURE;
}

