#pragma once 

#include <string>
#include <assert.h>
#include "List.h"

// Dictionary Abstract Class
template <typename Key, typename E> class Dictionary {
private:
	void operator = (const Dictionary&) {} //protect assignment
	Dictionary(const Dictionary&) {} //protect copy

public:
	Dictionary() {}
	~Dictionary() {}

	//reinitialize dictionary
	virtual void clear() = 0;

	//insert a record
	//k: the key for the record being inserted
	//e: the record being inserted
	virtual void insert(const Key& k, const E& e) = 0;

	//remove and return a record
	//k: the key of the record to be removed 
	//return: a matching record. it multiple records match
	//"k", remove an arbitray one. Return NULL if no record
	//with "key "k" esists
	virtual E remove(const Key& k) = 0;

	//remove and return an arbitrary record from dictionary
	//return: the record removed, or NULL if none exists
	virtual E removeAny() = 0;

	//return: a record matching "k"  (NULL if none exists)
	//If multiple records match, return an arbitray one
	//k: the key of the recrod to find
	virtual E find(const Key& k) const = 0;

	//return the number of records in the dictionary
	virtual int size() = 0;
};

/*
//a simple payroll entry with id, name, address fields
class Payroll {
private:
	int ID;
	std::string name;
	std::string address;

public:
	Payroll(int inID, std::string inname, std::string inaddr) {
		ID = inID;
		name = inname;
		address = inaddr;
	}

	~Payroll() {}

	int getID() { return ID; }
	std::string getname() { return name; }
	std::string getaddr() { return address; }
};
*/

//container for a key-value pair
template <typename Key, typename E> class KVpair {
private:
	Key k;
	E e;

public:
	KVpair() {}
	KVpair(Key kval, E eval) {
		k = kval;
		e = eval;
	}

	KVpair(const KVpair& o) //copy constructor
	{
		k = o.k; e = o.e;
	}
	Key key() { return k; }
	void setKey(Key ink) { k = ink; }
	void setValue(E val) { e = val; }
	E value() { return e; }
};

//Dictionary implemented with an unsorted array based list
template <typename Key, typename E>
class UALdict : public Dictionary<Key, E> {
private:
	AList<KVpair<Key, E> >* list;

public:
	UALdict(int size = 20) {
		list = new AList<KVpair<Key, E> >(size);
	}

	~UALdict() { delete list; }
	void clear() { list->clear(); }

	//insert an element: append to list
	void insert(const Key& k, const E& e) {
		KVpair<Key, E> temp(k, e);
		list->append(temp);
	}

	//use sequential search to find the element to remove
	E remove(const Key& k) {
		E temp = find(k);
		if (temp != NULL) list->remove();
		return temp;
	}

	E removeAny() {
		assert(size() != 0, "Dictionary is empty");
		list->moveToEnd();
		list->prev();
		KVpair<Key, E> e = list->remove();
		return e.value();
	}

	E find(const Key& k) const {
		for (list->moveToStart; list->currPos() != list->length(); list->next()) {
			KVpair<Key, E> temp = list->getValue();
			if (k == temp.key()) return temp.value();
		}
		return NULL;
	}

	int size() { return list->length; }
};

//Sorted Array based list
//inherit from Alist as a protected base class
template <typename Key, typename E> class SAList : protected AList<KVpair<Key, E> > {
public:
	SAList(int size = 20) : AList<KVpair<Key, E> >(size) {}
	~SAList() {}

	//redefine insert function to keep values sorted

	void insert(KVpair<Key, E>& it) {
		KVpair<Key, E> curr;
		for (moveToStart(); currPos() < length(); next()) {
			curr = getValue();
			if (curr.key() > it.key())
				break;
		}
		AList<KVpair<Key, E> >::insert(it);
	}

	AList<KVpair<Key, E> > ::clear;
	AList<KVpair<Key, E> > ::remove;
	AList<KVpair<Key, E> > ::moveToStart;
	AList<KVpair<Key, E> > ::moveToEnd;
	AList<KVpair<Key, E> > ::prev;
	AList<KVpair<Key, E> > ::next;
	AList<KVpair<Key, E> > ::length;
	AList<KVpair<Key, E> > ::currPos;
	AList<KVpair<Key, E> > ::moveToPos;
	AList<KVpair<Key, E> > ::getValue;
};

//Dictionary implemented with a sorted array based list
template <typename Key, typename E> class SALdict : public Dictionary<Key, E> {
private:
	SAList<Key, E>* list;

public:
	SALdict(int size = 20) {
		list = new SAList<Key, E>(size);
	}

	~SALdict() { delete list; }
	void clear() { list->clear(); }

	//insert element
	void insert(const Key& k, const E& e) {
		KVpair<Key, E> temp(k, e);
		list->insert(temp);
	}

	//use seequential search to find element to remove
	E remove(const Key& k) {
		E temp = find(k);
		if (temp != NULL) list->remove();
		return temp;
	}

	E removeAny() {
		assert(list->length() != 0, "Dictionary is empty");
		list->moveToEnd();
		list->prev();
		KVpair<Key, E> e = list->remove();
		return e.value();
	}

	//find k using binary search
	E find(const Key& k) const {
		int l = -1;
		int r = list->length();
		while (l + 1 != r) {
			int i = (l + r) / 2;
			list->moveToPos(i);
			KVpair<Key, E> temp = list->getValue();
			if (k < temp.key()) r = i;
			if (k == temp.key()) return temp.value();
			if (k > temp.key()) l = i;
		}
		return NULL;
	}

	int size() { return list->length(); }

	void print() {
		int pos = list->currPos();
		list->moveToStart();
		KVpair<Key, E> temp = list->getValue();
		std::cout << "[" << temp.key() << ":" << temp.value();
		list->next();
		for (int i = 1; i < list->length(); i++) {
			temp = list->getValue();
			std::cout << ", " << temp.key() << ":" << temp.value();
			list->next();
		}
		list->moveToPos(pos);
		std::cout << "]" << std::endl;
	}

	void printkeys() {
		int pos = list->currPos();
		list->moveToStart();
		KVpair<Key, E> temp = list->getValue();
		std::cout << "[" << temp.key();
		list->next();
		for (int i = 1; i < list->length(); i++) {
			temp = list->getValue();
			std::cout << ", " << temp.key();
			list->next();
		}
		list->moveToPos(pos);
		std::cout << "]" << std::endl;
	}
	/*
	void getKeys(AList<Key> keyList) {
		AList<Key> keys(list->length());
		int pos = list->currPos();
		list->moveToStart();
		KVpair<Key, E> temp;
		for (int i = 0; i < list->length(); i++) {
			temp = list->getValue();
			keys.append(temp.key());
			list->next();
		}
		list->moveToPos(pos);
		keyList = keys;
	}
	*/
};