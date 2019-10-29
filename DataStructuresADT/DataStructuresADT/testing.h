#pragma once
#include <iostream>
// simple General Tree Node Implementation
template <typename Char> class TrieNodeTest {
private:
	char letter;
	TrieNodeTest<Char>* lc;
	TrieNodeTest<Char>* rs;
	TrieNodeTest<Char>* pt;


public:
	//two constructors -- with and without initial values
	TrieNodeTest() { letter = NULL;  lc = rs = pt = NULL; }
	TrieNodeTest(char c, TrieNodeTest<Char>* l = NULL, TrieNodeTest<Char>* r = NULL, TrieNodeTest<Char>* p = NULL)
	{
		letter = c; lc = l; rs = r; pt = p;
	}

	~TrieNodeTest() {}

	//functions to set and return value and key
	char getLetter() { return letter; }
	void setLetter(char c) { letter = c; }

	//functions to set and return the children
	TrieNodeTest<Char>* leftMostChild() { return lc; }
	TrieNodeTest<Char>* rightSibling() { return rs; }
	TrieNodeTest<Char>* parent() { return pt; }
	void setLeftMostChild(TrieNodeTest<Char>* b) { lc = (TrieNodeTest<Char>*)b; }// lc->setParent(this);
	void setRightSibling(TrieNodeTest<Char>* b) { rs = (TrieNodeTest<Char>*)b; }// rs->setParent(parent());
	void setParent(TrieNodeTest<Char>* b) { pt = (TrieNodeTest<Char>*)b; }

	//return true if it is a leaf, false otherwise
	bool isLeaf() {
		return (lc == NULL);
	}
};

