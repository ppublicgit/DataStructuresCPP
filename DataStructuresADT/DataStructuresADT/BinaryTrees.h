#pragma once
#include <iostream>
#include <assert.h>
#include "Dictionary.h"

//binary tree node abstract class
template <typename E> class BinNode {
public:
	virtual ~BinNode() {} //base destructor

	//return the nodes value
	virtual E& element() = 0;

	//set the nodes value
	virtual void setElement(const E&) = 0;

	//return the nodes left child
	virtual BinNode* left() const = 0;

	//return the nodes right child
	virtual BinNode* right() const = 0;

	//set the nodes left child
	virtual void setLeft(BinNode*) = 0;

	//set the nodes right child
	virtual void setRight(BinNode*) = 0;

	//return true of the node is a leaf, false otherwise
	virtual bool isLeaf() = 0;
};

template <typename E>
void preorder(BinNode<E>* root) {
	if (root == NULL)return; //empty subtree, do nothing
	visit(root);
	preorder(root->left());
	preorder(root->right());
}

//simple binary tree node implementation
template <typename Key, typename E> class BSTNode : public BinNode<E> {
private:
	Key k;
	E it;
	BSTNode* lc;
	BSTNode* rc;

public:
	//two constructors -- with and without initial values
	BSTNode() { lc = rc = NULL; }
	BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL)
	{
		k = K; it = e; lc = l; rc = r;
	}
	~BSTNode() {}

	//functions to set and return value and key
	E& element() { return it; }
	Key& key() { return k; }
	void setElement(const E& e) { it = e; }
	void setKey(const Key& K) { k = K; }

	//functions to set and return the children
	inline BSTNode* left() const { return lc; }
	inline BSTNode* right() const { return rc; }
	void setLeft(BinNode<E>* b) { lc = (BSTNode*)b; }
	void setRight(BinNode<E>* b) { rc = (BSTNode*)b; }

	//return true if it is a leaf, false otherwise
	bool isLeaf() {
		return (lc == NULL) && (rc == NULL);
	}
};

template <typename Key, typename E>
bool checkBST(BSTNode<Key, E>* root, Key low, Key high) {
	if (root == NULL) return true; //empty subtree
	Key rootkey = root->key;
	if ((rootkey < low) || (rootkey > high))
		return false; //out of range
	if (!checkBST<Key, E>(root->left(), low, rootkey))
		return false; //left side failed
	return checkBST<Key, E>(root->right(), rootkey, high);
}

/*
//=================== separating leaf and internal nodes ========================
// node implementation with simple inheritance
class VarBinNode { //node abstract baseclass
public:
	virtual ~VarBinNode() {}
	virtual bool isLeaf() = 0;
};

class LeafNode : public VarBinNode {
private:
	Operand var; //operand value

public:
	LeafNode(const Operand& val) { var = val; }// constructor
	bool isLeaf() { return true; }
	Operand value() { return var; }//return node value
};

class IntlNode : public VarBinNode {//internal node
private:
	VarBinNode* left;
	VarBinNode* right;
	Operator opx; //operator value

public:
	IntlNode(const Operator op, VarBinNode* l, VarBinNode* r) {
		opx = op; left = l; right = r;
	}
	bool isLeaf() { return false; }
	VarBinNode* leftchild() { return left; }
	VarBinNode* rightchild() { return right; }
	std::Operator value() { return opx; }
};

void traverse(VarBinNode* root) { //preordertraverse
	if (root == NULL) return;
	if (root->isLeaf()) std::cout << "Leaf : " << ((LeafNode*)root->value()) << std::endl;
	else {
		std::cout << "Internal : "
			<< ((IntlNode*)root->value()) << std::endl;
		traverse(((IntlNode*)root)->leftchild());
		traverse(((IntlNode*)root)->rightchild());
	}
}

//=================== separating leaf and internal nodes composite design pattern =====

// node implementation with composite design pattern
class VarBinNode { //node abstract baseclass
public:
	virtual ~VarBinNode() {}
	virtual bool isLeaf() = 0;
	virtual void traverse() = 0;
};

class LeafNode : public VarBinNode {
private:
	Operand var; //operand value

public:
	LeafNode(const Operand& val) { var = val; }// constructor
	bool isLeaf() { return true; }
	Operand value() { return var; }//return node value
	void traverse() { std::cout << "Leaf : " << value() << std::endl; }
};

class IntlNode : public VarBinNode {//internal node
private:
	VarBinNode* lc;
	VarBinNode* rc;
	Operator opx; //operator value

public:
	IntlNode(const Operator op, VarBinNode* l, VarBinNode* r) {
		opx = op; lc = l; rc = r;
	}
	bool isLeaf() { return false; }
	VarBinNode* left() { return lc; }
	VarBinNode* right() { return rc; }
	Operator value() { return opx; }
	void traverse() {
		std::cout << "Internal : " << value() << std::endl;
		if (left() != NULL) left()->traverse();
		if (right() != NULL) right()->traverse();
	}
};

//do a preorder traversal
void traverse(VarBinNode* root) {
	if (root != NULL) root->traverse();
}
*/

