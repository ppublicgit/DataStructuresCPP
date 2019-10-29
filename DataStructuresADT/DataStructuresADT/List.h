#pragma once
#include <iostream>
#include <assert.h>

template <typename E> class List { //list ADT
private:
	//void operator =(const List&) {} //Protect Assignment
	//List(const List&) {} //Protect copy constructor
public:
	List() {} //Default constructor
	virtual ~List() {} //base destructor
	//clear contents from list to make it empty
	virtual void clear() = 0;
	//insert an element at the current location
	//item: the element to be insterted
	virtual void append(const E& item) = 0;
	// Remove and return the current element
	// retrun: the element that was removed
	virtual E remove() = 0;
	//set the current position to the start of list
	virtual void moveToStart() = 0;
	//set the current position to the end of list
	virtual void moveToEnd() = 0;
	//move the current position one step left, No change
	//if already at beginning
	virtual void prev() = 0;
	//move the current position one step right. no change
	//if already at end
	virtual void next() = 0;
	//return:the number of elements in the list
	virtual int length() const = 0;
	//return : the position of the current element
	virtual int currPos() const = 0;
	//set current position
	//pos: the position to make current
	virtual void moveToPos(int pos) = 0;
	//return: the current element
	virtual const E& getValue() const = 0;
};

template <typename E> //array based list implementation
class AList : public List<E> {
private:
	int maxSize; //max size of list
	int listSize; //number of list items now
	int curr; //position of current element
	E* listArray; //array holding list elements
	void swap(int i, int j) {
		E temp = listArray[j];
		listArray[j] = listArray[i];
		listArray[i] = temp;
	}

	bool greaterthan(E lhs, E rhs) {
		return lhs > rhs;
	}

	bool lesserthan(E lhs, E rhs) {
		return lhs < rhs;
	}

public:
	AList(int size = 100) { //constructor
		maxSize = size;
		listSize = curr = 0;
		listArray = new E[maxSize];
	}

	~AList() { delete[] listArray; } //destructor

	AList(const AList& rhs) {
		std::cout << "copy constructor called" << std::endl;
		for (int i = 0; i < rhs.length(); i++) {
			listArray[i] = rhs.listArray[i];
		}
	}

	AList& operator =(const AList& rhs) {
		std::cout << "assignment called" << std::endl;
		/*for (int i = 0; i < rhs.length(); i++) {
			listArray[i] = rhs.listArray[i];
		}
		*/
		return *this;
	}

	void clear() { //reinitialize the list
		delete[] listArray; //remove the array
		listSize = curr = 0; //reset the size
		listArray = new E[maxSize]; //recreate the array
	}

	//insert "it" at current position
	void insert(const E& it) {
		assert(listSize < maxSize, "List capacity exceeded");
		for (int i = listSize; i > curr; i--) { //shift elements up
			listArray[i] = listArray[i-1];			// to make room
		}
		listArray[curr] = it;
		listSize++; //increment list size
	}

	void append(const E& it) { //append "it"
		assert(listSize < maxSize, "List capacity exceeded");
		listArray[listSize++] = it;
	}

	//remove and return the current element
	E remove() {
		assert((curr >= 0) && (curr < listSize), "No Element");
		E it = listArray[curr]; //copy the element
		for (int i = curr; i < listSize - 1; i++) //shift them down
			listArray[i] = listArray[i + 1];
		listSize--; //decrement list size
		return it;
	}

	void moveToStart() { curr = 0; } //reset position
	void moveToEnd() { curr = listSize; } //set at end
	void prev() { if (curr != 0) curr--; } //back up
	void next() { if (curr < listSize) curr++; } //next

	//return list size
	int length() const { return listSize; }

	//return current position
	int currPos() const { return curr; }

	//set current list position to "pos"
	void moveToPos(int pos) {
		assert((pos >= 0) && (pos < listSize), "Position out of range");
		curr = pos;
	}

	const E& getValue() const { //return current element
		assert((curr >= 0) && (curr < listSize), "No current element");
		return listArray[curr];
	}

	void insertionSort(bool type=true) { //insertion sort, true for greater than, false for lesser than
		if (type) {
			for (int i = 1; i < length(); i++) {//insert ith record
				for (int j = i; (j > 0) && (greaterthan(listArray[j], listArray[j - 1])); j--) {
					swap(j, j - 1);
				}
			}
		}
		else {
			for (int i = 1; i < length(); i++) {//insert ith record
				for (int j = i; (j > 0) && (lesserthan(listArray[j], listArray[j - 1])); j--) {
					swap(j, j - 1);
				}
			}
		}
	}

