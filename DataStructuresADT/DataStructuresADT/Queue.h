#include <iostream>
#include "List.h"
//Abstract Queue Class
template <typename E> class Queue {
private:
	void operator = (const Queue&) {} //protect assignment
	Queue(const Queue&) {} //protect copy constructor

public:
	Queue() {} //default constructor
	~Queue() {}//base destructor

	//reinitialize the queue. the user is responsible for
	//reclaiming the storage used by the queue elements
	virtual void clear() = 0;

	//place an element at the rear of the queue.
	//it: the elemnt being enqueued
	virtual void enqueue(const E&) = 0;

	//remove and return element at the front of the queue
	//return: the element at the front of the queue
	virtual E dequeue() = 0;

	//return: a copy of the front element
	virtual const E& frontValue() const = 0;

	//return the number of elements in the queue
	virtual int length() const = 0;
};

//array based queue implementation
template <typename E> class AQueue : public Queue<E> {
private:
	int front; //index of current front element of queue
	int rear; //index of current rear elemenet of queue
	int maxSize; //max size of queue
	E* listArray; //array holding queue elements 

public:
	AQueue(int size = 20) { //constructor
		//make list array one position larger for empty slot
		maxSize = size + 1;
		rear = 0;
		front = 1;
		listArray = new E[maxSize];
	}
	~AQueue() { delete[] listArray; } //destructor

	void clear() { rear = 0; front = 1; }//reinitialize

	void enqueue(const E& it) { //put it in queue
		assert((rear + 2) % maxSize != front, "Queue is full");
		rear = (rear + 1) % maxSize; //circular increment
		listArray[rear] = it;
	}

	E dequeue() {//return element at front of queue
		assert(length() != 0, "Queue is empty");
		E it = listArray[front];
		front = (front + 1) % maxSize;
		return it;
	}

	const E& frontValue() const {//return copy of front element
		assert(length() != 0, "Queue is empty");
		return listArray[front];
	}

	int length() const {//return size of queue
		return ((rear + maxSize) - front + 1) % maxSize;
	}

	void print() {
		int pos = front;
		std::cout << listArray[pos];
		pos++;
		while (pos != rear) {
			if (pos == maxSize) { pos = 0;} //circle array
			else {
				std::cout << " <- " << listArray[pos];
				pos++;
			}
		}
		std::cout << " <- " << listArray[pos] << std::endl;
	}
};

//linked queue implementation
template <typename E> class LQueue : public Queue<E> {
private:
	SLink<E>* front; //pointer to front queue node
	SLink<E>* rear; //pointer to rear queue node
	int size; //number of elements in queue

public:
	LQueue(int sz = 20) //Coonstructor
	{
		front = rear = new SLink<E>(); size = 0;
	}

	~LQueue() { clear(); delete front; }//destructor

	void clear() {
		while (front->next != rear) {
			SLink<E>* old = front;
			front = front->next;
			delete old;
		}
		SLink<E>* old = rear;
		rear = front;
		delete old;
		size = 0;
	}

	void enqueue(const E& it) {
		rear->next = new SLink<E>(it, NULL);
		rear = rear->next;
		size++;
	}

	E dequeue() {
		assert(size != 0, "Queeu is empty");
		E it = front->next->element;
		SLink<E>* ltemp = front->next;
		front->next = ltemp->next;
		if (rear == ltemp) rear = front;
		delete ltemp;
		size--;
		return it;
	}

	const E& frontValue() const {
		assert(size != 0, "Queeue is empty");
		return front->next->element;
	}

	int length() const { return size; }

	void print() {
		SLink<E>* pos = front;
		std::cout << pos->next->element;
		pos = pos->next;
		while (pos != rear) {
			std::cout << " <- " << pos->next->element;
			pos = pos->next;
		}
		std::cout << std::endl;
	}
};

//linked double ended queue implementation
template <typename E> class LDequeue : public Queue<E> {
private:
	DLink<E>* front; //pointer to front queue node
	DLink<E>* rear; //pointer to rear queue node
	int size; //number of elements in queue

public:
	LDequeue(int sz = 20) //Coonstructor
	{
		front = new DLink<E>(NULL, NULL);
		rear = new DLink<E>(front, NULL);
		front->next = rear;
		size = 0;
	}

	~LDequeue() { clear(); delete front; }//destructor

	void clear() {
		while (front->next != rear) {
			DLink<E>* old = front;
			front = front->next;
			delete old;
		}
		DLink<E>* old = rear;
		rear = front;
		delete old;
		size = 0;
	}

	void enqueue(const E& it) {
		enqueueRear(it);
	}

	void enqueueRear(const E& it) {
		rear->next = new DLink<E>(rear, NULL);
		rear = rear->next;
		rear->prev->element = it;
		size++;
	}

	void enqueueFront(const E& it) {
		front->prev = new DLink<E>(it, NULL, front);
		front = front->prev;
		front->next->element = it;
		size++;
	}

	E dequeue() {
		E it = dequeueFront();
		return it;
	}

	E dequeueFront() {
		assert(size != 0, "Queue is empty");
		E it = front->next->element;
		DLink<E>* ltemp = front->next;
		front->next = ltemp->next;
		front->next->prev = front;
		if (rear == ltemp) rear = front;
		delete ltemp;
		size--;
		return it;
	}

	E dequeueRear() {
		assert(size != 0, "Queeu is empty");
		E it = rear->prev->element;
		DLink<E>* ltemp = rear->prev;
		rear->prev = ltemp->prev;
		rear->prev->next = rear;
		if (front == ltemp) rear = front;
		delete ltemp;
		size--;
		return it;
	}

	const E& frontValue() const {
		assert(size != 0, "Queeue is empty");
		return front->next->element;
	}

	const E& rearValue() const {
		assert(size != 0, "Queeue is empty");
		return rear->prev->element;
	}

	int length() const { return size; }

	void print() {
		DLink<E>* pos = front;
		std::cout << pos->next->element;
		pos = pos->next;
		while (pos->next != rear) {
			std::cout << " <- " << pos->next->element;
			pos = pos->next;
		}
		std::cout << std::endl;
	}
};