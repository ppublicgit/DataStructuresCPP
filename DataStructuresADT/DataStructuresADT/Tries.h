#pragma once
#include <iostream>
#include <ctype.h>
#include <assert.h>
// simple General Tree Node Implem1entation
template <typename Char> class TrieNode {
private:
	char letter;
	TrieNode<Char>* lc;
	TrieNode<Char>* rs;
	TrieNode<Char>* pt;


public:
	//two constructors -- with and without initial values
	TrieNode() { letter = NULL;  lc = rs = pt = NULL; }
	TrieNode(char c, TrieNode<Char>* l = NULL, TrieNode<Char>* r = NULL, TrieNode<Char>* p = NULL)
	{
		letter = c; lc = l; rs = r; pt = p;
	}

	~TrieNode() {}

	//functions to set and return value and key
	char getLetter() { return letter; }
	void setLetter(char c) { letter = c; }

	//functions to set and return the children
	TrieNode<Char>* leftMostChild() { return lc; }
	TrieNode<Char>* rightSibling() { return rs; }
	TrieNode<Char>* parent() { return pt; }
	void setLeftMostChild(TrieNode<Char>* b) { lc = (TrieNode<Char>*)b; }// lc->setParent(this);
	void setRightSibling(TrieNode<Char>* b) { rs = (TrieNode<Char>*)b; }// rs->setParent(parent());
	void setParent(TrieNode<Char>* b) { pt = (TrieNode<Char>*)b; }

	//return true if it is a leaf, false otherwise
	bool isLeaf() {
		return (lc == NULL);
	}
};