	void bubbleSort(bool type=true) { //bubbble sort
		for (int i = 0; i < length() - 1; i++) {
			for (int j = length() - 1; j > i; j--) {
				if (type) {
					if (greaterthan(listArray[j], listArray[j - 1]))
						swap(j, j - 1);
				}
				else {
					if (lesserthan(listArray[j], listArray[j - 1]))
						swap(j, j - 1);
				}
			}
		}
	}

	void print() {
		if (length() == 0) { std::cout << "[]" << std::endl; } //empty list
		//elseif (listArray.length() == 1) { std::cout << "[" << listArray[0] << "]"; } //list lenght one
		else {
			std::cout << "[" << listArray[0];
			for (int i = 1; i < length(); i++)
				std::cout << ", " << listArray[i];
			std::cout << "]" << std::endl;
		}
	}
};

// Singly linked list node with freelist support
template <typename E> class SLink {
private:
	static SLink<E>* freelist; //reference to freelist head
public:
	E element; //value for this node
	SLink* next; // pointer to next node in list
	//Constructors
	SLink(const E& elemval, SLink* nextval = NULL) {
		element = elemval;
		next = nextval;
	}
	SLink(SLink* nextval = NULL) {
		next = nextval;
	}
	/*
	//overloaded new operator
	void* operator new(size_t) {
		if (freelist == NULL) return new::SLink; //create space
		SLink<E>* temp = freelist; //can take from freelist
		freelist = freelist->next; //move head to next link in freelist
		return temp; //return the link
	}

	//overloaded delete operator
	void operator delete(void* ptr) {
		((SLink<E>*)ptr)->next = freelist; //put on freelist
		freelist = (SLink<E>*)ptr;
	}
	*/
};

// freelist head pointer created here
template <typename E>
SLink<E>* SLink<E>::freelist = NULL;

// Linked list implementation
template <typename E> class LList : public List<E> {
private:
	SLink<E>* head; //pointer to list header
	SLink<E>* tail; //pointer to list tail
	SLink<E>* curr; //access to current element in list
	int cnt; //length of list

	void init() { //initialization helper method
		curr = tail = head = new SLink<E>;
		cnt = 0;
	}

	void removeall() { //return link nodes to free store
		while (head != NULL) {
			curr = head;
			head = head->next;
			delete curr;
		}
	}

public:
	LList(int size = 0) { init(); } //constructor
	~LList() { removeall(); } //destructor
	//void print() const; //print list contents
	void clear() { removeall(); init(); } //reinitialize

	// insert "it" at current position
	void insert(const E& it) {
		curr->next = new SLink<E>(it, curr->next);
		if (tail == curr) tail = curr->next; //new tail
		cnt++;
	}

	void append(const E& it) {
		tail->next = new SLink<E>(it, NULL);
		tail = tail->next;
		cnt++;
	}

	//remove and return current element
	E remove() {
		assert(curr->next != NULL, "no element");
		E it = curr->next->element; //remember value
		SLink<E>* ltemp = curr->next; //remember link node
		if (tail == curr->next) tail = curr; //reset tail
		curr->next = curr->next->next; //remove from list
		delete ltemp; //reclaim space
		cnt--; //decrement the count
		return it;
	}

	void moveToStart() { curr = head; }//place curr at lsit start
	void moveToEnd() { curr = tail; }//place curr at list end

	//move curr one step left; no change if already at front
	void prev() {
		if (curr == head) return; //no previous element
		SLink<E>* temp = head;
		while (temp->next != curr) {
			temp = temp->next;
		}
		curr = temp;
	}

	//move curr one step right; no change if alreadt at end
	void next() {
		if (curr == tail) return; //no next element
		curr = curr->next;
	}

	int length() const { return cnt; }//return length

	//return the position of the current element
	int currPos() const {
		SLink<E>* temp = head;
		int i;
		for (i = 0; temp != curr; i++) {
			temp = temp->next;
		}
		return i;
	}

	//move down list to "pos" position
	void moveToPos(int pos) {
		assert((pos >= 0) && (pos <= cnt), "Position out of range");
		curr = head;
		for (int i = 0; i < pos; i++) {
			curr = curr->next;
		}
	}

	const E& getValue() const { //return current element
		assert(curr->next != NULL, "No Value");
		return curr->next->element;
	}

	void print() {
		if (length() == 0) { std::cout << "[]" << std::endl; } //empty list
		else {
			int pos = currPos();
			moveToStart();
			std::cout << "[" << getValue();
			for (int i=1; i < length(); i++) {
				next();
				std::cout << ", " << getValue();
			}
			std::cout << "]" << std::endl;
			moveToPos(pos);
		}
	}
};

