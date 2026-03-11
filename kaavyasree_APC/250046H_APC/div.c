#include "apc.h"

void division(node *head_L1, node *head_OPR2, node *tail_OPR2,node **headR, node **tailR)
{
    // Linked list to store the current dividend part
    node *head_OPR1 = NULL;
    node *tail_OPR1 = NULL;

    // Temporary pointer to traverse dividend list
    node *L1_temp = head_L1;

    // Linked list to store subtraction result
    node *head_SR = NULL;
    node *tail_SR = NULL;

    int sub_count;   // Stores number of successful subtractions (quotient digit)

    // Insert first digit of dividend into OPR1 list
    insert_last(&head_OPR1, &tail_OPR1, L1_temp->data);

    // Build initial dividend part until it becomes >= divisor
    while (compare_list(head_OPR1, head_OPR2) == OPERAND2)
    {
        L1_temp = L1_temp->next;

        // If dividend digits are exhausted, quotient is 0
        if (!L1_temp)
        {
            insert_last(headR, tailR, 0);
            return;
        }

        // Append next digit to current dividend
        insert_last(&head_OPR1, &tail_OPR1, L1_temp->data);
    }

    // Main division loop (similar to long division)
    while (L1_temp != NULL)
    {
        sub_count = 0;   // Reset count for each quotient digit

        // Remove leading zeros from current dividend
        remove_pre_zeros(&head_OPR1);

        // Repeatedly subtract divisor from current dividend
        while (compare_list(head_OPR1, head_OPR2) != OPERAND2)
        {
            // Perform subtraction
            subtraction(tail_OPR1, tail_OPR2, &head_SR, &tail_SR);

            sub_count++;   // Increment quotient digit

            // Delete old dividend list
            delete_list(&head_OPR1, &tail_OPR1);

            // Update dividend with subtraction result
            head_OPR1 = head_SR;
            tail_OPR1 = tail_SR;

            // Reset subtraction result list
            head_SR = tail_SR = NULL;
        }

        // Store the quotient digit
        insert_last(headR, tailR, sub_count);

        // Move to next digit of dividend
        L1_temp = L1_temp->next;

        // Stop if no more digits are left
        if (L1_temp == NULL)
        {
            break;
        }

        // Bring down next digit (long division step)
        insert_last(&head_OPR1, &tail_OPR1, L1_temp->data);
    }
}
