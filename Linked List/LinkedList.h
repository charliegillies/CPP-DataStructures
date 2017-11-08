#pragma once

#include <cassert>

/*
 * Template based single linked list of items.
 */
template<typename T>
class LinkedList {
private:
	/* The nodes that form our chain. */
	struct Node {
		Node(const T& value) : value(value), next(nullptr), previous(nullptr) { }

		// template value of the node
		T value;
		// the next node in the linked list
		Node* next;
		// the previous node in the linked list
		Node* previous;
	};

public:
	// I kept Node and Iterator separate to hide the internal 
	// operations of the LinkedList, as I didn't want to expose the Nodes themselves.
	struct Iterator {
	private:
		Node* _node;

	public:
		explicit Iterator(Node* node) : _node(node) { }

		Iterator() = default;

		Iterator(const Iterator& i) {
			_node = i._node;
		}

		~Iterator() { }

		T& operator*() {
			return _node->value;
		}

		Iterator& operator++() {
			_node = _node->next;
			return *this;
		}

		Iterator& operator--() {
			_node = _node->previous;
			return *this;
		}

		bool operator==(const Iterator& it) {
			return _node == it._node;
		}

		bool operator!=(const Iterator& it) {
			return _node != it._node;
		}

	};

private:

	Node* _begin;
	Node* _end;
	int _size;

	/* Helper to find a node at a given index. */
	Node* node_at(const int index) {
		// ensure not empty and that index is valid
		assert(!empty() && index >= 0 && index < _size);

		// start at index 0, move to the value of index
		int i = 0;
		Node* search = _begin;
		while (i != index) {
			search = search->next;
			i++;
		}

		return search;
	}

public:
	LinkedList() : _begin(nullptr), _end(nullptr), _size(0) { } 

	~LinkedList() {
		// iterate through the linked list, delete all nodes
		Node* toDelete = _begin;
		while (toDelete != nullptr) {
			Node* next = toDelete->next;
			delete toDelete;
			toDelete = next;
		}

		_begin = nullptr;
		_end = nullptr;
		_size = 0;
	}

	Iterator begin() const {
		return Iterator(_begin);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}

	/* Pushes a value to the front of the list. */
	void push_front(const T& value) {
		_size++;

		// if we have no start node, create one
		if (_begin == nullptr) {
			_begin = new Node(value);
			_end = _begin;
		}
		else {
			// create our new beginning node, assign next as current begin
			Node* n = new Node(value);
			n->next = _begin;

			// set old _begins previous node to the new node, as it comes before it
			_begin->previous = n;

			_begin = n;
		}
	}

	/* Pushes a value to the back of the list. */
	void push_back(const T& value) {
		_size++;

		// if we have no start node, create one
		if (_begin == nullptr) {
			_begin = new Node(value);
			_end = _begin;
		}
		else {
			Node* n = new Node(value);
			// tell the nodes about each other
			_end->next = n;
			n->previous = _end;

			// and assign the new node to the end node
			_end = n;
		}
	}

	/* Gets the size of the list. */
	const int size() const {
		return _size;
	}

	/* Checks if the list is empty or not. */
	const bool empty() const {
		return _size == 0;
	}

	/* Gets the element at the top of the list. */
	const T& top() const {
		// ensure that the list is not empty, or _begin is a nullptr.
		assert(!empty());
		return _begin->value;
	}

	/* Gets the element at the back of the list. */
	const T& back() const {
		assert(!empty());
		return _end->value;
	}

	/* Removes the element at the front of the list. */
	void pop_front() {
		assert(!empty());

		// get a reference to our next node, remove reference to _begin
		Node* next = _begin->next;
		if(next != nullptr)
			next->previous = nullptr;

		// delete begin, assign to the next node in the list
		delete _begin;
		_begin = next;

		_size--;
	}

	void pop_back() {
		assert(!empty());

		// the second last node in the chain, set next to nullptr
		Node* prev = _end->previous;
		prev->next = nullptr;

		// delete current end, assign to previous
		delete _end;
		_end = prev;

		_size--;
	}

	/* Gets an element at index position of the list. 
	 * Takes longer depending on list size and index position.
	 */
	const T& at(const int index) {
		// ensure not empty and that index is valid
		assert(!empty() && index >= 0 && index < _size);
		// get the node at index, return its value
		return node_at(index)->value;
	}

	/* Inserts a given value into a given index. */
	void insert_at(const int index, const T& value) {
		// ensure index is valid
		assert(index >= 0 && index < _size);

		// first thing to check, is if our 'insert' is at our 
		// beginning or end positions, which would mean replacing our
		// _begin and _end values, we can cheat using push_front and push_back
		if (index == 0) {
			push_front(value);
		}
		else if (index == (_size - 1)) {
			push_back(value);
		}
		else {
			// not a start or end position, so get the node at index
			Node* current = node_at(index);
			// now create a new node representing our inserted value
			Node* n = new Node(value);

			// make the current index positions nodes previous nodes
			// next node equal to our new node. This forms the left hand chain
			current->previous->next = n;
			// while currents previous node is now our new node
			current->previous = n;
			// new nodes NEXT node is the current node
			n->next = current;

			_size++;
		}
	}

	/* Removes an element from a given index. */
	void remove_at(const int index) {
		// ensure index is valid
		assert(index >= 0 && index < _size);

		// we will do the same thing as insert_at 
		// and cheat using the index position
		if (index == 0) {
			pop_front();
		}
		else if (index == (_size - 1)) {
			pop_back();
		}
		else {
			// get the current node at index
			Node* current = node_at(index);
			// to remove we just put currents previous node
			// as equal to currents next node and vice versa
			Node* prev = current->previous;
			Node* next = current->next;
			prev->next = next;
			next->previous = prev;

			// and then delete current, which is no longer referenced
			delete current;

			_size--;
		}
	}
};
