#pragma once

#include "Node.h"

class Ejercicio02
{
public:
	Node<int>* addTwoNumbers(Node<int>* l1, Node<int>* l2){
	Node<int> dummy(0);
    	Node<int>* current = &dummy;
    	int carry = 0;

    while (l1 || l2 || carry) {
        int sum = carry;

        if (l1) {
            sum += l1->value;
            l1 = l1->next;
        }

        if (l2) {
            sum += l2->value;
            l2 = l2->next;
        }

        carry = sum / 10;
        current->next = new Node<int>(sum % 10);
        current = current->next;
    }

    return dummy.next;
}
};