//binary search tree implementation for the dictionary ADT
template <typename Key, typename E>
class BST : public SALdict<Key, E> {
private:
	BSTNode<Key, E>* root; //root of the BST
	int nodecount; //number of nodes in bst

	//private helper functions
	void clearhelp(BSTNode<Key, E>*);
	BSTNode<Key, E>* inserthelp(BSTNode<Key, E>*, const Key&, const E&);
	BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
	BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
	BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
	E findhelp(BSTNode<Key, E>*, const Key&) const;
	void printhelp(BSTNode<Key, E>*, int) const;

public:
	BST() { root = NULL; nodecount = 0; }
	~BST() { clearhelp(root); }

	void clear() //reinitiatilaize tree
	{
		clearhelp(root); root = NULL; nodecount = 0;
	}

	//insert a record into the tree
	//k key value of record
	//e the record to insert
	void insert(const Key& k, const E& e) {
		root = inserthelp(root, k, e);
		nodecount++;
	}

	//remove a record from the tree
	//k key value of record to remove
	//return: the record removed or Null if there is none
	E remove(const Key& k) {
		E temp = findhelp(root, k);
		if (temp != NULL) {
			root = removehelp(root, k);
			nodecount--;
		}
		return temp;
	}

	//remove and return the root node from the dictionary
	// return the record removed, null if tree is empty
	E removeAny() { //delete min value
		if (root != NULL) {
			E temp = root->element();
			root = removehelp(root, root->key());
			nodecount--;
			return temp;
		}
		else return NULL;
	}

	//return the record with key value k, null if non exists
	//k the key vcalue to find
	//return some record matching k
	//return true if such exists, false otherwise. if multiple
	//records match k, return an arbitrary one
	E find(const Key& k) const { return findhelp(root, k); }

	//return the number of records in the dictionary
	int size() { return nodecount; }

	void print() const { //print the contents of BST
		if (root == NULL) std::cout << "The BST is empty. \n" << std::endl;
		else printhelp(root, 0);
	}
};

template <typename Key, typename E>
E BST<Key, E>::findhelp(BSTNode<Key, E>* root, const Key& k) const {
	if (root == NULL) return NULL;
	if (k < root->key()) return findhelp(root->left(), k);
	else if (k > root->key()) return findhelp(root->right(), k);
	else return root->element();
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it) {
	if (root == NULL) return new BSTNode<Key, E>(k, it, NULL, NULL);
	if (k < root->key())
		root->setLeft(inserthelp(root->left(), k, it));
	else root->setRight(inserthelp(root->right(), k, it));
	return root;
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::deletemin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL) return rt->right();
	else {
		rt->setLeft(deletemin(rt->left()));
	}
}

template<typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::getmin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL) { return rt; }
	else return getmin(rt->left());
}

