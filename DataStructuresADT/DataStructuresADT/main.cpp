#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctype.h>

#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "Dictionary.h"
#include "BinaryTrees.h"
#include "HashDictionary.h"
#include "Tries.h"

using namespace std;

int main() {
	
	std::cout << endl;
	std::cout << "=========== LIST TESTING ===========" << endl;
#pragma region List Testing
	std::cout << "------- array list testing -------" << endl;
	AList<double> alist;
	alist.append(10);
	alist.append(12);
	alist.append(14);
	alist.append(15);
	alist.append(19);
	alist.append(21);
	alist.append(23);
	alist.print();
	std::cout << "curr pos : " << alist.currPos() << endl;
	alist.moveToPos(2);
	std::cout << "removing element at curr pos " << alist.currPos() << " with value of " << alist.remove() << endl;
	alist.print();
	alist.moveToPos(2);
	std::cout << "curr pos : " << alist.currPos() << endl;
	alist.insert(13);
	alist.print();

	std::cout << endl;

	std::cout << "------- single linked list testing -------" << endl;
	LList<string> slist;
	slist.append("cat");
	slist.append("dog");
	slist.append("fish");
	slist.append("mouse");
	slist.append("horse");
	slist.append("elephant");
	slist.append("giraffe");
	slist.print();
	std::cout << "curr pos : " << slist.currPos() << endl;
	std::cout << "removing element at curr pos " << slist.currPos() << " with value of " << slist.remove() << endl;
	slist.print();
	slist.moveToPos(2);
	std::cout << "curr pos : " << slist.currPos() << endl;
	slist.insert("zebra");
	slist.print();
	std::cout << "curr pos : " << slist.currPos() << endl;

	std::cout << endl;

	std::cout << "------- double linked list testing -------" << endl;
	DLList<string> dllist;
	dllist.append("cat");
	dllist.append("dog");
	dllist.append("fish");
	dllist.append("mouse");
	dllist.append("horse");
	dllist.append("elephant");
	dllist.append("giraffe");
	dllist.print();
	std::cout << "curr pos : " << dllist.currPos() << endl;
	dllist.moveToPos(4);
	std::cout << "removing element at curr pos " << dllist.currPos() << " with value of " << dllist.remove() << endl;
	dllist.print();
	dllist.moveToPos(2);
	std::cout << "curr pos : " << dllist.currPos() << endl;
	dllist.insert("zebra");
	dllist.print();
	std::cout << "curr pos : " << dllist.currPos() << endl;

	std::cout << endl;

	std::cout << "------- adaptive array list length testing -------" << endl;
	ALenList<string> alenlist(8);
	std::cout << "max size is : " << alenlist.getMaxSize() << endl;
	alenlist.append("cat");
	alenlist.append("dog");
	alenlist.append("fish");
	alenlist.append("mouse");
	std::cout << "max size is : " << alenlist.getMaxSize() << endl;
	alenlist.append("horse");
	alenlist.append("elephant");
	alenlist.append("giraffe");
	std::cout << "max size is : " << alenlist.getMaxSize() << endl;
	alenlist.append("spider");
	alenlist.append("frog");
	alenlist.print();
	std::cout << "curr pos : " << alenlist.currPos() << endl;
	alenlist.moveToPos(4);
	std::cout << "removing element at curr pos " << alenlist.currPos() << " with value of " << alenlist.remove() << endl;
	alenlist.print();
	alenlist.moveToPos(2);
	std::cout << "curr pos : " << alenlist.currPos() << endl;
	alenlist.insert("zebra");
	alenlist.print();
	std::cout << "max size is : " << alenlist.getMaxSize() << endl;
	std::cout << "current length : " << alenlist.length() << endl;
	alenlist.moveToEnd();
	alenlist.prev();
	std::cout << "current position : " << alenlist.currPos() << endl;
	string _  = alenlist.remove();
	_ = alenlist.remove();
	_ = alenlist.remove();
	_ = alenlist.remove();
	_ = alenlist.remove();
	std::cout << "current length : " << alenlist.length() << endl;
	std::cout << "max size is : " << alenlist.getMaxSize() << endl;
	std::cout << "curr pos : " << alenlist.currPos() << endl;
	alenlist.insert("salamander");
	alenlist.print();

	std::cout << endl;

#pragma endregion List Testing
	
	std::cout << endl;
	std::cout << "=========== STACK TESTING ===========" << endl;
#pragma region Stack Testing
	std::cout << endl;

	std::cout << "------- Stack array testing -------" << endl;
	AStack<double> astack;
	astack.push(10);
	astack.push(12);
	astack.push(14);
	astack.push(15);
	astack.push(19);
	astack.push(21);
	astack.push(23);
	astack.print();
	std::cout << "length of stack : " << astack.length() << endl;
	std::cout << "Pop top : " << astack.pop() << endl;
	std::cout << "length of stack : " << astack.length() << endl;
	astack.print();
	std::cout << "Top value : " << astack.topValue() << endl;

	std::cout << endl;

	std::cout << "------- Stack linked list testing -------" << endl;
	LStack<double> lstack;
	lstack.push(10);
	lstack.push(12);
	lstack.push(14);
	lstack.push(15);
	lstack.push(19);
	lstack.push(21);
	lstack.push(23);
	lstack.print();
	std::cout << "length of stack : " << lstack.length() << endl;
	std::cout << "Pop top : " << lstack.pop() << endl;
	std::cout << "length of stack : " << lstack.length() << endl;
	lstack.print();
	std::cout << "Top value : " << lstack.topValue() << endl;
	lstack.push(25);
	lstack.print();

	std::cout << endl;

#pragma endregion Stack Testing

	std::cout << endl;
	std::cout << "=========== QUEUE TESTING ===========" << endl;
#pragma region Queue Testing
	std::cout << endl;

	std::cout << "------- Queue array testing -------" << endl;
	AQueue<double> aqueue(7);
	aqueue.enqueue(10);
	aqueue.enqueue(12);
	aqueue.enqueue(14);
	aqueue.enqueue(15);
	aqueue.enqueue(19);
	aqueue.enqueue(21);
	aqueue.enqueue(23);
	aqueue.print();
	std::cout << "length of queue : " << aqueue.length() << endl;
	std::cout << "Dequeue front : " << aqueue.dequeue() << endl;
	std::cout << "length of queue : " << aqueue.length() << endl;
	aqueue.print();
	std::cout << "Front value : " << aqueue.frontValue() << endl;	
	aqueue.dequeue();
	aqueue.dequeue();
	aqueue.enqueue(10);
	aqueue.enqueue(12);
	aqueue.enqueue(14);
	aqueue.print();

	std::cout << endl;

	std::cout << "------- Queue linked list testing -------" << endl;
	LQueue<double> lqueue;
	lqueue.enqueue(10);
	lqueue.enqueue(12);
	lqueue.enqueue(14);
	lqueue.enqueue(15);
	lqueue.enqueue(19);
	lqueue.enqueue(21);
	lqueue.enqueue(23);
	lqueue.print();
	std::cout << "length of queue : " << lqueue.length() << endl;
	std::cout << "Dequeue front : " << lqueue.dequeue() << endl;
	std::cout << "length of queue : " << lqueue.length() << endl;
	lqueue.print();
	std::cout << "Front value : " << lqueue.frontValue() << endl;	
	lqueue.dequeue();
	lqueue.dequeue();
	lqueue.enqueue(10);
	lqueue.enqueue(12);
	lqueue.enqueue(14);
	lqueue.print();

	std::cout << endl;

	std::cout << "-------Double Ended Queue linked list testing -------" << endl;
	LDequeue<double> dequeue;
	dequeue.enqueue(10);
	dequeue.enqueueFront(12);
	dequeue.enqueueRear(14);
	dequeue.enqueue(15);
	dequeue.enqueueFront(19);
	dequeue.enqueueRear(21);
	dequeue.enqueue(23);
	dequeue.print();
	std::cout << "length of queue : " << dequeue.length() << endl;
	std::cout << "Dequeue : " << dequeue.dequeue() << endl;
	std::cout << "Dequeue Rear : " << dequeue.dequeueRear() << endl;
	std::cout << "Dequeue front : " << dequeue.dequeueFront() << endl;
	std::cout << "length of queue : " << dequeue.length() << endl;
	dequeue.print();
	std::cout << "Front value : " << dequeue.frontValue() << endl;
	std::cout << "Rear value : " << dequeue.rearValue() << endl;
	dequeue.dequeueFront();
	dequeue.dequeueRear();
	dequeue.enqueueRear(10);
	dequeue.enqueueFront(12);
	dequeue.enqueueFront(13);
	dequeue.print();

	std::cout << endl;

#pragma endregion Queue Testing

	std::cout << endl;
	std::cout << "==== NON-HASH DICTIONARY TESTING ====" << endl;
#pragma region Non-Hash Dictioary Testing
	std::cout << endl;

	std::cout << "------- Dictionary Sorted Array Testing -------" << endl;
	SALdict<string, double> saldict(7);
	saldict.insert("Cat", 4);
	saldict.insert("Spider", 8);
	saldict.print();
	saldict.printkeys();
	std::cout << "length of dictionary : " << saldict.size() << endl;
	std::cout << "Remove Key 'Cat' with value of " << saldict.remove("Cat") << endl;
	std::cout << "length of dictionary : " << saldict.size() << endl;
	saldict.print();
	std::cout << "Value for 'Spider' is " << saldict.find("Spider") << endl;

	std::cout << endl;
#pragma endregion Non-Hash Dictionary Testing

	std::cout << endl;
	std::cout << "======== BINARY TREE TESTING ========" << endl;
#pragma region Binary Trees Testing
	std::cout << endl;

	std::cout << "------- Binary Search Tree for Dictionary Testing -------" << endl;
	BST<string, double> bst;
	bst.insert("Cat", 4);
	bst.insert("Spider", 8);
	bst.insert("Dog", 4);
	bst.insert("Centipede", 100);
	bst.insert("Millipede", 1000);
	bst.insert("Ostrich", 2);
	bst.insert("Shark", 0);
	bst.print();
	std::cout << "length of binary search tree : " << bst.size() << endl;
	std::cout << "Remove Key 'Cat' with value of " << bst.remove("Cat") << endl;
	std::cout << "length of binary search tree : " << bst.size() << endl;
	bst.print();
	std::cout << "Value for 'Spider' is " << bst.find("Spider") << endl;

	std::cout << endl;
	
	std::cout << "------- Min heap Testing -------" << endl;
	int maxsize = 100;
	heapMinTree<int> heapmin(maxsize);
	heapmin.insert(1);
	heapmin.insert(8);
	heapmin.insert(4);
	heapmin.insert(100);
	heapmin.insert(1000);
	heapmin.print();
	std::cout << "new insert" << endl;
	std::cout << "length of minheap : " << heapmin.size() << endl;
	std::cout << "Remove first from heap :  " << heapmin.removeFirst() << endl;
	std::cout << "length of min heap : " << heapmin.size() << endl;
	heapmin.print();
	heapmin.insert(2);
	heapmin.insert(0);
	heapmin.print();

	std::cout << endl;
	
	std::cout << "------- Max heap Testing -------" << endl;
	heapMaxTree<int> heapmax(maxsize);
	heapmax.insert(1);
	heapmax.insert(8);
	heapmax.insert(4);
	heapmax.insert(100);
	heapmax.insert(1000);
	heapmax.print();
	std::cout << "length of max heap : " << heapmax.size() << endl;
	std::cout << "Remove first from heap :  " << heapmax.removeFirst() << endl;
	std::cout << "length of max heap : " << heapmax.size() << endl;
	heapmax.print();
	heapmax.insert(2);
	heapmax.insert(0);
	heapmax.print();

	std::cout << endl;
	
#pragma endregion Binary Trees Testing

	std::cout << endl;
	std::cout << "============ HASH TESTING ===========" << endl;
#pragma region Hash Testing
	std::cout << endl;

	std::cout << "------- Hash Dictionary Testing -------" << endl;
	hashDict<string, double> hdict(1000);
	hdict.insert("Cat", 4);
	hdict.insert("Spider", 8);
	hdict.insert("Dog", 4);
	hdict.insert("Centipede", 100);
	hdict.insert("Millipede", 1000);
	hdict.insert("Ostrich", 2);
	hdict.insert("Shark", 0);
	hdict.print();
	hdict.printHashPos();
	std::cout << "length of hash dictionary : " << hdict.size() << endl;
	std::cout << "Remove Key 'Cat' with value of " << hdict.remove("Cat") << endl;
	std::cout << "length of hash dictionary : " << hdict.size() << endl;
	hdict.print();
	std::cout << "Value for 'Spider' is " << hdict.find("Spider") << endl;
	hdict.printHashPos();
	hdict.insert("Human", 2);
	hdict.insert("Cat", 4);
	hdict.printHashPos();
	std::cout << endl;

	hashDict<string, double> hdictcollisions(497087);
	ALenList<string> wordlist;
	ifstream hdictfile("words.txt");
	string eachline;
	int linecount = 0;
	bool skip;
	while (getline(hdictfile, eachline) ) {
		linecount++;
		skip = false;
		for (int i = 0; i < eachline.size(); i++) {
			if (!isalpha(eachline[i])) {
				skip = true;
			}
		}
		if (skip) { continue;  }
		else {
			hdictcollisions.insert(eachline, 1);
			wordlist.append(eachline);
		}		
	}
	std::cout << "Size of hash dictionary : " << hdictcollisions.maxPossibleSize() << endl;
	std::cout << "Number of keys in hash dictionary : " << hdictcollisions.size() << endl;
	std::cout << "number of collisions : " << hdictcollisions.getCollisionCount() << endl;
	//hdictcollisions.printHashPos();
	std::cout << endl;

#pragma endregion Hash Testing

	std::cout << endl;
	std::cout << "============ SORTING TESTING ===========" << endl;

#pragma region Sorting Testing
	std::cout << endl;

	std::cout << "------- Insertion Sort Array Testing -------" << endl;
	alist.clear();
	alist.append(1);
	alist.append(5);
	alist.append(3);
	alist.append(0);
	alist.append(2);
	alist.append(1);
	alist.append(8);
	alist.append(9);
	alist.print();
	std::cout << "sorting array list by greater than" << endl;
	alist.insertionSort();
	alist.print();
	std::cout << "sorting array list by lesser than" << endl;
	alist.insertionSort(false);
	alist.print();
	std::cout << endl;

	std::cout << endl;

	std::cout << "------- Bubble Sort Array Testing -------" << endl;
	alist.clear();
	alist.append(1);
	alist.append(5);
	alist.append(3);
	alist.append(0);
	alist.append(2);
	alist.append(1);
	alist.append(8);
	alist.append(9);
	alist.print();
	std::cout << "sorting array list by greater than" << endl;
	alist.bubbleSort();
	alist.print();
	std::cout << "sorting array list by lesser than" << endl;
	alist.bubbleSort(false);
	alist.print();
	std::cout << endl;

	std::cout << endl;

	std::cout << "------- Selection Sort Array Testing -------" << endl;
	alenlist.clear();
	alenlist.append("cat");
	alenlist.append("dog");
	alenlist.append("fish");
	alenlist.append("ape");
	alenlist.append("gorilla");
	alenlist.append("ape");
	alenlist.append("human");
	alenlist.append("caterpillar");
	alenlist.print();
	std::cout << "sorting array list by greater than" << endl;
	alenlist.selsort();
	alenlist.print();
	std::cout << "sorting array list by lesser than" << endl;
	alenlist.selsort(false);
	alenlist.print();
	std::cout << endl;

	std::cout << endl;

	std::cout << "------- Selection Sort Array Testing -------" << endl;
	dllist.clear();
	dllist.append("cat");
	dllist.append("dog");
	dllist.append("fish");
	dllist.append("ape");
	dllist.append("gorilla");
	dllist.append("ape");
	dllist.append("human");
	dllist.append("caterpillar");
	dllist.print();
	std::cout << "sorting array list by greater than" << endl;
	dllist.insertionSort();
	dllist.print();
	std::cout << "sorting array list by lesser than" << endl;
	dllist.insertionSort(false);
	dllist.print();
	std::cout << endl;

	std::cout << endl;

	std::cout << "------- Shell Sort Array Testing -------" << endl;
	alenlist.clear();
	alenlist.append("cat");
	alenlist.append("dog");
	alenlist.append("fish");
	alenlist.append("ape");
	alenlist.append("gorilla");
	alenlist.append("ape");
	alenlist.append("human");
	alenlist.append("caterpillar");
	alenlist.append("millipede");
	alenlist.append("dinosaur");
	alenlist.append("elephant");
	alenlist.append("spider");
	alenlist.append("frog");
	alenlist.append("babboon");
	alenlist.append("chimpanzee");
	alenlist.append("whale");
	alenlist.append("shark");
	alenlist.print();
	std::cout << "sorting array list by greater than" << endl;
	alenlist.shellSort(true, alenlist.length(), true);
	alenlist.print();
	std::cout << "sorting array list by lesser than" << endl;
	alenlist.shellSort(false, alenlist.length(), true);
	alenlist.print();
	std::cout << endl;

	std::cout << endl;

	std::cout << "------- Merge Sort Array Testing -------" << endl;
	alenlist.clear();
	alenlist.append("cat");
	alenlist.append("dog");
	alenlist.append("fish");
	alenlist.append("ape");
	alenlist.append("gorilla");
	alenlist.append("ape");
	alenlist.append("human");
	alenlist.append("millipede");
	alenlist.append("caterpillar");
	alenlist.append("elephant");
	alenlist.append("dinosaur");
	alenlist.append("spider");
	alenlist.append("frog");
	alenlist.append("babboon");
	alenlist.append("chimpanzee");
	alenlist.append("whale");
	alenlist.append("shark");
	alenlist.print();
	std::cout << "sorting array list by greater than" << endl;
	alenlist.mergeSort();
	alenlist.print();
	std::cout << "sorting array list by lesser than" << endl;
	alenlist.mergeSort(false);
	alenlist.print();
	std::cout << endl;

	std::cout << endl;

	std::cout << "------- Quick Sort Array Testing -------" << endl;
	alenlist.clear();
	alenlist.append("cat");
	alenlist.append("dog");
	alenlist.append("fish");
	alenlist.append("ape");
	alenlist.append("gorilla");
	alenlist.append("ape");
	alenlist.append("human");
	alenlist.append("millipede");
	alenlist.append("caterpillar");
	alenlist.append("elephant");
	alenlist.append("dinosaur");
	alenlist.append("spider");
	alenlist.append("frog");
	alenlist.append("babboon");
	alenlist.append("chimpanzee");
	alenlist.append("whale");
	alenlist.append("shark");
	alenlist.print();
	std::cout << "sorting array list by greater than" << endl;
	alenlist.quickSort();
	alenlist.print();
	std::cout << "sorting array list by lesser than" << endl;
	alenlist.quickSort(false);
	alenlist.print();
	std::cout << endl;
#pragma endregion Sorting Testing


	std::cout << endl;
	std::cout << "============ TRIES TESTING ===========" << endl;

#pragma region Trie Testing
	std::cout << endl;

	std::cout << "------- Alphabet Trie Testing -------" << endl;
	
	AlphabetTrie<string> alphatrie;
	alphatrie.insertWord("cat");
	alphatrie.insertWord("dog");
	alphatrie.insertWord("fish");
	alphatrie.insertWord("ape");
	alphatrie.insertWord("gorilla");
	alphatrie.insertWord("ape");
	alphatrie.insertWord("human");
	alphatrie.insertWord("millipede");
	alphatrie.insertWord("caterpillar");
	alphatrie.insertWord("elephant");
	alphatrie.insertWord("dinosaur");
	alphatrie.insertWord("spider");
	alphatrie.insertWord("spia23");
	alphatrie.print();
	alphatrie.checkForWord("dinosaur");
	alphatrie.checkForWord("cat");
	alphatrie.checkForWord("cate");
	alphatrie.checkForWord("ca");
	std::cout << "current trie has " << alphatrie.getWordCount() << " words" << endl;
	std::cout << "current trie has " << alphatrie.getNodeCount() << " nodes" << endl;

	std::cout << "Removing word cat... " << alphatrie.remove("cat") << " removed." << endl;
	std::cout << "current trie has " << alphatrie.getWordCount() << " words" << endl;
	std::cout << "current trie has " << alphatrie.getNodeCount() << " nodes" << endl;
	alphatrie.print();
	std::cout << "Removing word caterpillar... " << alphatrie.remove("caterpillar") << " removed." << endl;
	std::cout << "current trie has " << alphatrie.getWordCount() << " words" << endl;
	std::cout << "current trie has " << alphatrie.getNodeCount() << " nodes" << endl;
	alphatrie.print();
	std::cout << "Removing word dinosaur... " << alphatrie.remove("dinosaur") << " removed." << endl;
	std::cout << "current trie has " << alphatrie.getWordCount() << " words" << endl;
	std::cout << "current trie has " << alphatrie.getNodeCount() << " nodes" << endl;
	alphatrie.print();


	alphatrie.clear();
	alphatrie.print();
	std::cout << "current trie has " << alphatrie.getWordCount() << " words" << endl;
	std::cout << "current trie has " << alphatrie.getNodeCount() << " nodes" << endl;
	auto start = std::chrono::high_resolution_clock::now();
	ifstream file("words.txt");
	string line;
	ALenList<string> vec;
	int counter = 0;
	while (getline(file, line) && counter < 20000) {
		if (counter % 1 == 0) {
			if (alphatrie.insertWord(line, false)) { vec.append(line); }
		}
		counter++;
	}
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s" << endl;
	std::cout << "current trie has " << alphatrie.getWordCount() << " words" << endl;
	std::cout << "current trie has " << alphatrie.getNodeCount() << " nodes" << endl;
	std::cout << "adaptive length list has " << vec.length() << " words" << endl;
	vec.moveToEnd();
	vec.prev();
	string word;
	int totalLength = vec.length();
	for (int i = 0; i < totalLength; i++) {
		word = vec.remove();
		alphatrie.remove(word, false);
	}
	auto finish2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed2 = finish2 - start;
	std::cout << "Elapsed time: " << elapsed2.count() << " s" << endl;
	std::cout << "current trie has " << alphatrie.getWordCount() << " words" << endl;
	std::cout << "current trie has " << alphatrie.getNodeCount() << " nodes" << endl;
	alphatrie.print();
	std::cout << endl;
#pragma endregion Trie Testing
	return 0;
}