#pragma once

#include <iostream>
#include<cmath>
#include <string>
#include "Dictionary.h"
#include "List.h"

//dictionary implemented with a hash table
template <typename Key, typename E>
class hashDict : public Dictionary<Key, E> {
private:
	KVpair<Key, E>* HT; //the hash table
	int M; //size of HT
	int currcnt; //the current number of elements in HT
	Key EMPTYKEY; //user supplied key value for an empty slot
	Key REMOVEDKEY; //user supplied key value for a removed slot
	int collisioncount;

	int probe(Key K, int i) const { //probe using linear probing 
		return i;
	}

	int hashFunc(int x) const { return x % M; } //poor hash function
	int hashFunc(char* x) const { //hash function for character keys
		int i, sum;
		for (sum = 0, i = 0; x[i] != '\0'; i++) {
			sum += int(x[i]);
		}
		return sum % M;
	}

	int hashFunc(std::string x, int offsetindex=0, int prime1=7, int prime2 = 11) const { //hash function for character keys
		int i, charint;
		int sum;
		int powintreturn;
		for (sum = 0, i = 0; x[i] != '\0'; i++) {
			charint = int(x[i])-65+1; //convert char to ascii value and change range from 65-122 to 1-58
			powintreturn = powint(prime1, i, M);
			sum = (sum + (charint * powintreturn) + offsetindex*(charint * powint(prime2, i, M) ) ) % M;
		}
		return sum ;
	}

	int powint(int x, int power, int M) const {
		int ret = 1;
		for (int i = 0; i < power; i++) {
			ret = (x*ret) % M;
		}
		return ret;
	}

	void hashInsert(const Key&, const E&);
	//void hashInsert(KVpair<Key, E>*, const Key&, const E&);
	E hashSearch(const Key&) const;

	void hashResize(int resizefactor = 2) {
		std::cout << "Resizing hash function by factor of " << resizefactor << std::endl;
		std::cout << "Number of collisions before resizing is : " << collisioncount << std::endl;
		ALenList<KVpair<Key, E> > temp(M);
		for (int i = 0; i < M; i++) {
			if (HT[i].key() != EMPTYKEY && HT[i].key() != REMOVEDKEY) {
				temp.append(HT[i]);
			}
		}
		delete[] HT;
		M *= resizefactor;
		collisioncount = 0;
		KVpair<Key, E>* HT = new KVpair<Key, E>[M];
		this->HT = HT;
		for (int i = 0; i < M; i++) {
			(HT[i]).setKey(EMPTYKEY); //initialize HT
		}
		KVpair<Key, E> tempval;
		for (int i = 0; i < temp.length(); i++) {
			tempval = temp.getValue();
			hashInsert(tempval.key(), tempval.value());
			temp.next();
		}
		
	}

public:
	hashDict(int sz = 16, Key ek = "", Key rk = "\r") { //"k" defines an empty slot
		M = sz;
		EMPTYKEY = ek;
		REMOVEDKEY = rk;
		currcnt = 0;
		HT = new KVpair<Key, E>[sz]; //make hash table of size sz
		for (int i = 0; i < M; i++) {
			(HT[i]).setKey(EMPTYKEY); //initialize HT
		}
	}
	//~hashDict() { delete HT; }

	void clear() {
		for (int i = 0; i < M; i++) {
			(HT[i]).setKey(EMPTYKEY); //initialize HT
		}
	}

	//find some record with key value "k"
	E find(const Key& k) const { return hashSearch(k); }

	//size of dictionary
	int size() { return currcnt; }

	int maxPossibleSize() { return M; }

	//insert element "it" with key "k" into the dictionary
	void insert(const Key& k, const E& it) {
		assert(currcnt < M , "Hash table is full");
		hashInsert(k, it);
		currcnt++;
	}

	E remove(const Key& k) {
		int home; //home position for k
		int pos = home = hashFunc(k); //initial position is home slot
		for (int i = 1; (k != (HT[pos].key()) && (EMPTYKEY != (HT[pos]).key())); i++) {
			pos = (home + probe(k, i)) % M; //next on probe sequence
		}
		if (k == (HT[pos]).key()) {
			E ret = HT[pos].value();
			HT[pos].setKey(REMOVEDKEY);
			HT[pos].setValue(NULL);
			return ret;
		}
		else return NULL; //k not in hash value
		
	}