//doubly linked list node with freelist support
template <typename E> class DLink {
private:
	static DLink<E>* freelist; //reference to freelist head

public:
	E element; //value for this node
	DLink* next; //pointer to next node
	DLink* prev; //pointer to previous node

	//constructors
	DLink(const E& it, DLink* prevp, DLink* nextp) {
		element = it;
		next = nextp;
		prev = prevp;
	}
	DLink(DLink* prevp = NULL, DLink* nextp = NULL) {
		prev = prevp;
		next = nextp;
	}
	/*
	//overloaded new operator
	void* operator new(size_t) {
		if (freelist == NULL) return new::DLink; //create space
		DLink<E>* temp = freelist; //can take from freelist
		freelist = freelist->next; //move freelist head up one to remove node
		return temp; //return link node
	}

	//overloaded delete operator
	void operator(void* ptr) {
		((DLink<E>*)ptr)->next = freelist; //put on freelist
		freelist = (DLink<E>*)ptr;
	}
	*/
};

//The freelist head pointer is actually created here
template <typename E>
DLink<E>* DLink<E>::freelist = NULL;

// double linked list class
template <typename E> class DLList : public List<E> {
private:
	DLink<E>* head; //pointer to list header
	DLink<E>* tail; //pointer to list tail
	DLink<E>* curr; //access to current element in list
	int cnt; //length of list

	void init() { //initialization helper method
		head = ::new DLink<E>;
		tail = ::new DLink<E>(head, NULL);
		head->next = tail;
		curr = head;
		
		cnt = 0;
	}

	void removeall() { //return link nodes to free store
		while (head != NULL) {
			curr = head;
			head = head->next;
			delete curr;
		}
	}

	void swap(DLink<E>* i, DLink<E>* j) {
		/*
		DLink<E>* temp = ::new DLink<E>(i->element, i->prev, i->next);
		i->next = j->next;
		i->prev = j->prev;
		j->next = temp->next;
		j->prev = temp->prev;
		i->next->prev = i;
		i->prev->next = i;
		j->next->prev = j;
		j->prev->next = j;
		*/
		E temp = i->element;
		i->element = j->element;
		j->element = temp;
	}

	bool greaterthan(E lhs, E rhs) {
		return lhs > rhs;
	}

	bool lesserthan(E lhs, E rhs) {
		return lhs < rhs;
	}

public:
	DLList(int size = 0) { init(); } //constructor
	~DLList() { removeall(); } //destructor
	//void print() const; //print list contents
	void clear() { removeall(); init(); } //reinitialize

	// insert "it" at current position
	void insert(const E& it) {
		curr->next = curr->next->prev = new DLink<E>(it, curr, curr->next);
		cnt++;
	}

	void append(const E& it) {
		tail->prev = tail->prev->next = new DLink<E>(it, tail->prev, tail);
		cnt++;
	}

	//remove and return current element
	E remove() {
		assert(curr->next != NULL, "no element");
		E it = curr->next->element; //remember value
		DLink<E>* ltempnext = curr->next; //remember link node
		curr->next->next->prev = curr;
		curr->next = curr->next->next; //remove from list
		delete ltempnext; //reclaim space
		cnt--; //decrement the count
		return it;
	}

	void moveToStart() { curr = head; }//place curr at lsit start
	void moveToEnd() { curr = tail; }//place curr at list end

	//move curr one step left; no change if already at front
	void prev() {
		if (curr != head) curr = curr->prev;
	}

	//move curr one step right; no change if alreadt at end
	void next() {
		if (curr != tail) curr = curr->next;
	}

	int length() const { return cnt; }//return length

	//return the position of the current element
	int currPos() const {
		DLink<E>* temp = head;
		int i;
		for (i = 0; temp != curr; i++) {
			temp = temp->next;
		}
		return i;
	}

	//move down list to "pos" position
	void moveToPos(int pos) {
		assert((pos >= 0) && (pos <= cnt), "Position out of range");
		curr = head;
		for (int i = 0; i < pos; i++) {
			curr = curr->next;
		}
	}

	const E& getValue() const { //return current element
		assert(curr->next != NULL, "No Value");
		return curr->next->element;
	}

	void insertionSort(bool type=true) { //insertion sort, true for greater than, false for lesser than
		DLink<E>* iter = head->next;
		DLink<E>* iter2;
		if (type) {
			for (iter; iter->next != tail; iter = iter->next) {//insert ith record
				for (iter2 = iter; (iter2->prev != head) && (greaterthan(iter2->element, iter2->prev->element)); iter2 = iter2->prev) {
					swap(iter2, iter2->prev);
				}
			}
		}
		else {
			for (iter; iter->next != tail; iter = iter->next) {//insert ith record
				for (iter2 = iter; (iter2->prev != head) && (lesserthan(iter2->element, iter2->prev->element)); iter2 = iter2->prev) {
					swap(iter2, iter2->prev);
				}
			}
		}
	}
	/*
	void mergeSort(E temp[], int left, int right) {
		if (left == right) return; //list of one element
		int mid = (left + right) / 2;
		mergesort(temp, left, mid);
		mergesort(temp, mid + 1, right);
		for (int i = left; i <= right; i++) //copy subarray to temp
			temp[i] = listArray[i];
		//do the merge operation back to A
		int i1 = left; int i2 = mid + 1;
		for (int curr = left; curr <= right; curr++) {
			if (i1 == mid + 1) //left sublist exhausted
				listArray[curr] = temp[i2++];
			else if (i2 > right) //right sublist exhausted
				listArray[curr] = temp[i1++];
			else if (greaterthan(temp[i1], temp[i2]))
				listArray[curr] = temp[i1++];
			else listArray[curr] = temp[i2++];
		}
	}
	*/

	void print() {
		if (length() == 0) { std::cout << "[]" << std::endl; } //empty list
		else {
			int pos = currPos();
			moveToStart();
			std::cout << "[" << getValue();
			for (int i = 1; i < length(); i++) {
				next();
				std::cout << ", " << getValue();
			}
			std::cout << "]" << std::endl;
		}
	}
};