template <typename Char> class AlphabetTrieTesting {
private:
	TrieNodeTest<Char>* root; //root of the BST
	int nodecount; //number of nodes in bst
	int wordcount;
	//Private helper functions
	void clearhelp(TrieNodeTest<Char>* node);
	//GenNode<Key, E>* inserthelp(GenNode<Key, E>*, Key&, E&);
	//GenNode<Key, E>* deletemin(GenNode<Key, E>*);
	//GenNode<Key, E>* getmin(GenNode<Key, E>*);
	//GenNode<Key, E>* removehelp(GenNode<Key, E>*, Key&);
	//E findhelp(GenNode<Key, E>*, Key&);
	void printhelp(TrieNodeTest<Char>*, int);

	TrieNodeTest<Char>* insertRestofWord(TrieNodeTest<Char>* node, Char word, int i, bool siblingtraverse) {
		char currletter;
		if (siblingtraverse) {
			while (node != NULL) {
				currletter = word[i];
				if (currletter > node->getLetter()) {
					if (node->rightSibling() == NULL) {
						TrieNodeTest<Char>* temp = new TrieNodeTest<Char>(currletter, NULL, node->rightSibling(), node->parent());
						node->setRightSibling(temp);
						nodecount++;
						return insertRestofWord(temp, word, ++i, false);
					}
					else {
						node = node->rightSibling();
					}
				}
				else if (currletter < node->getLetter()) {
					TrieNodeTest<Char>* temp = new TrieNodeTest<Char>(currletter, NULL, node, node->parent());
					if (node->parent()->leftMostChild() == node) {
						node->parent()->setLeftMostChild(temp);
						nodecount++;
						return insertRestofWord(temp, word, ++i, false);
					}
					else {
						TrieNodeTest<Char>* leftchildtraverse = node->parent()->leftMostChild();
						while (leftchildtraverse->rightSibling() != temp->rightSibling()) {
							leftchildtraverse = leftchildtraverse->rightSibling();
						}
						leftchildtraverse->setRightSibling(temp);
						nodecount++;
						return insertRestofWord(temp, word, ++i, false);
						//}
					}
				}
			}
		}

		else {
			for (i; i < word.size(); i++) {
				currletter = word[i];
				TrieNodeTest<Char>* temp = new TrieNodeTest<Char>(currletter, NULL, NULL, node);
				node->setLeftMostChild(temp);
				node = node->leftMostChild();
				nodecount++;
			}
			return node;
		}
	}

	TrieNodeTest<Char>* nodeLetterSearch(TrieNodeTest<Char>* leftStart, char c) {
		TrieNodeTest<Char>* next = leftStart;
		bool match;
		while (next != NULL) {
			match = (next->getLetter() == c);
			if (match) return next;
			next = next->rightSibling();
		}
		return NULL;
	}

public:
	AlphabetTrieTesting() {
		root = new TrieNodeTest<Char>();
		root->setLetter('^');
		root->setLeftMostChild(NULL);
		root->setRightSibling(NULL);
		root->setParent(NULL);
		nodecount = 1;
		wordcount = 0;
	}

	/*AlphabetTrie(GenNode<Char>* lc = NULL) {
		root->setLetter('^');
		root->setLeftMostChild(lc);
		root->setRightSibling(TrieNodeTest<Char> * NULL);
		root->setParent(TrieNodeTest<Char> * NULL);
		nodecount = 1;
		wordcount = 0;
	}*/

	~AlphabetTrieTesting() {
		clear();
	}

	void clear() {
		clearhelp(root);
		root->setLeftMostChild(NULL);
		nodecount = 1;
		wordcount = 0;
	}



	void insertWord(Char word) {
		TrieNodeTest<Char>* node = root;
		TrieNodeTest<Char>* nodeMatch;
		int i;
		
		for (i = 0; i < word.size(); i++) {
			if (node->leftMostChild() == NULL) {
				node = insertRestofWord(node, word, i, false);
				break;
			}
			else {
				node = node->leftMostChild();
				nodeMatch = nodeLetterSearch(node, word[i]);
			}
			if (nodeMatch == NULL) {
				node = insertRestofWord(node, word, i, true);
				break;
			}
		}
		if (node->leftMostChild() == NULL) {
			TrieNodeTest<Char>* endchar = new TrieNodeTest<Char>('$', NULL, node->leftMostChild(), node);
			node->setLeftMostChild(endchar);
			wordcount++;
		}
		else if (node->leftMostChild()->getLetter() == '$') {
			std::cout << "Trie already contains word " << word << std::endl;
			return;
		}
		else {
			TrieNodeTest<Char>* endchar = new TrieNodeTest<Char>('$', NULL, node->leftMostChild(), node);
			node->setLeftMostChild(endchar);
			wordcount++;
		}
		
	}

	bool checkForWord(Char word) {
		TrieNodeTest<Char>* node = root;
		for (int i = 0; i < word.size(); i++) {
			node = node->leftMostChild();
			if (node->getLetter() != word[i]) {
				std::cout << "The word \"" << word << "\" is not in the trie." << std::endl;
				return false;
			}

		}
		if (node->leftMostChild()->getLetter() == '$') {
			std::cout << "The word \"" << word << "\" is in the trie." << std::endl;
			return true;
		}
		else {
			std::cout << "The word \"" << word << "\" is not in the trie." << std::endl;
			return false;
		}
	}

	int getNodeCount() { return nodecount; }
	int getWordCount() { return wordcount; }

	void print() {
		printhelp(root, 0);
	}
};


template <typename Char>
void AlphabetTrieTesting<Char>::clearhelp(TrieNodeTest<Char>* node) {
	if (node == NULL) return;
	clearhelp(node->leftMostChild());
	clearhelp(node->rightSibling());
	delete node;
}

template <typename Char>
void AlphabetTrieTesting<Char>::printhelp(TrieNodeTest<Char>* rt, int level) {
	if (rt == NULL) return;
	printhelp(rt->leftMostChild(), level + 1);
	for (int i = 0; i < level; i++)
		std::cout << "  ";
	std::cout << rt->getLetter() << "\n";
	printhelp(rt->rightSibling(), level);
}