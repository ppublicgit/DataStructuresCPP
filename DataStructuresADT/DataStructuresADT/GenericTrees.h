#pragma once

template <typename E> class GenNodeADT {
public:
	virtual ~GenNodeADT() {} //base destructor

	//return the nodes value
	virtual E& element() = 0;

	//set the nodes value
	virtual void setElement(const E&) = 0;

	//return the nodes left child
	virtual GenNodeADT* leftMostChild() const = 0;

	//return the nodes right child
	virtual GenNodeADT* rightSibling() const = 0;

	//set the nodes left child
	virtual void setLeftMostChild(GenNodeADT*) = 0;

	//set the nodes right child
	virtual void setRightSibling(GenNodeADT*) = 0;

	//return true of the node is a leaf, false otherwise
	virtual bool isLeaf() = 0;
};

template <typename E>
void preorder(GenNodeADT<E>* root) {
	if (root == NULL)return; //empty subtree, do nothing
	visit(root);
	preorder(root->leftMostChild());
	preorder(root->rightSibling());
}

// simple General Tree Node Implementation
template <typename Key, typename E> class GenNode {//: public GenNodeADT<E> {
private:
	Key k;
	E it;
	GenNode<Key, E>* lc;
	GenNode<Key, E>* rs;
	GenNode<Key, E>* pt;
	

public:
	//two constructors -- with and without initial values
	GenNode() { lc = rs = pt = NULL; }
	GenNode(Key K, E e, GenNode<Key, E>* l = NULL, GenNode<Key, E>* r = NULL, GenNode<Key, E>* p = NULL)
	{
		k = K; it = e; lc = l; rs = r; pt = p;
	}

	~GenNode() {}

	//functions to set and return value and key
	E& element() { return it; }
	Key& key() { return k; }
	void setElement(const E& e) { it = e; }
	void setKey(const Key& K) { k = K; }

	//functions to set and return the children
	GenNode<Key, E>* leftMostChild() { return lc; }
	GenNode<Key, E>* rightSibling() { return rs; }
	GenNode<Key, E>* parent() { return pt; }
	void setLeftMostChild(GenNode<Key, E>* b) { lc = (GenNode<Key, E>*)b; lc->setParent(this); }
	void setRightSibling(GenNode<Key, E>* b) { rs = (GenNode<Key, E>*)b; rs->setParent(parent()); }
	void setParent(GenNode<Key, E>* b) { pt = (GenNode<Key, E>*)b; }

	//return true if it is a leaf, false otherwise
	bool isLeaf() {
		return (lc == NULL);
	}
};


template <typename Key, typename E> class GenTree {
private:
	GenNode<Key, E>* root; //root of the BST
	int nodecount; //number of nodes in bst

	//Private helper functions
	void clearhelp(GenNode<Key, E>*);
	GenNode<Key, E>* inserthelp(GenNode<Key, E>*, Key&, E&);
	//GenNode<Key, E>* deletemin(GenNode<Key, E>*);
	//GenNode<Key, E>* getmin(GenNode<Key, E>*);
	//GenNode<Key, E>* removehelp(GenNode<Key, E>*, Key&);
	//E findhelp(GenNode<Key, E>*, Key&);
	void printhelp(GenNode<Key, E>*, int);

public:
	GenTree() {
		root = NULL; nodecount = 0;
	}

	GenTree(Key k, E it, GenNode<Key, E>* lc = NULL) {
		root->setKey(k); root->setElement(it); 
		root->setLeftMostChild(lc); 
		root->setRightSibling(GenNode<Key, E> * NULL); 
		root->setParent(GenNode<Key, E> * NULL); 
		nodecount = 1;
	}

	~GenTree() { clear(); }

	void clear() {
		clearhelp(root); root = NULL; nodecount = 0;
	}

	void insert(Key k, E it) {
		root = inserthelp(root, k, it);
		while (root->parent() != NULL) {
			root = root->parent();
		}
		nodecount++;
	}

	GenNode<Key, E>* getRoot() { return root; }

	/*
	E remove() {

	}

	E removeAny() {

	}

	E find() {

	}
	*/
	int size() { return nodecount; }

	void print() {
		printhelp(root, 0);
	}
};

template <typename Key, typename E>
void GenTree<Key, E>::clearhelp(GenNode<Key, E>* node) {
	if (node == NULL) return;
	clearhelp(node->leftMostChild());
	clearhelp(node->rightSibling());
	delete node;
}

template <typename Key, typename E>
GenNode<Key, E>* GenTree<Key, E>::inserthelp(GenNode<Key, E>* node, Key& k, E& it) {
	if (node == NULL) return new GenNode<Key, E>(k, it);
	else if (k < node->key()) {
		node->setLeftMostChild(inserthelp(node->leftMostChild(), k, it));
	}
	else {
		if (node->parent() == NULL) { //create new root
			GenNode<Key, E>* temp = new GenNode<Key, E>(k, it, node);
			node->setParent(temp);
			return temp;
		}
		else {
			node->setRightSibling(inserthelp(node->rightSibling(), k, it));
		}
	}
}

/*
//remove a node with key value k
//return the tree with the node removed
template <typename Key, typename E>
GenNode<Key, E>* GenTree<Key, E>::removehelp(GenNode<Key, E>* rt, Key& k) {
	if (rt == NULL) return NULL;
	else if (k < rt->key())
		rt->setLeftMostChild(removehelp(rt->leftMostChild(), k));
	else if (k > rt->key())
		rt->setRightSibling(removehelp(rt->rightSibling(), k));
	else {
		GenNode<Key, E>* temp = rt;
		if (rt->leftMostChild() == NULL) {
			rt = rt->rightSibling();
			delete temp;
		}
		else if (rt->rightSibling() == NULL) {
			rt = rt->leftMostChild();
			delete temp;
		}
		else {
			GenNode<Key, E>* temp = getmin(rt->rightSibling());
			rt->setElement(temp->element());
			rt->setKey(temp->key());
			rt->setRightSibling(deletemin(rt->right()));
			delete temp;
		}
	}
	return rt;
}
*/
template <typename Key, typename E>
void GenTree<Key, E>::printhelp(GenNode<Key, E>* rt, int level) {
	if (rt == NULL) return;
	printhelp(rt->leftMostChild(), level + 1);
	for (int i = 0; i < level; i++)
		std::cout << "  ";
	std::cout << rt->key() << "\n";
	printhelp(rt->rightSibling(), level);
}
