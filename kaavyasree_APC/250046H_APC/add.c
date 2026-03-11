#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    //temporary pointers to traverse both lists from the tail
    node *temp1=tail1;
    node *temp2=tail2;
    //Intialize result list as empty
    *headR=*tailR=NULL;
    int sum,carry=0;   //loops continues until: both lists are fully traversed and n carry is left
    while(temp1 || temp2  || carry)
    {
        sum=carry;    //start with carry from previous addition
        if(temp1)  //if first list still has digits , add its data
        {
            sum += temp1->data;
            temp1=temp1->prev;  //move to previous digit
        }
        //if second list still has digit of sum at the begining of result list
        if(temp2)
        {
            sum += temp2->data;
            temp2 = temp2->prev;
        }
        insert_first(headR,tailR,sum % 10);
        carry = sum / 10;          //update carry for next iteration
    }
}
