#pragma once
/*
	Template based, BST (Binary Search Tree) container class.
	This container requires it's parameter typer to have operators of comparsion and relation defined
*/

/*
TODO LIST:
 universal traversal method?
 AVL
*/

#include <iostream>
#include "definitions.h"

namespace containers {
	
	template <typename K>
	struct node
	{
		node<K> * up;          // parrent node
		node<K> * left;        // left child
		node<K> * right;       // right
		size_t height;		   // height of the subtree
		K key;                 // node content
		size_t occurence;      // number of keys in the node
		
		node(K nkey) : up(nullptr), left(nullptr), right(nullptr), height(0), key(nkey), occurence(0) {}
		node(K nkey, node * newup) : up(newup), left(nullptr), right(nullptr), height(0), key(nkey), occurence(0) {}

		side sideofparrent() {
			/*
				Returns information about this nodes relation with it's parrent
			*/
			if (this->up == nullptr)        // this node has no parrent
				return ORPHAN;
			if (this->up->left == this)     // this node is left child of it's parrent
				return LEFT;
			if (this->up->right == this)    // this node is right child of it's parrent
				return RIGHT;
			else
				return MISSATTACHED;         // this node points at parrent, that's not pointing back on this node, as it's child
		}
		node<K> * search(const K& searchkey) {
			/*
				Searches for node containikng searchkey, starting from this node
			*/
			node<K> * nod = this;
			while (nod != nullptr)
			{
				if (nod->key == searchkey)
					return nod;
				else if (nod->key > searchkey)
					nod = nod->left;
				else if (nod->key < searchkey)
					nod = nod->right;
			}
			return nullptr;                // searchkey was not found in the tree
		}
		node<K> * searchparrent(const K& searchkey) {
			/*
				Searches for parrent node of node that would contain searchkey, starting from this node
			*/
			node<K> * nod = this;
			while (nod != nullptr)
			{
				if (nod->key == searchkey)
					return nod->up;
				else if (nod->key > searchkey)
				{
					if (nod->left == nullptr)
						return nod;
					nod = nod->left;
				}
				else if (nod->key < searchkey)
				{
					if (nod->right == nullptr)
						return nod;
					nod = nod->right;
				}
			}
		}

		int balancefactor() {
			int rh = this->right != nullptr ? this->right->height : -1;
			int lh = this->left  != nullptr ? this->left->height : -1;

			return rh - lh;
		}
		node<K> *  leftrot() {
			// NEW UNTESTED
			node<K> * swap = this->right;
			swap->up = this->up;
			if (this->sideofparrent() == LEFT)
				this->up->left = swap;
			if (this->sideofparrent() == RIGHT)
				this->up->right = swap;
			this->up = swap;
			this->right = swap->left;
			if(this->right != nullptr)
				this->right->up = this;
			swap->left = this;
			updateheights();
			return swap;
		}
		node<K> *  rightrot() {
			// NEW UNTESTED
			node<K> * swap = this->left;
			swap->up = this->up;
			if (this->sideofparrent() == LEFT)
				this->up->left = swap;
			if (this->sideofparrent() == RIGHT)
				this->up->right = swap;
			this->up = swap;
			this->left = swap->right;
			if (this->left != nullptr)
				this->left->up = this;
			swap->right = this;
			updateheights();
			return swap;
		}
		node<K> * cutnode(bool returnreplacer = false) {
			/*
				cuts node from tree structure
			*/
			node<K> * replacer = nullptr;
			if (this->left != nullptr && this->right != nullptr)       // if has 2 childs
			{
				// some code to determine which replacer to choose
				if (true)                                        // replace with next()
					replacer = this->next(true)->cutnode();      // cut next from subtree
				else                                             // replace with prev()
					replacer = this->prev(true)->cutnode();      // cut prev from subtree

				// assume pointers for replacer
				replacer->left = this->left;
				replacer->right = this->right;
				replacer->up = this->up;
				
				// assume pointers for replacer's neighbourhood
				if (replacer->left != nullptr)
					replacer->left->up = replacer;
				if (replacer->right != nullptr)
					replacer->right->up = replacer;
				if (sideofparrent() == LEFT)
					replacer->up->left = replacer;
				else if (sideofparrent() == RIGHT)
					replacer->up->right = replacer;
				replacer->updateheights();
}
			else if (this->left == nullptr && this->right == nullptr)  // if has no childs
			{
				if (sideofparrent() == LEFT)
					this->up->left = nullptr;
				else if (sideofparrent() == RIGHT)
					this->up->right = nullptr;
				this->up->updateheights();
			}
			else                                                       // if has one child
			{
				replacer = (this->left == nullptr ? this->right : this->left);
				if (sideofparrent() == LEFT)
					this->up->left = replacer;
				else if (sideofparrent() == RIGHT)
					this->up->right = replacer;
				replacer->up = this->up;
				this->up->updateheights();
			}
			if (returnreplacer)
				return replacer;
			else
				return this;
		}
		node<K> * remove() {
			/*
				Removes node from tree structure, returns node that replaced it's place
			*/

			node<K> * replacer = this->cutnode(true);
			delete this;
			return replacer;
		}
	
