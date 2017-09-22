#ifndef CUSTOMSTACK_H
#define CUSTOMSTACK_H

/*
 * Note to reader:
 * This stack uses dynamic allocation, and will automatically
 * resize itself if we expand over our initial limit.
 */

/** A stack of whatever type we specify. */
template<typename T>
class CustomStack {
private:
	unsigned int _count;
	unsigned int _arraySize;
	T* _array;

	/** Resizes the array to the given amount  */
	void resize(unsigned int size) {
		// create a dynamic array with our given size
		T* newArray = new T[size];
		
		// copy over our current items to the new array
		for (int i = 0; i < _count; i++) {
			newArray[i] = _array[i];
		}

		// now delete our current array and set the new one
		delete[] _array;
		_array = newArray;
		_arraySize = size;
	}

public:
	/** Creates a new CustomStack. Allocates space for 100 items, but will dynamically resize.*/
	CustomStack() : _count(0), _arraySize(100) { 
		_array = new T[_arraySize];
	}
	
	~CustomStack() {
		delete[] _array;
	}

	/** Return true if the stack is empty, false otherwise. */
	bool empty() {
		return _count == 0;
	}

	/** Add an item to the top of the stack. */
	void push(const T& value) {
		// if we've gone over our dynamic array size, resize!
		if (_count + 1 >= _arraySize) {
			resize(_arraySize + 100);
		}

		// We use _count as an index for pushing things into our stack
		// since _count will always be 1 ahead of our last push position
		_array[_count] = value;
		_count++;
	}

	/** Remove the item at the top of the stack. */
	void pop() {
		// ensure our stack is not empty
		if (empty()) {
			throw std::exception("Cannot pop() on an empty stack.");
		}

		// we remove an element by simply moving our index down by 1
		_count--;

		// NOTE: there is a big problem with this design however
		// as we leave the object previously at the count position
		// in memory.. so if it was a shared_ptr, it wouldn't be removed
		// until the stack reallocates or the stack is deconstructed.
	}

	/** Return the item at the top of the stack. */
	T& top() {
		// ensure our stack is not empty
		if (empty()) {
			throw std::exception("Cannot top() on an empty stack.");
		}

		// Count always specifies the point ahead
		// of our last push, so: (count - 1) represents
		// the index of our last push
		return _array[_count - 1];
	}

	/** Return the number of items on the stack. */
	int size() {
		return _count;
	}
};

#endif