#pragma once

#include "Node.h"

class FrontMiddleBackQueue
{
private:
    Node<int>* head;
    Node<int>* tail;

	bool isEmpty();

public:
	FrontMiddleBackQueue();

	void pushFront(int value);

	void pushMiddle(int value);

	void pushBack(int value);

	int popFront();

	int popMiddle();

	int popBack();
};

