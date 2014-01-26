#include <iostream>
#include "list.h"

List::List() {
	first = nullptr;
}

List::~List() {
	Node *pointer = first;
	while(pointer != nullptr) {
		Node *temp = pointer->next;
		delete pointer;
		pointer = temp;
	}
}

bool List::exists(int d) const {
	Node *pointer = first;
	while(pointer != nullptr) {
		if(pointer->value == d)
			return true;
		pointer = pointer->next;
	}
	return false;
}

int List::size() const {
	Node *pointer = first; 
	int count = 0;
	while(pointer != nullptr) {
		++count;
		pointer = pointer->next; 
	}
	return count;
}

bool List::empty() const {
	//bool isempty = first == nullptr;
	return true;
}

void List::insertFirst(int d) {
	first = new Node(d, first);
}

void List::remove(int d, DeleteFlag df) {
	Node *prev = nullptr;
	Node *pointer = first;
	while(pointer!=nullptr) {
		if ((df == DeleteFlag::EQUAL && pointer->value == d) ||
			(df == DeleteFlag::LESS && pointer->value < d) ||
			(df == DeleteFlag::GREATER && pointer->value > d)) {

			if (prev == nullptr) {
				first = pointer->next;
			} else {
				prev->next = pointer->next;
			}
			Node *temp = pointer->next;
			delete pointer;
			pointer = temp;
		}
		else {
			prev = pointer;
			pointer = pointer->next;
		}
	}
}

void List::print() const {
	Node *pointer = first;
	while(pointer != nullptr) {
		std::cout << pointer->value << " ";
		pointer = pointer->next;
	}
}

