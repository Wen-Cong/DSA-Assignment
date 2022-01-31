#pragma once
#include <iostream>
using namespace std;

typedef int AvailRoom;
// to change accordingly to number of rooms
const int AR_MAX_SIZE = 20;

class List
{
public:
	AvailRoom items[AR_MAX_SIZE];
	int      size;

public:

	// constructor
	List();

	// add an item to the back of the list (append)
	// pre : size < MAX_SIZE
	// post: item is added to the back of the list
	//       size of list is increased by 1
	bool add(AvailRoom item);

	// add an item at a specified position in the list (insert)
	// pre : 0 <= index < size && size < MAX_SIZE
	// post: item is added to the specified position in the list
	//       size of list is increased by 1
	bool add(int index, AvailRoom item);

	// remove an item at a specified position in the list
	// pre : 0 <= index < size
	// post: item is removed the specified position in the list
	//       size of list is decreased by 1
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	// pre : 0 <= index < size
	// post: none
	AvailRoom get(int index);

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
	void replace(int index, AvailRoom item);

	int find(AvailRoom item);

	bool exists(AvailRoom item);
};