//remove a node with key value k
//return the tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::removehelp(BSTNode<Key, E>* rt, const Key& k) {
	if (rt == NULL) return NULL;
	else if (k < rt->key())
		rt->setLeft(removehelp(rt->left(), k));
	else if (k > rt->key())
		rt->setRight(removehelp(rt->right(), k));
	else {
		BSTNode<Key, E>* temp = rt;
		if (rt->left() == NULL) {
			rt = rt->right();
			delete temp;
		}
		else if (rt->right() == NULL) {
			rt = rt->left();
			delete temp;
		}
		else {
			BSTNode<Key, E>* temp = getmin(rt->right());
			rt->setElement(temp->element());
			rt->setKey(temp->key());
			rt->setRight(deletemin(rt->right()));
			delete temp;
		}
	}
	return rt;
}

template <typename Key, typename E>
void BST<Key, E>::clearhelp(BSTNode<Key, E>* root) {
	if (root == NULL) return;
	clearhelp(root->left());
	clearhelp(root->right());
	delete root;
}

template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* root, int level) const {
	if (root == NULL) return;
	printhelp(root->left(), level + 1);
	for (int i = 0; i < level; i++)
		std::cout << "  ";
	std::cout << root->key() << "\n";
	printhelp(root->right(), level + 1);
}

//heap min class
template <typename E> class heapMinTree {
private:
	E* Heap; //pointer to the heap array
	int maxsize; //maxize of heap
	int n; //number of elements in heap

	//helper function to put element in its correct place 
	void siftdown(int pos) {
		while (!isLeaf(pos)) { //sotp if position is a leaf
			int j = leftchild(pos);
			int rc = rightchild(pos);
			if ((rc < n) && prior(Heap[rc], Heap[j]))
				j = rc; //set j to greater childs value
			if (prior(Heap[pos], Heap[j])) return; //done
			swap(Heap, pos, j);
			pos = j; //move down
		}
	}

	bool prior(E left, E right) {
		return left < right;
	}

	void swap(E A[], int i, int j) {
		E temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}

	void printhelp(int pos, int level) {
		int lc = leftchild(pos);
		if (lc < 0 || lc >= n) {
			for (int i = 0; i < level; i++)
				std::cout << "  ";
			std::cout << Heap[pos];
			padwhitespace(Heap[pos]);
			std::cout << "\n";
		}
		else {
			printhelp(lc, level + 1);
			for (int i = 0; i < level; i++)
				std::cout << "  ";
			std::cout << Heap[pos];
			padwhitespace(Heap[pos]);
			std::cout << "\n";
			int rc = rightchild(pos);
			if (rc > 0 && rc < n) {
				printhelp(rc, level + 1);
			}
		}
	}

	void padwhitespace(int num) {
		int maxNum = Heap[n-1];
		int maxlen = 0;
		for (maxlen; maxNum > 0; maxlen++) {
			maxNum = maxNum / 10;
		}
		int numlen = 0;
		if (num == 0) { numlen++; }
		for (numlen; num > 0; numlen++) {
			num = num / 10;
		}
		int len = maxlen - numlen;
		for (int i = 0; i <= len; i++) {
			std::cout << " ";
		}
	}

public:
	heapMinTree(E* h, int num, int max) {
		Heap = h; n = num; maxsize = max; buildHeap();
	}

	heapMinTree(int max=100) {
		Heap = new E[max]; n = 0; maxsize = max; buildHeap();
	}

	~heapMinTree() {
		delete Heap;
	}

	int size() const { return n; }
	bool isLeaf(int pos) const { return (pos >= n / 2) && (pos < n); }
	int leftchild(int pos) const { return 2 * pos + 1; } // return left child position
	int rightchild(int pos) const { return 2 * pos + 2; } //return right hcild postiion
	int parent(int pos) const { return (pos - 1) / 2; } //return parent position
	void buildHeap() {
		for (int i = n / 2 - 1; i >= 0; i--) siftdown(i);
	}

	//insert it into the heap
	void insert(const E& it) {
		assert(n < maxsize, "Heap is full");
		int curr = n++;
		Heap[curr] = it; //start at end of heap
		//now sift up until curr's parent > curr
		while ((curr != 0) && prior(Heap[curr], Heap[parent(curr)])) {
			swap(Heap, curr, parent(curr));
			curr = parent(curr);
		}
	}

	//remove first value
	E removeFirst() {
		assert(n > 0, "Heap is empty");
		swap(Heap, 0, --n);//swap first with last value
		if (n != 0) siftdown(0); //siftdown new root value
		return Heap[n];
	}

	//remove and return element at specified position
	E remove(int pos) {
		assert((pos >= 0) && (pos < n), "Bad position");
		if (pos == (n - 1)) n--; //last element, no work to do
		else
		{
			swap(Heap, pos, --n); //swap with last value
			while ((pos != 0) && (prior(Heap[pos], Heap[parent(pos)]))) {
				swap(Heap, pos, parent(pos)); //push up large key
				pos = parent(pos);
			}
			if (n != 0) siftdown(pos); // pushdown small key
		}
		return Heap[n];
	}

	void print() { //print the contents of BST
		if (n == 0) std::cout << "The heap is empty. \n" << std::endl;
		else printhelp(0, 0);
		std::cout << std::endl;
	}
};

