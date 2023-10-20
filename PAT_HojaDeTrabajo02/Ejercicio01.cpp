#include "Ejercicio01.h"

Node<char>* Ejercicio01::rotateRight(Node<char>* head, int k)
{
    if (!head || !head->next || k == 0)
        return head;

    Node<char>* it = head;

    int size = 0;
    while (it->next) {
        ++size;
        it = it->next;
    }
    ++size;

    k = k % size;
    it->next = head;
    
    while (size != k) {
        it = head;
        head = head->next;
        --size;
    }

    it->next = nullptr;

    return head;
}