template <typename E> //array based list implementation with adaptive length
class ALenList : public List<E> {
private:
	int initSize; //initial size of list
	int maxSize; //current maxSize of list
	int listSize; //number of list items now
	int curr; //position of current element
	E* listArray; //array holding list elements

	void listCopy(E* left, E* right, int len) {
		for (int i = 0; i < len; i++) {
			left[i] = right[i];
		}
	}

	void incSize() {
		int threeQuarterSize = maxSize * 3 / 4;
		if (listSize >= threeQuarterSize) {
			E* tempList = new E[maxSize];
			listCopy(tempList, listArray, listSize);
			maxSize *= 2;
			delete[] listArray;
			listArray = new E[maxSize];
			listCopy(listArray, tempList, listSize);
			delete[] tempList;
		}
	}

	void decSize() {
		int oneQuarterSize = maxSize * 1 / 4;
		if (listSize <= oneQuarterSize) {
			E* tempList = new E[maxSize];
			listCopy(tempList, listArray, listSize);
			maxSize /= 2;
			delete[] listArray;
			listArray = new E[maxSize];
			listCopy(listArray, tempList, listSize);
			delete[] tempList;
		}
	}

	void swap(int i, int j) {
		E temp = listArray[j];
		listArray[j] = listArray[i];
		listArray[i] = temp;
	}

	void swap(E A[], int i, int j) {
		E temp = A[j];
		A[j] = A[i];
		A[i] = temp;
	}

	bool greaterthan(E lhs, E rhs) {
		return lhs > rhs;
	}

	bool lesserthan(E lhs, E rhs) {
		return lhs < rhs;
	}

	void insertionSortIncremented(bool greater = true, int n = length(), int incr = 1) {
		if (greater) {
			for (int i = incr; i < n; i += incr) {
				for (int j = i; (j >= incr) && (greaterthan(listArray[j], listArray[j - incr])); j -= incr)
					swap(j, j - incr);
			}
		}
		else {
			for (int i = incr; i < n; i += incr) {
				for (int j = i; (j >= incr) && (lesserthan(listArray[j], listArray[j - incr])); j -= incr)
					swap(j, j - incr);
			}
		}
	}