//heap max class
template <typename E> class heapMaxTree {
private:
	E* Heap; //pointer to the heap array
	int maxsize; //maxize of heap
	int n; //number of elements in heap

	//helper function to put element in its correct place 
	void siftdown(int pos) {
		while (!isLeaf(pos)) { //sotp if position is a leaf
			int j = leftchild(pos);
			int rc = rightchild(pos);
			if ((rc < n) && prior(Heap[rc], Heap[j]))
				j = rc; //set j to greater childs value
			if (prior(Heap[pos], Heap[j])) return; //done
			swap(Heap, pos, j);
			pos = j; //move down
		}
	}

	bool prior(E left, E right) {
		return left > right;
	}

	void swap(E A[], int i, int j) {
		E temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}

	void printhelp(int pos, int level) {
		int lc = leftchild(pos);
		if (lc < 0 || lc >= n) {
			for (int i = 0; i < level; i++)
				std::cout << "  ";
			padwhitespace(Heap[pos]);
			std::cout << Heap[pos] << "\n";
		}
		else {
			printhelp(lc, level + 1);
			for (int i = 0; i < level; i++)
				std::cout << "  ";
			padwhitespace(Heap[pos]);
			std::cout << Heap[pos] << "\n";
			int rc = rightchild(pos);
			if (rc > 0 && rc < n) {
				printhelp(rc, level + 1);
			}
		}
	}

	void padwhitespace(int num) {
		int maxNum = Heap[0];
		int maxlen = 0;
		for (maxlen; maxNum > 0; maxlen++) {
			maxNum = maxNum / 10;
		}
		int numlen = 0;
		if (num == 0) { numlen++; }
		for (numlen; num > 0; numlen++) {
			num = num / 10;
		}
		int len = maxlen - numlen;
		for (int i = 0; i <= len; i++) {
			std::cout << " ";
		}
	}

public:
	heapMaxTree(E* h, int num, int max) {
		E* Heap = h; n = num; maxsize = max; buildHeap();
	}

	heapMaxTree(int max = 100) {
		Heap = new E[max]; n = 0; maxsize = max; buildHeap();
	}

	~heapMaxTree() {
		delete Heap;
	}

	int size() const { return n; }
	bool isLeaf(int pos) const { return (pos >= n / 2) && (pos < n); }
	int leftchild(int pos) const { return 2 * pos + 1; } // return left child position
	int rightchild(int pos) const { return 2 * pos + 2; } //return right hcild postiion
	int parent(int pos) const { return (pos - 1) / 2; } //return parent position
	void buildHeap() {
		for (int i = n / 2 - 1; i >= 0; i--) siftdown(i);
	}

	//insert it into the heap
	void insert(const E& it) {
		assert(n < maxsize, "Heap is full");
		int curr = n++;
		Heap[curr] = it; //start at end of heap
		//now sift up until curr's parent > curr
		while ((curr != 0) && prior(Heap[curr], Heap[parent(curr)])) {
			swap(Heap, curr, parent(curr));
			curr = parent(curr);
		}
	}

	//remove first value
	E removeFirst() {
		assert(n > 0, "Heap is empty");
		swap(Heap, 0, --n);//swap first with last value
		if (n != 0) siftdown(0); //siftdown new root value
		return Heap[n]; 
	}

	//remove and return element at specified position
	E remove(int pos) {
		assert((pos >= 0) && (pos < n), "Bad position");
		if (pos == (n - 1)) n--; //last element, no work to do
		else
		{
			swap(Heap, pos, --n); //swap with last value
			while ((pos != 0) && (prior(Heap[pos], Heap[parent(pos)]))) {
				swap(Heap, pos, parent(pos)); //push up large key
				pos = parent(pos);
			}
			if (n != 0) siftdown(pos); // pushdown small key
		}
		return Heap[n];
	}


	void print() { //print the contents of BST
		if (n == 0) std::cout << "The heap is empty. \n" << std::endl;
		else printhelp(0, 0);
		std::cout << std::endl;
	}

};


