#pragma once
template<typename T>
struct Node
{
	T value;
	Node* next;
	Node(T val) : value(val), next(nullptr) {}
};
