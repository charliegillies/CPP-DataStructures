/*
 * Linked list test program.
 */

#include "LinkedList.h"
#include <iostream>

int main()
{
	LinkedList<int> intList;

	// push a couple of numbers into the list..
	intList.push_back(10);
	intList.push_back(20);
	intList.push_front(5);

	// list size should now be 3, confirm that
	assert(!intList.empty());
	assert(intList.size() == 3);

	// this should look like 5 -> 10 -> 20, confirm that
	assert(intList.top() == 5);
	intList.pop_front();
	assert(intList.top() == 10);
	intList.pop_front();
	assert(intList.top() == 20);
	intList.pop_front();

	// we've removed all elements from the list, confirm empty
	assert(intList.empty());

	// put some data back into the int list
	intList.push_back(100);
	intList.push_back(150);
	intList.push_back(-99);
	intList.push_front(200);
	// data should now look like 200 -> 100 -> 150 -> -99
	// first confirm list size is 4 elements
	assert(intList.size() == 4);
	// now let's confirm that the last element is -99
	assert(intList.back() == -99);

	// okay, now let's get, insert and remove some data.
	// at index 1 we have element '100', confirm that
	assert(intList.at(1) == 100);
	
	// remove that same element, ensure size is now 3
	intList.remove_at(1);
	assert(intList.size() == 3);
	// element at position 1 should now be '150'
	assert(intList.at(1) == 150);

	// so now let's insert 100 back into its position
	intList.insert_at(1, 100);
	assert(intList.at(1) == 100);

	// confirm we're back at a 4 size array
	assert(intList.size() == 4);
	// now let's test .remove_at on the first and last positions
	intList.remove_at(0);
	intList.remove_at(2);
	// now we should have two elements, 100 and 150
	assert(intList.size() == 2);

	// iterator print test for the remaining two elements
	// this uses the automatic for loop
	std::cout << "auto for loop: " << std::endl;
	for (int i : intList) {
		std::cout << "\t" << i << std::endl;
	}

	std::cout << "\nrange loop: " << std::endl;
	for (auto iterator = intList.begin(); iterator != intList.end(); ++iterator) {
		std::cout << "\t" << *iterator << std::endl;
	}

	// pause until key command
	system("pause");
	return 0;
}