	E removeAny() {
		E ret;
		for (int pos = 0; pos < M; pos++) {
			if (HT[pos].key() != EMPTYKEY && HT[pos].key() != REMOVEDKEY) {
				ret = HT[pos].value();
				HT[pos].setKey(REMOVEDKEY);
				HT[pos].setValue(NULL);
				return ret;
			}
		}
		return NULL;
	}

	void print() {
		bool first = true;
		for (int pos = 0; pos < M; pos++) {
			if (first == true) {
				if (HT[pos].key() != EMPTYKEY && HT[pos].key() != REMOVEDKEY) {
					std::cout << "[" << HT[pos].key() << ":" << HT[pos].value();
					first = false;
					continue;
				}
			}
			if (HT[pos].key() != EMPTYKEY && HT[pos].key() != REMOVEDKEY) {
				std::cout << ", " << HT[pos].key() << ":" << HT[pos].value();
			}
		}
		std::cout << "]" << std::endl;
	}

	void printHashPos() {
		std::cout << "Hash position printing" << std::endl;
		for (int pos = 0; pos < M; pos++) {
			if (HT[pos].key() != EMPTYKEY && HT[pos].key() != REMOVEDKEY) {
				std::cout << HT[pos].key() << " has position of " << pos << std::endl;
			}
		}
	}

	int getCollisionCount() {
		return collisioncount;
	}
};

//use folding on a string, summed 4 bytes at a time
int sfold(char* key, int M) {
	unsigned int* lkey = (unsigned int*)key;
	int intlength = std::strlen(key) / 4;
	unsigned int sum = 0;
	for (int i = 0; i < intlength; i++)
		sum += lkey[i];
	//now deal with the extra chars at the end
	int extra = strlen(key) - intlength * 4;
	char temp[4];
	lkey = (unsigned int*)temp;
	lkey[0] = 0;
	for (int i = 0; i < extra; i++) {
		temp[i] = key[intlength * 4 + i];
	}
	sum += lkey[0];

	return sum % M;
}

//insert e into hash table HT
template <typename Key, typename E>
void hashDict<Key, E>::hashInsert(const Key& k, const E& e) {
	int home; //home position for e
	if (currcnt >= M*1/2 ) {
		hashResize(2);
	}
	int pos = home = hashFunc(k); //init probe sequence
	for (int i = 1; (HT[pos].key() != REMOVEDKEY && HT[pos].key() != EMPTYKEY); i++) {
		collisioncount++;
		pos = (hashFunc(k, i)); //probe
		assert(k != (HT[pos]).key(), "Duplicates not allowed");
	}
	KVpair<Key, E> temp(k, e);
	HT[pos] = temp;
}

//template <typename Key, typename E>
//void hashDict<Key, E>::hashInsert(KVpair<Key, E>* hashtable, const Key& k, const E& e) {
//	int home; //home position for e
//	int pos = home = hashFunc(k); //init probe sequence
//	for (int i = 1; (hashtable[pos].key() != REMOVEDKEY && hashtable[pos].key() != EMPTYKEY); i++) {
//		collisioncount++;
//		pos = (hashFunc(k, i)); //probe
//		assert(k != (hashtable[pos]).key(), "Duplicates not allowed");
//	}
//	KVpair<Key, E> temp(k, e);
//	hashtable[pos] = temp;
//}

//search for the record with key k
template <typename Key, typename E>
E hashDict<Key, E>::hashSearch(const Key& k) const {
	int home; //home position for k
	int pos = home = hashFunc(k); //initial position is home slot
	for (int i = 1; (k != (HT[pos].key()) && (EMPTYKEY != (HT[pos]).key())); i++) {
		pos = hashFunc(k, i); //next on probe sequence
	}
	if (k == (HT[pos]).key())
		return (HT[pos]).value();
	else return NULL; //k not in hash value
}