	void merge(E arr[], int l, int m, int r, bool greater) {
		int i, j, k;
		int n1 = m - l + 1;
		int n2 = r - m;
		E* L = new E[n1];
		E* R = new E[n2]; // create temp arrays 
		for (i = 0; i < n1; i++) //Copy data to temp arrays L[] and R[]
			L[i] = arr[l + i];
		for (j = 0; j < n2; j++)
			R[j] = arr[m + 1 + j];
		/* Merge the temp arrays back into arr[l..r]*/
		i = 0; // Initial index of first subarray 
		j = 0; // Initial index of second subarray 
		k = l; // Initial index of merged subarray
		if (greater) {
			while (i < n1 && j < n2) {
				if (greaterthan(L[i], R[j])) {
					arr[k] = L[i];
					i++;
				}
				else {
					arr[k] = R[j];
					j++;
				}
				k++;
			}
			/* Copy the remaining elements of L[], if there
			   are any */
			while (i < n1) {
				arr[k] = L[i];
				i++;
				k++;
			}
		}
		else {
			while (i < n1 && j < n2) {
				if (lesserthan(L[i], R[j])) {
					arr[k] = L[i];
					i++;
				}
				else {
					arr[k] = R[j];
					j++;
				}
				k++;
			}
			/* Copy the remaining elements of L[], if there
			   are any */
			while (i < n1) {
				arr[k] = L[i];
				i++;
				k++;
			}
		}
		/* Copy the remaining elements of R[], if there
		   are any */
		while (j < n2) {
			arr[k] = R[j];
			j++;
			k++;
		}

		delete[] L;
		delete[] R;
	}

	/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
	void mergeSortHelp(E A[], bool greater, int l, int r) {
		if (l < r) {
			// Same as (l+r)/2, but avoids overflow for 
			// large l and h 
			int m = l + (r - l) / 2;
			// Sort first and second halves 
			mergeSortHelp(A, greater, l, m);
			mergeSortHelp(A, greater, m + 1, r);
			merge(A, l, m, r, greater);
			//std::cout << "left, mid, right index sorted :   " << l << ", " << m << ", " << r << std::endl;
		}
	}

	//quicksort
	void qsortHelp(E A[], bool greater, int i, int j) { //quicksort
		if (j <= i) return; //dont sort 0 or 1 elements
		int pivotindex = (i + j) / 2;
		swap(A, pivotindex, j); //put pivot at end
		//k will be the first position in the right subarray
		int k = partition(A, i - 1, j, A[j], greater);
		swap(A, k, j); //put pivot in place)
		qsortHelp(A, greater, i, k - 1);
		qsortHelp(A, greater, k + 1, j);
	}

	inline int findpivot(int i, int j) {
		return (i + j) / 2;
	}

	inline int partition(E A[], int l, int r, E& pivot, bool greater) {
		if (greater) {
			do { //move the bounds inward until they meet
				while (greaterthan(A[++l], pivot)); //move l right and r left
				while ((l < r) && greaterthan(pivot, A[--r]));
				swap(A, l, r); //swap out of place values
			} while (l < r); // stop when they cross
			return l;// return first position in right partition
		}
		else {
			do { //move the bounds inward until they meet
				while (lesserthan(A[++l], pivot)); //move l right and r left
				while ((l < r) && lesserthan(pivot, A[--r]));
				swap(A, l, r); //swap out of place values
			} while (l < r); // stop when they cross
			return l;// return first position in right partition
		}
	}

public:
	ALenList(int size = 100) { //constructor
		initSize = size;
		maxSize = size;
		listSize = curr = 0;
		listArray = new E[maxSize];
	}

	~ALenList() { delete[] listArray; } //destructor

	/*
	ALenList(const ALenList& rhs) {
		std::cout << "copy constructor called" << std::endl;
		for (int i = 0; i < rhs.length(); i++) {
			listArray[i] = rhs.listArray[i];
		}
	}

	ALenList& operator =(const ALenList& rhs) {
		std::cout << "assignment called" << std::endl;
		for (int i = 0; i < rhs.length(); i++) {
			listArray[i] = rhs.listArray[i];
		}
		return *this;
	}
	*/
	E operator [](int index) {
		return listArray[index];
	}

	void clear() { //reinitialize the list
		delete[] listArray; //remove the array
		listSize = curr = 0; //reset the size
		listArray = new E[initSize]; //recreate the array
		maxSize = initSize;
	}

