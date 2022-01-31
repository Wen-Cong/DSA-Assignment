// List_AvailableRooms.cpp - Implementation of List ADT using Array
#include "List_AvailableRooms.h" // header file

// constructor
List_AvailableRooms::List_AvailableRooms() { size = 0; }

// add an item to the back of the list (append)
bool List_AvailableRooms::add(AvailRoom item)
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
bool List_AvailableRooms::add(int index, AvailRoom item)
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
void List_AvailableRooms::remove(int index)
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
AvailRoom List_AvailableRooms::get(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
		return items[index];
	else
		return -1;
}

// check if the list is empty
bool List_AvailableRooms::isEmpty() { return size == 0; }

// check the size of the list
int List_AvailableRooms::getLength() { return size; }



// display the items in the list
void List_AvailableRooms::print()
{

	for (int pos = 0; pos < size; pos++) {
		cout << "Room Number: "<< items[pos] << endl;
	}
}

// replace the  item in the specified index in the list
void List_AvailableRooms::replace(int index, AvailRoom item)
{
	items[index] = item;
}
int List_AvailableRooms::find(AvailRoom item) {
	for (int pos = 0; pos < size; pos++) {
		if (items[pos] == item) {
			return pos;
		}
	}return-1;
}
bool List_AvailableRooms::exists(AvailRoom item) {
	for (int pos = 0; pos < size; pos++) {
		if (items[pos] == item) {
			return true;
		}
	}
	return false;
}
