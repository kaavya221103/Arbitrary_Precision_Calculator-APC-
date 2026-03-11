/* Documentation
    Name            : 		N.Kaavya Sree
    Date            : 		13-feb-2026
    Description     : 		The Accurate Precision Calculator (APC) is a command-line based arithmetic application developed in C that performs mathematical operations on very large integers with high precision. Unlike traditional calculators that rely on built-in data types and are limited by size constraints, this project uses doubly linked lists to represent numbers digit by digit, enabling calculations on numbers of arbitrary length without loss of accuracy.
					Each digit of an operand is stored in a separate node of a linked list, allowing the calculator to simulate manual arithmetic operations such as addition, subtraction, multiplication, and division. The calculator supports core arithmetic operations and ensures accurate results even when dealing with numbers that exceed the range of standard integer types.
					The project is modularly designed with well-defined functions for list creation, arithmetic processing, comparison, and memory management. Command-line argument validation ensures correct input format, while utility functions handle tasks such as removing leading zeros, comparing operands, and printing results.
					The Accurate Precision Calculator demonstrates the practical application of data structures, dynamic memory allocation, and algorithmic problem-solving, making it suitable for academic purposes and for understanding the implementation of arbitrary-precision arithmetic systems.make this parain short
*/#include "apc.h"

#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define RESET "\033[0m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;
	int p_flag1=0,p_flag2=0,n_flag1=0,n_flag2=0,result_sign=0;
    // Validation
	if(!cla_validation(argc,argv))
	{
		printf("Error : Invalid arguments\n");
		return FAILURE;
	}
	printf(CYAN "Operand 1 : "WHITE "%s\n" RESET, argv[1]);
	printf(CYAN "Operand 2 : "WHITE "%s\n" RESET, argv[3]);
	printf(CYAN "Operator  : "WHITE "%c\n" RESET, argv[2][0]);
	printf(BLUE "============================================================================\n" RESET);


    // Create 2 lists of operands
	create_list(argv[1],&head1,&tail1);
	create_list(argv[3],&head2,&tail2);

    //Remove pre zeros
	remove_pre_zeros(&head1);
	remove_pre_zeros(&head2);

	if(argv[1][0]=='+')
		p_flag1=1;
	else if(argv[1][0]=='-')
		n_flag1=1;
	if(argv[3][0]=='+')
		p_flag2=1;
	else if(argv[3][0]=='-')
		n_flag2=1;
    char oper = argv[2][0];
	//fetch operator
	if(oper == '+')
	{
		// -a + -b
		if(n_flag1 == 1 && n_flag2==1)
		{
			oper='+';
		}
		// +a + -b
		else if(n_flag1==0 && n_flag2 == 1)
		{
			oper='-';
		}
		// -a + +b
		else if(n_flag1 == 1 && n_flag2==0)
		{
			oper='-';
		}
	}
	else if(oper == '-')
	{
		// -a - -b
		if(n_flag1 == 1 && n_flag2==1)
		{
			oper='-';
		}
		// +a - -b
		else if(n_flag1==0 && n_flag2 == 1)
		{
			oper='+';
		}
		// -a - +b
		else if(n_flag1 == 1 && n_flag2==0)
		{
			oper='+';
		}
	}
	if(oper == '+')
		printf(MAGENTA"Operation : ADDITION(+)\n"RESET);
	else if(oper == '-')
	{
		printf(MAGENTA"Operation : SUBTRACTION(-)\n"RESET);
	}
	else if(oper == 'x' || oper == 'X')
	{
		printf(MAGENTA"Operation : MULTIPLICATION(X)\n"RESET);
	}
	else if(oper == '/')
	{
		printf(MAGENTA"Operation : DIVISION(/)\n"RESET);
	}
	
	printf(BLUE "============================================================================\n" RESET);
	printf(MAGENTA "                ~~~~~~~~~~~~~APC CALCULATOR~~~~~~~~~~~~~~~~               \n"RESET);
	printf(BLUE "============================================================================\n" RESET);

	switch(oper)
	{
		case '+':
			addition(tail1, tail2, &headR, &tailR);
			if(n_flag1 == 1 && n_flag2==0)
				result_sign =1;
			else
				result_sign = (n_flag1 && n_flag2);
			break;

		case '-':
		{
			int ret = compare_list(head1, head2);

			if (ret == OPERAND1)
			{
				subtraction(tail1, tail2, &headR, &tailR);
				result_sign = n_flag1;
			}
			else if (ret == OPERAND2)
			{
				subtraction(tail2, tail1, &headR, &tailR);
				result_sign = !n_flag1;
			}
			else
			{
				insert_first(&headR, &tailR, 0);
				result_sign = 0;
			}
			break;
		}

		case 'x':
		case 'X':
			multiplication(tail1, tail2, &headR, &tailR);
			result_sign = (n_flag1 != n_flag2);
			break;

		case '/':
			if (head2->data == 0)
			{
				printf("Runtime Error : Divisible by Zero\n"); 
				return FAILURE;
			}
			division(head1, head2, tail2, &headR, &tailR);
			result_sign = (n_flag1 != n_flag2);
			break;

		default:
			printf("Invalid operator\n");
			return FAILURE;
	}
	remove_pre_zeros(&headR); // it removes pre zeors
	printf(MAGENTA"Result : " RESET);

	/* avoid printing -0 */
	if (result_sign && !(headR->data == 0))
    	printf("-");

	print_list(headR);
	printf("\n");
	return SUCCESS;
}

