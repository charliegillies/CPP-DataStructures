// Test program for my CustomStack

#include "stdafx.h" 
#include "CustomStack.h"

#include <cassert>
#include <exception>

int main()
{
	// begin test program!
	CustomStack<int> testStack;

	// push 42, then ensure our top element is 42
	testStack.push(42);
	assert(testStack.top() == 42);

	// now push 21, then ensure our top element is 21
	testStack.push(21);
	assert(testStack.top() == 21);
	
	// ensure that we have two items in our stack
	assert(testStack.size() == 2);

	// now let's pop our two items and ensure the stack is empty
	testStack.pop();
	testStack.pop();
	assert(testStack.empty());

	// great, now let's add 101 items to ensure the stack dynamically resizes..
	for (int i = 0; i <= 101; i++) {
		testStack.push(i);
	}

	// so now our stack SHOULD hold ints from 0-101
	// so let's do a reverse loop to ensure that's the case!
	for (int i = 101; i >= 0; i--) {
		// ensure top() and i are equal
		assert(testStack.top() == i);
		testStack.pop();
	}

	// now check again that our stack is empty
	assert(testStack.empty());

	// now let's do some assertion tests..
	// 1. if we try to pop an empty stack, it should throw an exception
	bool exceptionThrown = false;
	try {
		testStack.pop();
	}
	catch(std::exception& e) {
		exceptionThrown = true;
	}

	assert(exceptionThrown);

	// 2. calling top() on an empty stack should throw an exception..
	exceptionThrown = false;
	try {
		testStack.top();
	}
	catch (std::exception& e) {
		exceptionThrown = true;
	}

	assert(exceptionThrown);
    
	return 0;
}