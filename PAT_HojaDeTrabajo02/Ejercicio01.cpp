#include "Ejercicio01.h"

Node<char>* Ejercicio01::rotateRight(Node<char>* head, int k)
{
    if (!head || !head->next || k == 0)
        return head;

    Node<char>* it = head;
    Node<char>* prev = nullptr;

    int size = 0;
    while (it) {
        ++size;
        prev = it;
        it = it->next;
    }

    k = k % size;
    prev->next = head;

    prev = nullptr;
    while (k >= 0) {
        prev = head;
        head = head->next;
        --k;
    }

    prev->next = nullptr;

    return head;
}