	//insert "it" at current position
	void insert(const E& it) {
		assert(listSize < maxSize, "List capacity exceeded");
		incSize();
		for (int i = listSize; i > curr; i--) { //shift elements up
			listArray[i] = listArray[i - 1];			// to make room
		}
		listArray[curr] = it;
		listSize++; //increment list size
	}

	void append(const E& it) { //append "it"
		assert(listSize < maxSize, "List capacity exceeded");
		incSize();
		listArray[listSize++] = it;
	}

	//remove and return the current element
	E remove() {
		assert((curr >= 0) && (curr < listSize), "No Element");
		E it = listArray[curr]; //copy the element
		for (int i = curr; i < listSize - 1; i++) //shift them down
			listArray[i] = listArray[i + 1];
		listSize--; //decrement list size
		if (curr = listSize) curr--; // decrement curr position if removing last element
		decSize();
		return it;
	}

	void moveToStart() { curr = 0; } //reset position
	void moveToEnd() { curr = listSize; } //set at end
	void prev() { if (curr != 0) curr--; } //back up
	void next() { if (curr < listSize) curr++; } //next

	//return list size
	int length() const { return listSize; }

	//return current position
	int currPos() const { return curr; }

	//set current list position to "pos"
	void moveToPos(int pos) {
		assert((pos >= 0) && (pos < listSize), "Position out of range");
		curr = pos;
	}

	const E& getValue() const { //return current element
		assert((curr >= 0) && (curr < listSize), "No current element");
		return listArray[curr];
	}

	void selsort(bool greater=true) { //selection sort
		if (greater) {
			for (int i = 0; i < length() - 1; i++) {
				int lowindex = i;
				for (int j = length() - 1; j > i; j--) {
					if (greaterthan(listArray[j], listArray[lowindex]))
						lowindex = j;
				}
				swap(i, lowindex);
			}
		}
		else {
			for (int i = 0; i < length() - 1; i++) {
				int lowindex = i;
				for (int j = length() - 1; j > i; j--) {
					if (lesserthan(listArray[j], listArray[lowindex]))
						lowindex = j;
				}
				swap(i, lowindex);
			}
		}
	}

	void insertionSort(bool type = true) { //insertion sort, true for greater than, false for lesser than
		if (type) {
			for (int i = 1; i < length(); i++) {//insert ith record
				for (int j = i; (j > 0) && (greaterthan(listArray[j], listArray[j - 1])); j--) {
					swap(j, j - 1);
				}
			}
		}
		else {
			for (int i = 1; i < length(); i++) {//insert ith record
				for (int j = i; (j > 0) && (lesserthan(listArray[j], listArray[j - 1])); j--) {
					swap(j, j - 1);
				}
			}
		}
	}

	void shellSort(bool greater=true, int n = length(), bool verbose=false) { //shellsort
		if (greater) {
			for (int i = n / 2; i > 2; i /= 2) //for each increment
				for (int j = 0; j < i; j++) //sort each sublist
					insertionSortIncremented(true, n - j, i);
			if (verbose) {
				std::cout << "preliminary incremented insertion sort : " << std::endl;
				print();
			}
			insertionSortIncremented(true, length(), 1);
		}
		else {
			for (int i = n / 2; i > 2; i /= 2) //for each increment
				for (int j = 0; j < i; j++) //sort each sublist
					insertionSortIncremented(false, n - j, i);
			if (verbose) {
				std::cout << "preliminary incremented insertion sort : " << std::endl;
				print();
			}
			insertionSortIncremented(false, length(), 1);
		}
	}

	void mergeSort(bool greater=true, int left=0, int right=NULL) {
		if (right == NULL) {
			right = length()-1;
		}
		mergeSortHelp(listArray, greater, left, right);
	}

	void print(int left=0, int right=NULL) {
		if (right == NULL) {
			right = length()-1;
		}
		if (length() == 0) { std::cout << "[]" << std::endl; } //empty list
		//elseif (listArray.length() == 1) { std::cout << "[" << listArray[0] << "]"; } //list lenght one
		else {
			std::cout << "[" << listArray[left];
			for (int i = left + 1; i <= right; i++)
				std::cout << ", " << listArray[i];
			std::cout << "]" << std::endl;
		}
	}

	int getMaxSize() { return maxSize; }
	
	void quickSort(bool greater=true, int left=0, int right=NULL) {
		if (right == NULL) {
			right = length() - 1;
		}
		qsortHelp(listArray, greater, left, right);
	}
};