//Huffman tree node abstract base class
template <typename E> class HuffNode {
public:
	virtual ~HuffNode() {};
	virtual int weight() = 0;
	virtual bool isLeaf() = 0;
};

template <typename E> class HuffLeafNode : public HuffNode<E> {
private:
	E it;
	int wgt;

public:
	HuffLeafNode(const E& val, int freq) {
		it = val; wgt = freq;
	}

	int weight() { return wgt; }
	E val() { return it; }
	bool isLeaf() { return true; }
};

template <typename E> class HuffIntlNode : public HuffNode<E> {
private:
	int wgt;
	HuffNode<E>* lc;
	HuffNode<E>* rc;

public:
	HuffIntlNode(HuffNode<E>* l, HuffNode<E>* r) {
		wgt = l->weight() + r->weight(); lc = l; rc = r;
	}

	int weight() {
		return wgt;
	}
	bool isLeaf() { return false; }
	HuffNode<E>* left() const {
		return lc;
	}
	HuffNode<E>* right() const {
		return rc;
	}
	void setLeft(HuffNode<E>* b) { lc = (HuffNode<E>*)b; }
	void setRight(HuffNode<E>* b) { rc = (HuffNode<E>*)b; }
};

//HuffTree is a template of two parameters: the element
//type being coded and a comparator for two such elements.
template <typename E>
class HuffTree {
private:
	HuffNode<E>* Root; //tree root

public:
	HuffTree(E& val, int freq) {//leaf constructor
		Root = new HuffLeafNode<E>(val, freq);
	}
	//internal node constructor
	HuffTree(HuffTree<E>* l, HuffTree<E>* r) {
		Root = new HuffIntlNode<E>( l->root(), r->root());
	}
	~HuffTree() {}
	HuffNode<E>* root() { return Root; } //get root
	int weight() { return Root->weight(); }
};

/*
//Build a huffman tree from a collection of frequencies/weights
template <typename E>
HuffTree<E>* buildHuff(HuffTree<E>** TreeArray, int count) {
	heap<HuffTree<E>*, minTreeComp>* (TreeArray, count, count);
	HuffTree<char>* temp1, * temp2, * temp3 = NULL;
	while (forest->size() > 1) {
		temp1 = forest->removefirst();
		temp2 = forest->removefirst();
		temp3 = new HuffTree<E>(temp1, temp2);
		forest->insert(temp3);
		delete temp1;
		delete temp2;
	}
	return temp3;
}
*/


