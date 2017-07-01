#pragma once

/*
Template based fifo (First In First Out) container class implemented as double linked list
*/

#include <iostream>

template <typename T>
struct qnode
{
	T elem;
	qnode * prev;
	qnode * next;
};

template <typename T>
class fifo
{
	size_t lenght;
	qnode<T> * head;
	qnode<T> * tail;
	
	void inline deletenodes() {
		qnode<T> * nextnode = head;
		qnode<T> * old;
		while (nextnode != nullptr)
		{
			old = nextnode;
			nextnode = nextnode->prev;
			//std::cout << "Deleting " << old->elem << "\n";
			delete old;
		}
	}

public:
	fifo() : lenght(0), head(nullptr), tail(nullptr) {}
	~fifo() {
		deletenodes();
	}
	fifo(const fifo<T>& queue) : lenght(0) {
		qnode<T> * readnode = queue.head;
		while (readnode != nullptr)
		{
			this->push(readnode->elem);
			readnode = readnode->prev;
		}
	}
	fifo(fifo<T>&& queue) : lenght(queue.lenght) {
		head = queue.head;
		tail = queue.tail;
		queue.head = nullptr;
		queue.tail = nullptr;
	}
	fifo<T>& operator=(const fifo<T>& queue) {
		deletenodes();
		lenght = 0;
		qnode<T> * node = queue.head;
		while (node != nullptr)
		{
			this->push(node->elem);
			node = node->prev;
		}
		return *this;
	}
	fifo<T>& operator=(fifo<T>&& queue) {
		deletenodes();
		lenght = queue.lenght;
		head = queue.head;
		tail = queue.tail;
		queue.head = nullptr;
		queue.tail = nullptr;
		return *this;
	}
	const T& push(const T& elem) {
		qnode<T> * oldtail = tail;

		tail = new qnode<T>;
		tail->elem = elem;
		tail->next = oldtail;
		tail->prev = nullptr;
		if (lenght > 0)
			oldtail->prev = tail;
		else
			head = tail;
		++lenght;
		return tail->elem;
	}
	T& pop() {
		if (lenght > 0)
		{
			T tmp = head->elem;
			qnode<T> * tmpnode = head;
			head = head->prev;
			if (lenght == 1)
				tail = nullptr;
			else
				head->next = nullptr;
			delete tmpnode;
			--lenght;
			return tmp;
		}
		else
			std::cerr << "Queue empty\n";	//error
	}
	size_t getLenght() const { return lenght; }
	bool isEmpty() const { return lenght == 0; }
};

// Dumps and prints fifo content
template <class T>
void dumpqueue(fifo<T>& queue) {
	while (!queue.isEmpty())
		std::cout << queue.pop();
	std::cout << std::endl;
}