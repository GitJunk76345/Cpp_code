#pragma once
/*
Template based, BST (Binary Search Tree) container class
*/

/*
TODO LIST:
 removing
 destructor
 prev/next
 universal traversal method?
 AVL
*/

#include <iostream>

template <typename K>
struct node
{
	node<K> * up;
	node<K> * left;
	node<K> * right;
	K key;
	size_t occurence; // how many times
	node(K nkey) : up(nullptr), left(nullptr), right(nullptr), key(nkey), occurence(0) {}
	node(K nkey, node * newup) : up(newup), left(nullptr), right(nullptr), key(nkey), occurence(0) {}

	void print(size_t depth) const {
		for (size_t i = 0; i < depth; ++i)
			std::cout << "  ";
		std::cout << key << " (" << occurence << ")" << std::endl;
	}
	void printall(int order, size_t depth) const {
		switch (order) {
		case -1: //print preorder
			print(depth);
			if (this->left != nullptr)
				left->printall(order, depth + 1);
			if (this->right != nullptr)
				right->printall(order, depth + 1);
			break;
		case 0: //print inorder
			if (this->left != nullptr)
				left->printall(order, depth + 1);
			print(depth);
			if (this->right != nullptr)
				right->printall(order, depth + 1);
			break;
		case 1:	//print postorder
			if (this->left != nullptr)
				left->printall(order, depth + 1);
			if (this->right != nullptr)
				right->printall(order, depth + 1);
			print(depth);
			break;
		}
		return;
	}
};

template <typename K>
class bst
{
	size_t nodes;	  // number of nodes in tree
	size_t elements;  // number of elements - sum of all occurences in all nodes
	node<K> * root;   // root node
public:
	bst() : nodes(0), elements(0), root(nullptr) {}
	//TODO
	~bst() {

	}
	//WORKING
	size_t size() const {
		return elements;
	}
	size_t nodeCount() const {
		return nodes;
	}
	//WORKING YET LOOKS UGLY NON-COMPACT
	size_t add(const K& key) { // adds element and returns amount of such lements in tree
		bool exist = false;
		node<K> * nod = root;
		node<K> * nodparrent = nullptr;
		while (nod != nullptr)
		{
			nodparrent = nod;
			if (nod->key == key)
			{
				exist = true;
				break;
			}
			if (nod->key < key)
				nod = nod->right;
			else
				nod = nod->left;	
		}
		if (!exist)
		{
			if(nodparrent == nullptr)
				nod = root = new node<K>(key);
			else
			{
				if (nodparrent->key > key)
					nod = nodparrent->left = new node<K>(key, nodparrent);
				else if (nodparrent->key < key)
					nod = nodparrent->right = new node<K>(key, nodparrent);
			}
			++nodes;
		}
		++(nod->occurence);
		++elements;
		return true;
	}

	//TODO
	bool remove(const K& key) {
		// TODO
		if (true)
			return true;
		else
			return false;
	}
	bool remove(const node<K> * n) { // removes pointed node
		// TODO
		if (true)
			return true;
		else
			return false;
	}
	//bool pop(const K& key) {} // decrements occurende and removes node while occurence == 0
	
	//WORKING
	void print(int order = 0) const { // ORDER -1 - preorder, 0 - inorder, 1 - postorder
		if (root == nullptr)
			return;
		root->printall(order, 0);
		return;		
	}
	size_t search(const K& key) const {
		node<K> * nod = root;
		size_t counter = 0;
		while (nod != nullptr)
		{
			if (nod->key == key)
			{
				counter = nod->occurence;
				break;
			}
			else if (nod->key > key)
				nod = nod->left;
			else if (nod->key < key)
				nod = nod->right;
		}
		return counter;  // return occurence of object in tree
	}

	//TODO
	const K& next(const K& key) {
	}
	const K& prev(const K& key) {
	}

	//WORKING YET HAS NO EXCEPTIONS FOR EMPTY TREE
	const K& min() { // UGLY
		node<K> * nod = root;
		if (root == nullptr)
		{
			std::cerr << "Error: bst is empty\n";
		}
		while (nod->left != nullptr)
			nod = nod->left;
		return nod->key;
	}
	const K& max() { // UGLY
		node<K> * nod = root;
		if (root == nullptr)
		{
			std::cerr << "Error: bst is empty\n";
		}
		while (nod->right != nullptr)
			nod = nod->right;
		return nod->key;
	}
};