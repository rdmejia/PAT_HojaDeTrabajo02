#include "Ejercicio02.h"

Node<int>* Ejercicio02::addTwoNumbers(Node<int>* l1, Node<int>* l2)
{
    Node<int>* result = nullptr;
    int carry = 0;
    int sum = 0;
    int digit = 0;

    Node<int>** it = &result;

    while (l1 && l2) {
        sum = carry + l1->value + l2->value;
        digit = sum % 10;
        carry = sum / 10;
        
        *it = new Node<int>{digit};

        l1 = l1->next;
        l2 = l2->next;
        it = &((*it)->next);
    }

    while (l1) {
        sum = carry + l1->value;
        digit = sum % 10;
        carry = sum / 10;

        *it = new Node<int>{digit};

        l1 = l1->next;
        it = &((*it)->next);
    }

    while (l2) {
        sum = carry + l2->value;
        digit = sum % 10;
        carry = sum / 10;

        *it = new Node<int>{digit};

        l2 = l2->next;
        it = &((*it)->next);
    }

    if (carry > 0) {
        *it = new Node<int>{carry};
    }

    return result;
}