template <typename Char> class AlphabetTrie {
private:
	TrieNode<Char>* root; //root of the BST
	int nodecount; //number of nodes in bst
	int wordcount;
	//Private helper functions
	void clearhelp(TrieNode<Char>* node);
	void removehelp(TrieNode<Char>*, Char, int);
	void printhelp(TrieNode<Char>*, int, TrieNode<Char>*);

	TrieNode<Char>* leftSibling(TrieNode<Char>* node) {
		TrieNode<Char>* leftsiblingtraverse = node->parent()->leftMostChild();
		if (leftsiblingtraverse == node) {
			return NULL;
		}
		while (leftsiblingtraverse->rightSibling() != node) {
			leftsiblingtraverse= leftsiblingtraverse->rightSibling();
		}
		return leftsiblingtraverse;
	}

	TrieNode<Char>* insertRestofWord(TrieNode<Char>* node, Char word, int i, bool siblingtraverse) {
		char currletter;
		if (siblingtraverse) {
			while (node != NULL) {
				currletter = word[i];
				if (currletter > node->getLetter()) {
					if (node->rightSibling() == NULL) {
						TrieNode<Char>* temp = new TrieNode<Char>(currletter, NULL, node->rightSibling(), node->parent());
						node->setRightSibling(temp);
						nodecount++;
						return insertRestofWord(temp, word, ++i, false);
					}
					else {
						node = node->rightSibling();
					}
				}
				else if (currletter < node->getLetter()) {
					TrieNode<Char>* temp = new TrieNode<Char>(currletter, NULL, node, node->parent());
					if (node->parent()->leftMostChild() == node) {
						node->parent()->setLeftMostChild(temp);
						nodecount++;
						return insertRestofWord(temp, word, ++i, false);
					}
					else {
						TrieNode<Char>* leftchildtraverse = node->parent()->leftMostChild();
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
				TrieNode<Char>* temp = new TrieNode<Char>(currletter, NULL, NULL, node);
				node->setLeftMostChild(temp);
				node = node->leftMostChild();
				nodecount++;
			}
			return node;
		}
	}

	TrieNode<Char>* nodeLetterSearch(TrieNode<Char>* leftStart, char c) {
		TrieNode<Char>* next = leftStart;
		bool match;
		while (next != NULL) {
			match = (next->getLetter() == c);
			if (match) return next;
			next = next->rightSibling();
		}
		return NULL;
	}

	bool checkIfAlphabetWord(Char word) {
		bool ret = true;
		for (int i = 0; i < word.size(); i++) {
			if (!isalpha(word[i])) {
				ret = false;
				break;
			}
		}
		return ret;
	}

public:
	AlphabetTrie() {
		root = new TrieNode<Char>();
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
		root->setRightSibling(TrieNode<Char> * NULL);
		root->setParent(TrieNode<Char> * NULL);
		nodecount = 1;
		wordcount = 0;
	}*/

	~AlphabetTrie() {
		clear();
		delete root;
	}

	void clear() {
		if (root->leftMostChild() != NULL) {
			clearhelp(root->leftMostChild());
			nodecount = 1;
			wordcount = 0;
		}
	}



	bool insertWord(Char word, bool verbose=true) {
		if (!checkIfAlphabetWord(word)) {
			if (verbose)
			std::cout << "The word " << word << 
				"is not a recognized english dictionary word (contains non-letter characters)" << std::endl;
			return false;
		}
		TrieNode<Char>* node = root;
		TrieNode<Char>* nodeMatch;
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
			else { node = nodeMatch; }
		}
		if (node->leftMostChild() == NULL) {
			TrieNode<Char>* endchar = new TrieNode<Char>('$', NULL, node->leftMostChild(), node);
			node->setLeftMostChild(endchar);
			wordcount++;
			nodecount++;
		}
		else if (node->leftMostChild()->getLetter() == '$') {
			if (verbose)
			std::cout << "Trie already contains word " << word << std::endl;
			return false;
		}
		else {
			TrieNode<Char>* endchar = new TrieNode<Char>('$', NULL, node->leftMostChild(), node);
			node->setLeftMostChild(endchar);
			wordcount++;
			nodecount++;
		}
		return true;
	}

	bool checkForWord(Char word, bool verbose=true) {
		TrieNode<Char>* node = root;
		for (int i = 0; i < word.size(); i++) {
			node = node->leftMostChild();
			node = nodeLetterSearch(node, word[i]);
			if (node == NULL) {
				if (verbose)
				std::cout << "The word \"" << word << "\" is not in the trie." << std::endl;
				return false;
			}

		}
		if (node->leftMostChild()->getLetter() == '$') {
			if (verbose)
			std::cout << "The word \"" << word << "\" is in the trie." << std::endl;
			return true;
		}
		else {
			if (verbose)
			std::cout << "The word \"" << word << "\" is not in the trie." << std::endl;
			return false;
		}
	}

	int getNodeCount() { return nodecount; }
	int getWordCount() { return wordcount; }

	Char remove(Char word, bool verbose=true) {
		if (checkForWord(word, verbose)) {
			removehelp(root->leftMostChild(), word, 0);
			wordcount--;
			return word;
		}
		else {
			Char retword = "failed";
			return retword;
		}
	}

	void print() {
		if (nodecount == 1 || wordcount == 0) {
			std::cout << "Trie is empty" << std::endl;
			return;
		}
		printhelp(root->leftMostChild(), 0, root);
		std::cout << std::endl;
	}
};

template <typename Char>
void AlphabetTrie<Char>::removehelp(TrieNode<Char>* node, Char word, int level) {
	if (node->getLetter() == '$' && word.size() == level) {
		if (node->rightSibling() == NULL) {
			node->parent()->setLeftMostChild(NULL);
			delete node;
			node = NULL;
			nodecount--;
		}
		else {
			node->parent()->setLeftMostChild(node->rightSibling());
			delete node;
			node = NULL;
			nodecount--;
		}
		return;
	}
	node = nodeLetterSearch(node, word[level]);
	removehelp(node->leftMostChild(), word, level + 1);
	if (node->leftMostChild() == NULL && node->parent()->leftMostChild() == node) {
		if (node->rightSibling() == NULL) {
			node->parent()->setLeftMostChild(NULL);
		}
		else {
			node->parent()->setLeftMostChild(node->rightSibling());
		}
		delete node;
		node = NULL;
		nodecount--;
	}
	/*else if (node->leftMostChild() == NULL && node->rightSibling() == NULL) {
		delete node;
		node = NULL;
		nodecount--;
	}*/
	else if (node->leftMostChild() == NULL) {
		TrieNode<Char>* leftsib = leftSibling(node);
		leftsib->setRightSibling(node->rightSibling());
		delete node;
		node = NULL;
		nodecount--;
	}
}

template <typename Char>
void AlphabetTrie<Char>::clearhelp(TrieNode<Char>* node) {
	if (node == NULL) return;
	clearhelp(node->leftMostChild());
	clearhelp(node->rightSibling());
	node->parent()->setLeftMostChild(NULL);
	delete node;
	node = NULL;
	//nodecount--;
}

template <typename Char>
void AlphabetTrie<Char>::printhelp(TrieNode<Char>* rt, int level, TrieNode<Char>* rtprt) {
	if (rt == NULL) return;
	if (rtprt == rt->parent()) {
		for (int i = 0; i < level; i++)
			std::cout << " ";
	}
	
	if (rt->getLetter() == '$') { 
		std::cout << "\n";
		//for (int i = 0; i < level; i++)
		//	std::cout << " ";
	}
	else {
		std::cout << rt->getLetter();// << "\n";
	}
	printhelp(rt->leftMostChild(), level + 1, NULL);
	printhelp(rt->rightSibling(), level, rt->parent());
}