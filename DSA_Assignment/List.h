// List.h - - Specification of List ADT
#pragma once
#include <iostream>
#include "Booking.h"
using namespace std;

const int MAX_SIZE = 100;
typedef Booking ItemType;

class List
{
private:
	ItemType items[MAX_SIZE];
	int      size;

public:

	// constructor
	List();

	// add an item to the back of the list (append)
	// pre : size < MAX_SIZE
	// post: item is added to the back of the list
	//       size of list is increased by 1
	bool add(ItemType &item);

	// add an item at a specified position in the list (insert)
	// pre : 0 <= index < size && size < MAX_SIZE
	// post: item is added to the specified position in the list
	//       size of list is increased by 1
	bool add(int index, ItemType& item);

	// remove an item at a specified position in the list
	// pre : 0 <= index < size
	// post: item is removed the specified position in the list
	//       size of list is decreased by 1
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	// pre : 0 <= index < size
	// post: none
	ItemType& get(int index);

	// check if the list is empty
	// pre : none
	// post: none
	// return true if the list is empty; otherwise returns false
	bool isEmpty();

	// check the size of the list
	// pre : none
	// post: none
	// return the number of items in the list
	int getLength();
	
	// to display all the items in the list
	// pre: none
	// post: none <-- no changes made to the list
	void print();
	
	// to replace the specified index position with the item
	// pre: 0 <= index < size
	// post: item is now in index position
	void replace(int index, ItemType item);

	// to find specified person's name
	// pre: none
	// post: none
	int findName(string);
};
