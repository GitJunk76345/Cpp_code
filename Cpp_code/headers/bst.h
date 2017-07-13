#pragma once
/*
Template based, BST (Binary Search Tree) container class
*/

/*
TODO LIST:
 removing
 bst destructor
 prev/next <--
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
	size_t occurence;      // number of K keys in the node
	
	node(K nkey) : up(nullptr), left(nullptr), right(nullptr), key(nkey), occurence(0) {}
	node(K nkey, node * newup) : up(newup), left(nullptr), right(nullptr), key(nkey), occurence(0) {}

	node<K> * search(const K& key) {
		node<K> * nod = this;          // start from this node
		while (nod != nullptr)
		{
			if (nod->key == key)
				return nod;
			else if (nod->key > key)
				nod = nod->left;
			else if (nod->key < key)
				nod = nod->right;
		}
		return nullptr;                // key was not found in the tree
	}
	void remove() {
	/*
		Removes node from tree structure - TODO - resolve handling root in bst class 
	*/
		// TODO
		return;
	}
	node<K> * next(void)  {
		/*
			returns next in-order node or this, if there is no next node 
		*/
		node<K> * tmpnode = this;            // this is last in-order node
		if (tmpnode->right != nullptr)       // is right child present
		{
			tmpnode = tmpnode->right;        // right child is the next in-order node
			while (tmpnode->left != nullptr)
				tmpnode = tmpnode->left;     // left offspring of right child is the next in-order node
		}
		else
		{
			if (this->up != nullptr && this->up->left == this)
				tmpnode = this->up;          // this node's parrent is the next in-order node		
			else
			{
				node<K> * upnode = this;            // 
				while (upnode->up != nullptr && upnode->up->right == upnode)
					upnode = upnode->up;
				if (upnode->up != nullptr && upnode->up->left == upnode)
					tmpnode = upnode->up;
			}	
		}
		return tmpnode;
	}
	node<K> * prev(void)  {
		/*
		returns previous in-order node or this, if there is no previous node
		*/
		node<K> * tmpnode = this;            // this is first in-order node
		if (tmpnode->left != nullptr)        // is left child present
		{
			tmpnode = tmpnode->left;         // left child is the prev in-order node
			while (tmpnode->right != nullptr)
				tmpnode = tmpnode->right;    // right offspring of left child is the prev in-order node
		}
		else
		{
			if (this->up != nullptr && this->up->right == this)
				tmpnode = this->up;          // this node's parrent is the previous in-order node		
			else
			{
				node<K> * upnode = this;            // 
				while (upnode->up != nullptr && upnode->up->left == upnode)
					upnode = upnode->up;
				if (upnode->up != nullptr && upnode->up->right == upnode)
					tmpnode = upnode->up;
			}
		}
		return tmpnode;
	}
	K& next(const K& searchkey) {
		/*
			returns key to smallest node larger than searchkey or searchkey, if there is no larger node
		*/
		node<K> * tmpnode = this;            // this is last in-order node
		if (tmpnode->right != nullptr)       // is right child present
		{
			tmpnode = tmpnode->right;        // right child is the next in-order node
			while (tmpnode->left != nullptr)
				tmpnode = tmpnode->left;     // left offspring of right child is the next in-order node
		}
		else
		{
			if (this->up != nullptr && this->up->left == this)
				tmpnode = this->up;          // this node's parrent is the next in-order node
		}
		return tmpnode->key;
	}

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
		//delete nodes while traversing tree post-order
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
	bool fetch(const K& searchkey) { // decrements occurende and removes node while occurence == 0
		// TODO
		if (true)
			return true;
		else
			return false;
	}
		
	//WORKING
	void print(int order = 0) const { // ORDER -1 - pre-order, 0 - in-order, 1 - post-order
		if (root == nullptr)
			return;
		root->printall(order, 0);
		return;		
	}
	size_t search(const K& key) const {
		const node<K> * nod = root->search(key);
		if (nod == nullptr)
			return 0;
		else
			return nod->occurence;
	}

	//TODO
	const K& next(const K& searchkey) {
		/*
	SHOULD		returns key to smallest node larger than searchkey or searchkey, if there is no larger node
		*/
		if (root == nullptr)
		{
			std::cerr << "error - tree is empty\n";
			return K();
		}
		node<K> * nod = root->search(searchkey);
		if (nod == nullptr)
		{
			std::cerr << "error - no node before " << root->key << " node\n";
			return K();
		}
		nod = nod->next();
		return nod->key;
	}
	const K& prev(const K& key) {
		if (root == nullptr)
		{
			std::cerr << "error - tree is empty\n";
			return K();
		}
		node<K> * nod = root->search(key);
		if (nod == nullptr)
		{
			std::cerr << "error - no node before " << root->key << " node\n";
			return K();
		}
		nod = nod->prev();
		return nod->key;
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