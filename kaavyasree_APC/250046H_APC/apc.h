#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS     1
#define FAILURE     0


#define SAME        0   // Both operands are equal
#define OPERAND1    1   // Operand 1 is greater
#define OPERAND2    2   // Operand 2 is greater


typedef struct node
{
    struct node *prev;   // Pointer to previous node
    int data;            // Digit stored in the node
    struct node *next;   // Pointer to next node
} node;

//Adds two numbers represented by linked lists
void addition(node *tail1, node *tail2, node **headR, node **tailR);


//Subtracts second number from first number

void subtraction(node *tail1, node *tail2, node **headR, node **tailR);


//Multiplies two numbers represented by linked lists
void multiplication(node *tail1, node *tail2, node **headR, node **tailR);

//Divides first number by second number
void division(node *head_L1, node *head_OPR2, node *tail_OPR2,node **headR, node **tailR);

//Command line argument validation 
int cla_validation(int argc, char *argv[]);

//Creates a linked list from the operand string
 
void create_list(char *opr, node **head, node **tail);

//Linked list utility functions

//Inserts a node at the beginning of the list
int insert_first(node **head, node **tail, int data);


//Inserts a node at the end of the list
int insert_last(node **head, node **tail, int data);

// Deletes the entire linked list
int delete_list(node **head, node **tail);

//Prints the linked list
void print_list(node *head);

//Compares two linked lists representing numbers
int compare_list(node *head1, node *head2);

//Returns the length of the linked list
int list_len(node *head);

//Removes leading zeros from the list
void remove_pre_zeros(node **head);

#endif
