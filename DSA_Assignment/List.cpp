// List.cpp - Implementation of List ADT using Array
#include "List.h"  // header file

// constructor
List::List() { size = 0; }

// add an item to the back of the list (append)
bool List::add(ItemType &item)
{
	bool success = size < MAX_SIZE;
	if (success)
	{
		items[size] = item;    // add to the end of the list
		size++;                // increase the size by 1
	}
	return success;
}

// add an item at a specified position in the list (insert)
bool List::add(int index, ItemType& item)
{
	bool success = (index >= 0) && (index <= size) && (size < MAX_SIZE);
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
ItemType& List::get(int index)
{
	ItemType p;
	bool success = (index >= 0) && (index < size);
	if (success)
		return items[index];
	else
		return p;
}

// check if the list is empty
bool List::isEmpty() { return size == 0; }

// check the size of the list
int List::getLength() { return size; }



// display the items in the list
void List::print()
{

	for (int pos = 0; pos < size; pos++) {
		tm date = items[pos].getCheckOut();
		// Convert tm type to string in (dd/mm/yyyy) format
		string dateStr = "";
		// Append year, month and day in human readable format
		dateStr = to_string(date.tm_mday) + "/" + to_string(date.tm_mon + 1) + "/" + to_string(date.tm_year + 1900);
		// If hour and minute is found, append hour and minute
		if (date.tm_hour != NULL && date.tm_min != NULL) {
			dateStr += " " + to_string(date.tm_hour) + ":" + to_string(date.tm_min);
		}
		cout << "[" << pos + 1 << "] " 
			<< "  Name: " << items[pos].getGuestName() 
			<< "  Room Type: " << items[pos].getRoom().getType() 
			<< "  Check Out Date: " << dateStr << endl;
	}
}

// replace the  item in the specified index in the list
void List::replace(int index, ItemType item)
{
	items[index] = item;
}

// to find specified person's name
int List::findName(string target) {
	int p =-1;
	if (size > 0) {
		for (int pos = 0; pos < size; pos++) {
			if (items[pos].getGuestName() == target) {
				return pos;
			}
		}
		return p;
	}
	else {
		return p;
	}
}