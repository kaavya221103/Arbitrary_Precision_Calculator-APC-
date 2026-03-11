#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR1, node **tailR1)
{
    // temp1, temp2 are used to traverse both numbers from LSB
    node *temp1 = tail1, *temp2 = tail2;


    // headAR, tailAR → addition result list
    node *headR2 = NULL, *tailR2 = NULL;
    node *headAR = NULL, *tailAR = NULL;

    int count = 0;     // Keeps track of digit position (for shifting)
    int carry = 0;
    int num1, num2, mul, res;

    // Traverse second operand digit by digit
    while (temp2)
    {
        carry = 0;

        // Add zeros in front for positional shift 
        for (int i = 0; i < count; i++)
            insert_first(&headR2, &tailR2, 0);

        count++;   // Increase shift count for next iteration

        // Multiply current digit of operand2 with operand1
        while (temp1)
        {
            num1 = temp1->data;
            num2 = temp2->data;

            // Multiply digits and add carry
            mul = num1 * num2 + carry;
            res = mul % 10;
            carry = mul / 10;

            // First iteration stores directly in final result
            if (count == 0)
                insert_first(headR1, tailR1, res);
            else
                insert_first(&headR2, &tailR2, res);

            // Move to next digit of operand1
            temp1 = temp1->prev;
        }

        // If carry remains after multiplication
        if (carry)
        {
            if (count == 0)
                insert_first(headR1, tailR1, carry);
            else
                insert_first(&headR2, &tailR2, carry);
        }

        // Add partial product with accumulated result
        addition(*tailR1, tailR2, &headAR, &tailAR);

        // Clear old result lists
        delete_list(headR1, tailR1);
        delete_list(&headR2, &tailR2);

        // Update final result with addition result
        *headR1 = headAR;
        *tailR1 = tailAR;
        headAR = tailAR = NULL;

        // Move to next digit of second operand
        temp2 = temp2->prev;

        // Reset first operand pointer
        temp1 = tail1;
    }

    // Remove leading zeros from final result
    remove_pre_zeros(headR1);
}