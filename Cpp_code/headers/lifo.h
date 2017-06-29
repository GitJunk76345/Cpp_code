#pragma once
/* 
	Template based lifo (Last In First Out) container class
*/

#include <iostream>

template <typename T>
class lifo
{
	size_t height;
	size_t capacity;
	T*     data;
public:
	lifo(size_t size) : capacity(size), height(0) { data = new T[capacity];	}
	~lifo() { delete[] data; }

	lifo(const lifo<T>& stack) : height(stack.height), capacity(stack.capacity) {
		data = new T[capacity];
		for (size_t i = 0; i < height; ++i)
			data[i] = stack.data[i];
	}
	lifo(lifo<T>&& stack) : height(stack.height), capacity(stack.capacity) {
		data = stack.data;
		stack.data = nullptr;
	}
	lifo<T>& operator=(const lifo<T>& stack) {
		height = stack.height;
		capacity = stack.capacity;
		delete[] data;
		data = new T[capacity];
		for (size_t i = 0; i < height; ++i)
			data[i] = stack.data[i];
	}
	lifo<T>& operator=(lifo<T>&& stack) {
		height = stack.height;
		capacity = stack.capacity;
		delete[] data;
		data = stack.data;
		stack.data = nullptr;
	}

	const T& push(const T& elem) {
		if (height < capacity)
		{
			data[height] = elem;
			++height;
			return data[height - 1];
		}
		else
			std::cerr << "Stack overflow\n";    //error
	}
	T& pop() {
		if (height > 0)
		{
			--height;
			return data[height];
		}
		else
			std::cerr << "Stack empty\n";	//error
	}
	const T& peek() const {
		if (height > 0)
		{
			return data[height-1];
		}
		else
			std::cerr << "Stack empty\n";	//error
	}
	size_t getCapacity() { return capacity; }
	size_t getFree() { return capacity - height; }
	size_t getHeight() { return height; }
	bool isEmpty() const { return height == 0; }
	bool isFull() const { return height == capacity; }
};

// Dumps and prints lifo content
template <class T>
void dumpstack(lifo<T>& stack) {
	while (!stack.isEmpty())
		std::cout << stack.pop();
}