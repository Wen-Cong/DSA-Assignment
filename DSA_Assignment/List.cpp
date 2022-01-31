//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
// List_AvailableRooms.cpp - Implementation of List ADT using Array
#include "List.h" // header file

// constructor
List::List() { size = 0; }

// add an item to the back of the list (append)
bool List::add(AvailRoom item)
{
	bool success = size < AR_MAX_SIZE;
	if (success)
	{
		items[size] = item;    // add to the end of the list
		size++;                // increase the size by 1
	}
	return success;
}

// add an item at a specified position in the list (insert)
bool List::add(int index, AvailRoom item)
{
	bool success = (index >= 0) && (index <= size) && (size < AR_MAX_SIZE);
	if (success)
	{  // make room for the item by shifting all items at
	   // positions >= index toward the end of the
	   // List (no shift if index == size + 1)
		for (int pos = size; pos >= index; pos--)
			items[pos] = items[pos - 1];
		// insert the item
		items[index] = item;
		size++;  // increase the size by 1
	}
	return success;
}

// remove an item at a specified position in the list
void List::remove(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
	{  // delete item by shifting all items at positions >
	   // index toward the beginning of the list
	   // (no shift if index == size)
		for (int pos = index; pos < size; pos++)
			items[pos] = items[pos + 1];
		size--;  // decrease the size by 1
	}

}

// get an item at a specified position of the list (retrieve)
AvailRoom List::get(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
		return items[index];
	else
		return -1;
}

// check if the list is empty
bool List::isEmpty() { return size == 0; }

// check the size of the list
int List::getLength() { return size; }



// display the items in the list
void List::print()
{

	for (int pos = 0; pos < size; pos++) {
		cout << "Room Number: "<< items[pos] << endl;
	}
}

// replace the  item in the specified index in the list
void List::replace(int index, AvailRoom item)
{
	items[index] = item;
}
int List::find(AvailRoom item) {
	for (int pos = 0; pos < size; pos++) {
		if (items[pos] == item) {
			return pos;
		}
	}return-1;
}
bool List::exists(AvailRoom item) {
	for (int pos = 0; pos < size; pos++) {
		if (items[pos] == item) {
			return true;
		}
	}
	return false;
}
