#pragma once

#include "Node.h"

class Ejercicio01
{
public:
	Node<char>* rotateRight(Node<char>* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 0) {
            return head;
        }

        int len = 1;
        Node<char>* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
            len++;
        }

        k %= len;
        if (k == 0) {
            return head;
        }

        Node<char>* new_tail = head;
        for (int i = 0; i < len - k - 1; i++) {
            new_tail = new_tail->next;
        }

        Node<char>* new_head = new_tail->next;
        new_tail->next = nullptr;
        tail->next = head;

        return new_head;
    }
};

