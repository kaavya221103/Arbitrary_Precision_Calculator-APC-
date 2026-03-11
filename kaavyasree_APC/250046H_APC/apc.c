#include "apc.h"

// Function to validate command line arguments
int cla_validation(int argc, char *argv[])		// validation of CLA
{
    int i;

    // Check for correct number of arguments
	if (argc == 4)
	{
        /* -------- Validate first operand -------- */
        i = 0;

        // Skip optional sign
		if (argv[1][i] == '+' || argv[1][i] == '-')
    		i++;

        // Ensure all remaining characters are digits
		while (argv[1][i])
        {
            if (argv[1][i] >= '0' && argv[1][i] <= '9')
                i++;
            else
                return FAILURE;   // Invalid character found
        }

        /* -------- Validate second operand -------- */
        i = 0;

        // Skip optional sign
		if (argv[3][i] == '+' || argv[3][i] == '-')
    		i++;

        // Ensure all remaining characters are digits
        while (argv[3][i])
        {
            if (argv[3][i] >= '0' && argv[3][i] <= '9')
                i++;
            else
                return FAILURE;   // Invalid character found
        }

        // Both operands are valid
        return SUCCESS;
	}

    // Incorrect number of arguments
	return FAILURE;
}

// Function to create linked list from operand string
void create_list(char *opr, node **head, node **tail)
{
	int i = 0, num;

    // Ignore sign if present
	if (opr[i] == '+' || opr[i] == '-')
		i++;

    // Convert each digit character into a node
	while (opr[i])
	{
		num = opr[i] - '0';          // Char to integer conversion
		insert_last(head, tail, num);
        i++;
	}
}

// Insert a node at the beginning of the list
int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));
    if (!new)
        return FAILURE;   // Memory allocation failure

    new->data = data;
    new->prev = NULL;
    new->next = *head;

    // Update links if list is not empty
    if (*head)
    {
        (*head)->prev = new;
    }
    else
    {
        *tail = new;   // First node in the list
    }

    *head = new;
    return SUCCESS;
}

// Insert a node at the end of the list
int insert_last(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));
    if (!new)
        return FAILURE;   // Memory allocation failure

    new->data = data;
    new->next = NULL;
    new->prev = *tail;

    // Attach node at the end
    if (*tail)
    {
        (*tail)->next = new;
    }
    else
    {
        *head = new;   // First node in the list
    }

    *tail = new;
    return SUCCESS;
}

// Print the linked list
void print_list(node *head)
{
    // Check if list is empty
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    while (head)
	    {
		    printf("%d", head->data);   // Print each digit
		    head = head->next;
	    }
    	printf("\n");
    }
}

// Calculate length of linked list
int list_len(node *head)
{
    int count = 0;

    // Traverse and count nodes
    while (head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}

// Compare two linked lists representing numbers
int compare_list(node *head1, node *head2)
{
    int len1 = list_len(head1);
    int len2 = list_len(head2);

    // Compare based on number of digits
    if (len1 > len2)
        return OPERAND1;

    if (len1 < len2)
        return OPERAND2;

    // If lengths are equal, compare digit by digit
    node *temp1 = head1;
    node *temp2 = head2;

    while (temp1 && temp2)
    {
        if (temp1->data > temp2->data)
            return OPERAND1;
        else if (temp1->data < temp2->data)
            return OPERAND2;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    // Both numbers are equal
    return SAME;
}

// Remove leading zeros from the number
void remove_pre_zeros(node **head)
{
    // Remove zeros only from the beginning
	while ((*head)->data == 0)
	{
        // Stop if only one digit remains
		if ((*head)->next == NULL)
			return;

        // Delete leading zero node
		*head = (*head)->next;
		free((*head)->prev);
		(*head)->prev = NULL;
	}
}

// Delete entire linked list
int delete_list(node **head, node **tail)
{
    // Check if list is already empty
    if (*head == NULL)
        return FAILURE;

    node *temp = *head;

    // Free all nodes
    while (temp)
    {
        node *next = temp->next;
        free(temp);
        temp = next;
    }

    // Reset head and tail
    *head = NULL;
    *tail = NULL;

    return SUCCESS;
}