		node<K> * min(void) {
			/*
				Finds smallest node in this nodes subtree
			*/
			node<K> * nod = this;
			while (nod->left != nullptr)
				nod = nod->left;
			return nod;
		}
		node<K> * max(void) {
			/*
				Finds largest node in this nodes subtree
			*/
			node<K> * nod = this;
			while (nod->right != nullptr)
				nod = nod->right;
			return nod;
		}
		node<K> * next(bool subtreeonly = false) {
			/*
				returns next in-order node or nullptr, if there is no next node
			*/
			node<K> * tmpnode = this;            // this is last in-order node
			if (tmpnode->right != nullptr)       // is right child present
			{
				tmpnode = tmpnode->right;        // right child is the next in-order node
				while (tmpnode->left != nullptr)
					tmpnode = tmpnode->left;     // left offspring of right child is the next in-order node
			}
			else if (!subtreeonly)
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
					else
						tmpnode = nullptr;
				}
			}
			return tmpnode;
		}
		node<K> * prev(bool subtreeonly = false) {
			/*
				returns previous in-order node or nullptr, if there is no previous node
			*/
			node<K> * tmpnode = this;            // this is first in-order node
			if (tmpnode->left != nullptr)        // is left child present
			{
				tmpnode = tmpnode->left;         // left child is the prev in-order node
				while (tmpnode->right != nullptr)
					tmpnode = tmpnode->right;    // right offspring of left child is the prev in-order node
			}
			else if (!subtreeonly)
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
					else
						tmpnode = nullptr;
				}
			}
			return tmpnode;
		}
		node<K> * next(const K& searchkey) {
			/*
				returns smallest node larger than searchkey or nullptr, if there is no larger node
			*/

			node<K> * nod = search(searchkey);
			if (nod == nullptr) {
				//find parrent node to would be nod
				nod = searchparrent(searchkey);
				if (nod->key > searchkey)           // if it's larger then it's the next node
					return nod;
				else
					return nod->next();				// nod is previous node, find it's in-order successor
			}
			else
				return nod->next();					// found node for key - return in-order successor
		}
		node<K> * prev(const K& searchkey) {
			/*
				returns largest node smaller than searchkey or nullptr, if there is no smaller node
			*/

			node<K> * nod = search(searchkey);
			if (nod == nullptr) {
				//find parrent node to would be nod
				nod = searchparrent(searchkey);
				if (nod->key < searchkey)           // if it's smaller then it's the prev node
					return nod;
				else
					return nod->prev();				// nod is next node, find it's in-order predecessor
			}
			else
				return nod->prev();					// found node for key - return in-order predecessor
		}

		void updateheights() {
			/*
				Updates heights of nodes from this up to root or until no difference between new and old height is occuring
			*/

			int lh, rh;                                                    // left , right
			node<K> * nod = this;
			while (nod != nullptr)
			{
				lh = nod->left == nullptr ? -1 : nod->left->height;     // does parrent have left child
				rh = nod->right == nullptr ? -1 : nod->right->height;   // does parrent have right child
				nod->height = (lh > rh ? lh : rh) + 1;                  //  set height as higher branch height + 1
				nod = nod->up;                                          // process parrent node
			}
		}
		void print(size_t depth) const {
			/*
				Print this node's key
			*/
			for (size_t i = 0; i < depth; ++i)
				std::cout << "  ";
			std::cout << key << " (" << occurence << ")" << " [" << height << "]" << std::endl;
		}
		void printall(int order, size_t depth) const {
			/*
				Prints this node's subtree using specified order
			*/
			switch (order) {
			case PREORDER: //print preorder
				if (this->right != nullptr)
					right->printall(order, depth + 1);
				if (this->left != nullptr)
					left->printall(order, depth + 1);
				print(depth);
				break;
			case INORDER: //print inorder
				if (this->right != nullptr)
					right->printall(order, depth + 1);
				print(depth);
				if (this->left != nullptr)
					left->printall(order, depth + 1);
				break;
			case POSTORDER:	//print postorder
				print(depth);
				if (this->right != nullptr)
					right->printall(order, depth + 1);
				if (this->left != nullptr)
					left->printall(order, depth + 1);
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
		~bst() {
			/*
				Deletes all nodes through post-order traversal
			*/
			node<K> * deleted = root;
			node<K> * temp = nullptr;
			size_t level = 0;

			if (root == nullptr)
				return;
			while (true)
			{
				if (deleted->left != nullptr)      // retry with left subnode
				{
					++level;
					deleted = deleted->left;
					continue;
				}
				if (deleted->right != nullptr)      // retry with right subnode
				{
					++level;
					deleted = deleted->right;
					continue;
				}
				// deletion of node that has no subnodes begins here
				if (deleted->up != nullptr)            // if this isn't root node...
				{
					if (deleted->up->left == deleted)  // is deleted node left subnode?
					{
						deleted->up->left = nullptr;   // cut link from this node's parrent to this node
					}
					if (deleted->up->right == deleted)  // is deleted node right subnode?
					{
						deleted->up->right = nullptr;   // cut link from this node's parrent to this node
					}
					temp = deleted;
					deleted = deleted->up;             // in next iteration continue with parrent node
					delete temp;
					--level;
				}
				else                                   // processing root node that has no children
				{
					delete deleted;
					break;                             // all nodes in tree has been deleted by now
				}
			}
		}
		size_t size() const {
			return elements;
		}
		size_t nodeCount() const {
			return nodes;
		}

		// TODO WORK IN PROGRESS
		void avlcheck(node<K> * checkednode ) {
			/*
				some inconsistencies occuring - incorrect height may happen after AVL check
			*/
			node<K> * nod;
			while (checkednode != nullptr)
			{
				if (checkednode->balancefactor() > 1)            // tree is right heavy
				{
					if (checkednode->right->balancefactor() < 0) // tree's right subtree is left heavy
					{
						// double left rotation
						checkednode->right->rightrot();
						nod = checkednode->leftrot();
						if (nod->up == nullptr)
							root = nod;
					}
					else
					{
						// single left rotation
						nod = checkednode->leftrot();
						if (nod->up == nullptr)
							root = nod;
					}
				}
				else if (checkednode->balancefactor() < -1)      // tree is left heavy
				{
					if (checkednode->left->balancefactor() > 0)  // tree's left subtree is right heavy
					{
						// double right rotation
						checkednode->left->leftrot();
						nod = checkednode->rightrot();
						if (nod->up == nullptr)
							root = nod;
					}
					else
					{
						// single right rotation
						nod = checkednode->rightrot();
						if (nod->up == nullptr)
							root = nod;
					}
				}
				checkednode = checkednode->up;
			}
		}

		// WORKING YET LOOKS UGLY
		size_t add(const K& key) {
			/*
				Adds element and returns amount of such elements in tree
			*/
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
				if (nodparrent == nullptr)
					nod = root = new node<K>(key);
				else
				{
					if (nodparrent->key > key)
						nod = nodparrent->left = new node<K>(key, nodparrent);
					else if (nodparrent->key < key)
						nod = nodparrent->right = new node<K>(key, nodparrent);
				}
				++nodes;
				nod->up->updateheights();
				avlcheck(nod);            // AVL check
			}
			++(nod->occurence);
			++elements;
			return true;
		}
		bool fetch(const K& searchkey) {
			/*
				Removes 1 key occurence from tree and returns true or false if there is nothing to remove
			*/
			node <K> * nod = root->search(searchkey);
			if (nod != nullptr)
			{
				if (nod->occurence > 0)        // just decrease occurence
				{
					--(nod->occurence);
				}
				if (nod->occurence == 0)                          // delete actual node
				{
					if (nod == root)            // if removing root node refresh root pointer
						root = nod->remove();
					else
						nod->remove();
					--nodes;
				}
				--elements;
				return true;                   // fetch successfull
			}
			else
				return false;                  // not even single occurence of key in whole tree
		}

		//WORKING
		void print(int order = INORDER) const {
			/*
				Prints whole tree in one of 3 ways:
				INORDER, PREORDER, POSTORDER
			*/
			if (root == nullptr)
				return;
			root->printall(order, 0);
			return;
		}
		size_t search(const K& searchkey) const {
			/*
				Returns number of searchkey occurence in tree
			*/
			const node<K> * nod = root->search(searchkey);
			if (nod == nullptr)
				return 0;
			else
				return nod->occurence;
		}
		const K& next(const K& searchkey) {
			/*
				Returns key to smallest node larger than searchkey or searchkey, if there is no larger node
			*/
			if (root == nullptr)
			{
				std::cerr << "error - tree is empty\n";
				return K();
			}
			node<K> * nod = root->next(searchkey);
			if (nod == nullptr)
			{
				std::cerr << "error - no node after " << searchkey << " node\n";
				return K();
			}
			return nod->key;
		}
		const K& prev(const K& searchkey) {
			/*
				Returns key to smallest node larger than searchkey or searchkey, if there is no larger node
			*/
			if (root == nullptr)
			{
				std::cerr << "error - tree is empty\n";
				return K();
			}
			node<K> * nod = root->prev(searchkey);
			if (nod == nullptr)
			{
				std::cerr << "error - no node before " << searchkey << " node\n";
				return K();
			}
			return nod->key;
		}

		//WORKING YET HAS NO EXCEPTIONS FOR EMPTY TREE
		const K& min() { // UGLY
			if (root == nullptr)
			{
				std::cerr << "Error: bst is empty\n";
			}
			else
				return root->min()->key;
		}
		const K& max() { // UGLY
			if (root == nullptr)
			{
				std::cerr << "Error: bst is empty\n";
			}
			else
				return root->max()->key;
		}
	};
}