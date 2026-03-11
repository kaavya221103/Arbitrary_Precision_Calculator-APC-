#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    // temp1 and temp2 are used to traverse both numbers from LSB
    node *temp1 = tail1;
    node *temp2 = tail2;

    int borrow = 0;   // Stores borrow during subtraction

    // Initialize result list as empty
    *headR = *tailR = NULL;

    // Continue until both lists are completely traversed
    while (temp1 || temp2)
    {
        int num1 = 0, num2 = 0;

        // Get digit from first number
        if (temp1)
        {
            num1 = temp1->data;
            temp1 = temp1->prev;
        }

        // Get digit from second number
        if (temp2)
        {
            num2 = temp2->data;
            temp2 = temp2->prev;
        }

        // Apply previous borrow
        if (borrow == 1)
        {
            num1 = num1 - 1;
            borrow = 0;
        }

        // If current digit is smaller, borrow from next digit
        if (num1 < num2)
        {
            num1 += 10;
            borrow = 1;
        }

        // Perform digit-wise subtraction
        int sub = num1 - num2;

        // Insert result digit at the beginning
        insert_first(headR, tailR, sub);
    }

    // Remove leading zeros from the result
    remove_pre_zeros(headR);
}