#include "Ejercicio04.h"

FrontMiddleBackQueue::FrontMiddleBackQueue()
{
	head = tail = nullptr;
}

bool FrontMiddleBackQueue::isEmpty() {
	return head == nullptr;
}

void FrontMiddleBackQueue::pushFront(int value)
{
	if(isEmpty()) {
		head = tail = new Node<int>{value};
		return;
	}

	Node<int>* next = new Node<int>{value, head};
	head = next;
}

void FrontMiddleBackQueue::pushMiddle(int value)
{
	if(isEmpty()) {
		head = tail = new Node<int>{value};
		return;
	}

	Node<int> prehead{-1, head};

	Node<int>* fast = head;
	Node<int>* prev = &prehead;

	while (fast && fast->next) {
		prev = prev->next;
		fast = fast->next->next;
	}

	prev->next = new Node<int>{value, prev->next};
	head = prehead.next;
}

void FrontMiddleBackQueue::pushBack(int value)
{
	if(isEmpty()) {
		head = tail = new Node<int>{value};
		return;
	}

	tail->next = new Node<int>{value};
	tail = tail->next;
}

int FrontMiddleBackQueue::popFront()
{
	if (isEmpty()) return -1;

	int val = head->value;
	Node<int>* n = head;

	head = head->next;
	delete n;

	return val;
}

int FrontMiddleBackQueue::popMiddle()
{
	if (isEmpty()) return -1;

	if (!head->next) return popFront();

	Node<int>* prehead = new Node<int>{-1, head};

	Node<int>** slow = &prehead;
	Node<int>* fast = head;

	while (fast && fast->next) {
		slow = &((*slow)->next);
		fast = fast->next->next;
	}

	int val = -1;
	Node<int>* n;

	if (!fast) {
		val = (*slow)->value;
		n = *slow;
		*slow = (*slow)->next;
	}
	else {
		n = (*slow)->next;
		val = n->value;
		(*slow)->next = n->next;
	}

	head = prehead->next;

	delete n, prehead;

	return val;
}

int FrontMiddleBackQueue::popBack()
{
	if (isEmpty()) return -1;

	Node<int>* it = head;
	
	if (!it->next) {
		return popFront();
	}

	while (it->next != tail) {
		it = it->next;
	}

	Node<int>* n = tail;
	int val = tail->value;
	
	tail = it;
	tail->next = nullptr;

	delete n;

	return val;
}
