#pragma once
#include <assert.h>
#include "List.h"

// Stack Abstract Class
template <typename E> class Stack {
private:
	void operator = (const Stack&) {} //protect assignment
	Stack(const Stack&) {} //protect copy constructor

public:
	Stack() {} //default constructor
	~Stack() {} //base destructor

	//reinitialize the stack. the user is responsible
	//for reclaiming the storage used by the stack elements
	virtual void clear() = 0;

	//push an element onto the top of the stack.
	//return: the element at the top of the stack
	virtual E pop() = 0;

	//return: a copy of the top element
	virtual const E& topValue() const = 0;

	//return the number of elements in the stack
	virtual int length() const = 0;

	virtual void push(const E&) = 0;
};

//array based stack implementation
template <typename E> class AStack : public Stack<E> {
private:
	int maxSize; //maximimum size of stack
	int top; //index for top element
	E* listArray; //array holding stack elements

public:
	AStack(int size = 20) { maxSize = size; top = 0; listArray = new E[size]; } //constructor
	~AStack() { delete[] listArray; } //destructor
	void clear() { top = 0; } //reinitialize

	void push(const E& it) { //put "it" on stack
		assert(top != maxSize, "Stack is full");
		listArray[top++] = it;
	}

	E pop() {//return current top element of stack
		assert(top != 0, "Stack is empty");
		return listArray[--top];
	}

	const E& topValue() const { //return copy of top element of stack
		assert(top != 0, "Stack is empty");
		return listArray[top - 1];
	}

	int length() const { //return length
		return top;
	}

	void print() {
		if (length() == 0) { std::cout << "stack is empty" << std::endl; } //empty stack
		else {
			std::cout << "_____________" << std::endl;
			for (int i=1; i<=length(); i++)
				std::cout << listArray[top - i] << std::endl;
			std::cout << "_____________" << std::endl;
		}
		
	}
};

//linked stack implementation
template <typename E> class LStack : public Stack<E> {
private:
	SLink<E>* top; //pointer to first element
	int size; //number of elements

public:
	LStack(int sz = 20) {//constructor
		top = NULL; size = 0;
	}
	~LStack() { clear(); } //destructor

	void clear() { //reinitialize
		while (top != NULL) { //delete link nodes
			SLink<E>* temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}

	void push(const E& it) {//put it on stack
		top = new SLink<E>(it, top);
		size++;
	}

	E pop() {//remove it from stack
		assert(top != NULL, "stack is empty");
		E it = top->element;
		SLink<E>* ltemp = top->next;
		delete top;
		top = ltemp;
		size--;
		return it;
	}

	const E& topValue() const {//return copy of current top element of stack
		assert(top != NULL, "stack is empty");
		return top->element;
	}

	int length() const {//return size of stack
		return size;
	}

	void print() {
		if (length() == 0) { std::cout << "stack is empty" << std::endl; } //empty stack
		else {
			std::cout << "_____________" << std::endl;
			SLink<E>* temp = top;
			for (int i = 1; i <= length(); i++) {
				std::cout << top->element << std::endl;
				top = top->next;
			}
			std::cout << "_____________" << std::endl;
			top = temp;
		}
	}
};