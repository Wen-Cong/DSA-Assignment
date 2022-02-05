//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
// IT_Booking.cpp - Implementation of Interval Tree
// Bookings stored in this IT are sorted by check in date
#pragma once

#include "IT_Booking.h"
#include <time.h>
#define max(x,y) ((x > y)? x : y)

// constructor
IT_Booking::IT_Booking()
{
	root = NULL;
}


// Check if given two booking have overlapping check-in and check-out date range
bool isOverlapped(ItemType b1, ItemType b2)
{
	tm b1In = b1.getCheckIn();
	tm b1Out = b1.getCheckOut();
	tm b2In = b2.getCheckIn();
	tm b2Out = b2.getCheckOut();

	if ((difftime(mktime(&b1In), mktime(&b2Out)) < 0) &&
		(difftime(mktime(&b2In), mktime(&b1Out)) < 0))
		return true;
	return false;
}

// Check if given two booking have overlapping check-in and check-out date range
bool isOverlapped(ItemType b1, tm b2In, tm b2Out)
{
	tm b1In = b1.getCheckIn();
	tm b1Out = b1.getCheckOut();
	//Check if target end date is later than or equals to the checkin date
	if ((difftime(mktime(&b1In), mktime(&b2Out)) <= 0) &&
		// Check if the target start date is earlier than or equals to the checkout date
		(difftime(mktime(&b2In), mktime(&b1Out)) <= 0))
		return true;
	return false;
}

void IT_Booking::overlapSearch(Booking b, IT_Booking& bookingList)
{
	return overlapSearch(root, b, bookingList);
}

void IT_Booking::overlapSearch(BinaryNode* root, Booking b, IT_Booking& bookingList)
{
	// Base Case
	if (root == NULL)
		return;
	bool matchedQuery = false;
	// If given booking check in and check out date overlaps with root check in and check out date for the room type
	matchedQuery = isOverlapped(root->item, b) &&
	b.getRoom().getType() == root->item.getRoom().getType() &&
	root->item.getStatus() != "Checked Out";

	if (matchedQuery) {
		bookingList.insert(root->item);
	}

	tm bookingCheckIn = b.getCheckIn();
	tm bookingCheckOut = b.getCheckOut();

	// If left child of root is present and max of left child is
	// greater than check in time of given booking, 
	// then there are some rooms occupied during the given check in and check out time
	if (root->left != NULL && difftime(mktime(&root->left->max), mktime(&bookingCheckIn)) > 0)
		overlapSearch(root->left, b, bookingList);

	// If right child of root is present and min of right child is
	// lesser than check out time of given booking, 
	// then there are some rooms occupied during the given check in and check out time
	if (root->right != NULL && difftime(mktime(&root->right->min), mktime(&bookingCheckOut)) < 0)
		overlapSearch(root->right, b, bookingList);
	return;
}


void IT_Booking::overlapSearch(tm checkIn, tm checkOut, IT_Booking& bookingList, string isBooked)
{
	return overlapSearch(root, checkIn, checkOut, bookingList, isBooked);
}

void IT_Booking::overlapSearch(BinaryNode* root, tm checkIn, tm checkOut, IT_Booking& bookingList, string isBooked)
{
	// Base Case
	if (root == NULL)
		return;
	// If left child of root is present and max of left child is
	// greater than check in time of check in, 
	// then there are some rooms occupied during the given check in and check out time
	if (root->left != NULL && difftime(mktime(&root->left->max), mktime(&checkIn)) >= 0)
		overlapSearch(root->left, checkIn, checkOut, bookingList, isBooked);
	bool matchedQuery = isOverlapped(root->item, checkIn, checkOut);

	if (matchedQuery) {
		if (isBooked == "All") {
			//Insert into the list those that are not booked
			bookingList.insert(root->item);
		}
		else if (isBooked == "True")//if booked == "True" search for only status that are booked
		 {
			if (root->item.getStatus() == "Booked") {
				bookingList.insert(root->item);
			}
		}
		// if isbooked = "False" search for only status that are not booked
		else if (isBooked == "False") {
			if (root->item.getStatus() != "Booked") {
				bookingList.insert(root->item);
			}
		}
		else {
			//Insert into the list those that are not booked
			bookingList.insert(root->item);
		}
	}
	// If right child of root is present and min of right child is
	// lesser than check out time of check out, 
	// then there are some rooms occupied during the given check in and check out time
	if (root->right != NULL && difftime(mktime(&root->right->min), mktime(&checkOut)) <= 0)
		overlapSearch(root->right, checkIn, checkOut, bookingList, isBooked);

	return;
}

void IT_Booking::overlapSearch(tm checkIn, tm checkOut, BST_OccupiedBooking& bookingList)
{
	return overlapSearch(root, checkIn, checkOut, bookingList);
}

void IT_Booking::overlapSearch(BinaryNode* root, tm checkIn, tm checkOut, BST_OccupiedBooking& bookingList)
{
	// Base Case
	if (root == NULL)
		return;

	bool matchedQuery = isOverlapped(root->item, checkIn, checkOut);

	if (matchedQuery && root->item.getStatus() != "Booked") {
		// Insert only for bookings with status that are Checked In or Checked Out
		bookingList.insert(root->item);
	}

	// If left child of root is present and max of left child is
	// greater than check in time of check in, 
	// then there are some rooms occupied during the given check in and check out time
	if (root->left != NULL && difftime(mktime(&root->left->max), mktime(&checkIn)) > 0)
		overlapSearch(root->left, checkIn, checkOut, bookingList);

	// If right child of root is present and min of right child is
	// lesser than check out time of check out, 
	// then there are some rooms occupied during the given check in and check out time
	if (root->right != NULL && difftime(mktime(&root->right->min), mktime(&checkOut)) < 0)
		overlapSearch(root->right, checkIn, checkOut, bookingList);

	return;
}

// insert an item to the binary search tree
void IT_Booking::insert(ItemType item)
{
	insert(root, item);
}

void IT_Booking::insert(BinaryNode*& t, ItemType item)
{
	if (t == NULL)
	{
		BinaryNode* newroot = new BinaryNode;
		newroot->item = item;
		newroot->left = NULL;
		newroot->right = NULL;
		newroot->min = item.getCheckIn();
		newroot->max = item.getCheckOut();
		t = newroot;
	}
	else {
		//Comparing time the year have to be the no. of years different from 1900
		tm compareIn = t->item.getCheckIn();
		tm compareMax = t->max;
		tm compareMin = t->min;
		tm tempIn = item.getCheckIn();
		tm tempOut = item.getCheckOut();

		// Update the max value of this ancestor if needed
		if (difftime(mktime(&tempOut), mktime(&compareMax)) > 0)
			t->max = item.getCheckOut();

		// Update the min value of this ancestor if needed
		if (difftime(mktime(&compareMin), mktime(&tempIn)) > 0)
			t->min = item.getCheckIn();

		//if difftime > 0, temp is earlier
		if (difftime(mktime(&compareIn), mktime(&tempIn)) > 0)
			insert(t->left, item);  // insert in left subtree
		else
			insert(t->right, item); // insert in right subtree	

	}

	t = balance(t);				// balance the tree (AVL Tree function)
}


// traverse the binary search tree in inorder
void IT_Booking::inorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		inorder(root);
}



void IT_Booking::inorder(BinaryNode* t)
{
	if (t != NULL)
	{
		//Note: couts are used to debug interval tree to check if the tree is balanced
		//cout << "L" << endl;
		inorder(t->left);
		//cout << "M" << endl;
		//cout << "Min " << fromDateTime(t->min) << "\tMax " << fromDateTime(t->max) << endl;
		t->item.print();
		//cout << "R" << endl;
		inorder(t->right);
	}
}


// traverse the binary search tree in preorder
void IT_Booking::preorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		preorder(root);
}

void IT_Booking::preorder(BinaryNode* t)
{
	if (t != NULL)
	{
		t->item.print();
		preorder(t->left);
		preorder(t->right);
	}
}

// traverse the binary search tree in postorder
void IT_Booking::postorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		postorder(root);
}

void IT_Booking::postorder(BinaryNode* t)
{
	if (t != NULL)
	{
		postorder(t->left);
		postorder(t->right);
		t->item.print();
	}
}

// check if the binary search tree is empty
bool IT_Booking::isEmpty()
{
	return (root == NULL);
}

// count the number of roots in the binary search tree
int IT_Booking::countNodes()
{
	return countNodes(root);
}

int IT_Booking::countNodes(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + countNodes(t->left) + countNodes(t->right);
}

// compute the height of the binary search tree
int IT_Booking::getHeight()
{
	return getHeight(root);
}

int IT_Booking::getHeight(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
	{
		// return 1 + max(getHeight(t->left), getHeight(t->right));
		int leftHeight = getHeight(t->left);
		int rightHeight = getHeight(t->right);
		return 1 + max(leftHeight, rightHeight);
	}
}

// check if the binary search tree is balanced
bool IT_Booking::isBalanced()
{
	return isBalanced(root);
}

bool IT_Booking::isBalanced(BinaryNode* t)
{
	if (t == NULL)
		return true;
	else
	{
		int leftHeight = getHeight(t->left);	// height of left sub-tree
		int rightHeight = getHeight(t->right);	// height of right sub-tree
		bool isBalancedroot = (abs(leftHeight - rightHeight) <= 1);
		bool isBalancedLeft = isBalanced(t->left);
		bool isBalancedRight = isBalanced(t->right);
		return (isBalancedroot && isBalancedLeft && isBalancedRight);
	}
}

// delete an item from the binary search tree
void IT_Booking::remove(ItemType target)
{
	remove(root, target);
	balanceTree(root);			// AVL Tree function
}



void IT_Booking::remove(BinaryNode*& t, ItemType item)
{
	if (t != NULL)
	{
		//Comparing time the year have to be the no. of years different from 1900
		tm compare = t->item.getCheckIn();
		tm temp = item.getCheckIn();
		//if difftime > 1 temp is earlier
		if (difftime(mktime(&compare), mktime(&temp)) > 0)		// search in left subtree
			remove(t->left, item);
		else if (difftime(mktime(&compare), mktime(&temp)) < 0)	// search in right subtree
			remove(t->right, item);
		else						// item == t->item (found) - base case
		{
			if (t->left == NULL && t->right == NULL) // case 1 : root has 0 child
			{
				BinaryNode* temp = t;	// to be deleted
				t = NULL;
				delete temp;			// delete the root
			}
			else if (t->left == NULL)	// case 2 : root has 1 child
			{
				BinaryNode* temp = t;	// root to be deleted

				if (t == root)			// current root is root
					root = t->right;
				else
					t = t->right;

				delete temp;			// delete the root
			}
			else if (t->right == NULL)	// case 2 : root has 1 child
			{
				BinaryNode* temp = t;	// root to be deleted

				if (t == root)			// current root is root
					root = t->left;
				else
					t = t->left;

				delete temp;			// delete the root
			}
			else // case 3 : root has 2 children
			{
				BinaryNode* successor = t->left;
				while (successor->right != NULL)	// search for right most root in left sub-tree
					successor = successor->right;

				ItemType item = successor->item;
				remove(t->left, item);				// delete the successor (either case 1 or case 2)
				t->item = item;						// replace the root’s item with that of the successor
			}
		}
	}
}
//Find the first available room number.
int IT_Booking::availRoomList(List& aRoomList, string type) {
	List temp = List();
	availRoomList(root, temp, type);
	for (int i = 0; i < aRoomList.getLength(); i++) {
		if (!temp.exists(aRoomList.get(i))) {
			return aRoomList.get(i);
		}
	}
	
	return -1;
}
void IT_Booking::availRoomList(BinaryNode* t, List& aRoomList, string type) {
	if (t != NULL) {
		availRoomList(t->left, aRoomList, type);
		if (t->item.getRoom().getType() == type) {
			
			if (!aRoomList.exists(t->item.getRoom().getRoomNum())) {
				aRoomList.add(t->item.getRoom().getRoomNum());
			}				
		}		
		availRoomList(t->right, aRoomList,type);
	}
	return;
}

// print the option number and relevant booking details
void IT_Booking::printOption(int& index)
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		return printOption(root,index);
}
// print option
void IT_Booking::printOption(BinaryNode* t, int& index) {
	if (t != NULL) {
		printOption(t->left, index);
		index++;
		cout << "[" << index << "] "
			<< "Booking ID: "<< t-> item.getId()
			<< "  Name: " << t->item.getGuestName()
			<< "  Room Type: " << t->item.getRoom().getType()
			<< endl;
		printOption(t->right, index);
		return;
	}
}

//get booking witht the selected index
void IT_Booking::getBooking(Booking& b ,int index) {
	if (isEmpty()) {
		cout << "No items found" << endl;
	}
	else
	{
		int count = 0;
		return getBooking(root, b, index , count);
	}
}

void IT_Booking::getBooking(BinaryNode* t, Booking& b, int index, int& count) {
	if (t != NULL) {
		getBooking(t->left, b, index, count);
		count++;
		if (count == index) {
			b = t->item;
		}
		getBooking(t->right, b, index, count);
		return;
	}
}
// update booking details
void IT_Booking::updateBooking(Booking b) {
	if (isEmpty()) {
		cout << "No items found" << endl;
	}
	else
	{
		tm checkin = b.getCheckIn();
		tm checkout = checkin;
		checkout.tm_mday++;
		int count = 0;
		return updateBooking(root, checkin, checkout, b);
	}
}
void IT_Booking::updateBooking(BinaryNode* t, tm checkIn, tm checkOut, Booking b) {
	// Base Case
	if (t == NULL)
		return;

	bool matchedQuery = isOverlapped(t->item, checkIn, checkOut);

	if (matchedQuery) {
		if (t->item.getId() == b.getId()) {
			t->item = b;
		}
	}

	// If left child of root is present and max of left child is
	// greater than or equals check in time of check in, 
	// then there are some rooms occupied during the given check in and check out time
	if (t->left != NULL && difftime(mktime(&t->left->max), mktime(&checkIn)) >= 0)
		updateBooking(t->left, checkIn, checkOut,b);

	// If right child of root is present and min of right child is
	// lesser than or equals check out time of check out, 
	// then there are some rooms occupied during the given check in and check out time
	if (t->right != NULL && difftime(mktime(&t->right->min), mktime(&checkOut)) <= 0)
		updateBooking(t->right, checkIn, checkOut, b);
	return;
}

void IT_Booking::searchHighestRoomTypeCount(string& roomType, int& count)
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
	{
		Dictionary_Price roomTypes = Dictionary_Price();
		searchHighestRoomTypeCount(root, roomTypes);
		roomTypes.getHighestCount(roomType, count);
	}
}

void IT_Booking::searchHighestRoomTypeCount(BinaryNode* t, Dictionary_Price& roomTypes)
{
	if (t != NULL)
	{
		PriceRoomType rt = roomTypes.get(t->item.getRoom().getType());
		if (rt.count < 0) { // Room Type has not been seen yet
			// If room type is not seen before, set default count value as 1 since this is the first item of this room type
			rt.count = 1;
		}
		// Add room type to room type list if duplicate is found, function will add 1 to count number of duplication
		roomTypes.add(t->item.getRoom().getType(), rt);
		searchHighestRoomTypeCount(t->left, roomTypes);
		searchHighestRoomTypeCount(t->right, roomTypes);
		return;
	}
}
void IT_Booking::printDetails() {
	printDetails(root);
}
void IT_Booking::printDetails(BinaryNode* t) {
	if (t != NULL) {
		printDetails(t->left);
		cout << endl;
		cout << "Booking ID: " << t->item.getId() << endl;
		cout << "Guest Name: " << t->item.getGuestName() << endl;
		cout << "Status: " << t->item.getStatus() << endl;
		cout << "Room Type: " << t->item.getRoom().getType() << endl;
		cout << "Room Number: " << t->item.getRoom().getRoomNum() << endl;
		cout << "Check In Date: " << to_string(t->item.getCheckIn().tm_mday) + "/" + to_string(t->item.getCheckIn().tm_mon + 1) + "/" + to_string(t->item.getCheckIn().tm_year + 1900) << endl;
		cout << "Check Out Date: " << to_string(t->item.getCheckOut().tm_mday) + "/" + to_string(t->item.getCheckOut().tm_mon + 1) + "/" + to_string(t->item.getCheckOut().tm_year + 1900) << endl;
		printDetails(t->right);
	}
}
//Code Used in debugging to convert tm struct into string
//string IT_Booking::fromDateTime(tm date) {
//	// Convert tm type to string in (dd/mm/yyyy) format
//	string dateStr = "";
//	// Append year, month and day in human readable format
//	dateStr = to_string(date.tm_mday) + "/" + to_string(date.tm_mon + 1) + "/" + to_string(date.tm_year + 1900);
//	// If hour and minute is found, append hour and minute
//	if (date.tm_hour != NULL && date.tm_min != NULL) {
//		dateStr += " " + to_string(date.tm_hour) + ":" + to_string(date.tm_min);
//	}
//
//	return dateStr;
//}
// 
// Codes not in use
//// search an item in the binary search tree
//BinaryNode* IT_Booking::search(ItemType target)
//{
//	return search(root, target);
//}
//
//BinaryNode* IT_Booking::search(BinaryNode* t, ItemType target)
//{
//	if (t == NULL)	// item not found
//		return NULL;
//	else
//	{
//		if ((t->item.getCheckIn().tm_year == target.getCheckIn().tm_year)
//			&& (t->item.getCheckIn().tm_mon == target.getCheckIn().tm_mon)
//			&& (t->item.getCheckIn().tm_mday == target.getCheckIn().tm_mday))		// item found
//			return t;
//		else
//		{
//			//Comparing time the year have to be the no. of years different from 1900
//			tm compare = t->item.getCheckIn();
//			tm temp = target.getCheckIn();
//			//if difftime > 1 temp is earlier
//			if (difftime(mktime(&compare), mktime(&temp)) > 0)
//				return search(t->left, target);
//			else					// search in right subtree
//				return search(t->right, target);
//		}
//	}
//}

// //search for range of items in the binary search tree and return count
//int IT_Booking::searchRange(tm checkin, tm checkout, string roomType)
//{
//	return searchRange(root, checkin, checkout, roomType);
//}

//int IT_Booking::searchRange(BinaryNode* root, tm checkin, tm checkout, string roomType)
//{
//	if (root == NULL)
//	{
//		//base case: the tree is empty, we can return 0
//		return 0;
//	}
//	else
//	{
//		// our tree is not empty.
//		int countLeftOccupiedRooms = searchRange(root->left, checkin, checkout, roomType);
//		int countRightOccupiedRooms = searchRange(root->right, checkin, checkout, roomType);
//
//		// Get and format all time data for comparison
//		tm bookingCheckIn = root->item.getCheckIn();
//		tm bookingCheckOut = root->item.getCheckOut();
//		tm tempCheckIn = checkin;
//		tm tempCheckOut = checkout;
//
//		// Set condition to determine if room is occupied or booked
//		/*Checkout date for bookings that are currently in checked in status
//		  is more than check in date entered by customer. Hence, room is unavailable*/
//		bool isRoomOccupied = root->item.getStatus() == "Checked In" 
//						   && root->item.getRoom().getType() == roomType
//						   && difftime(mktime(&bookingCheckOut), mktime(&tempCheckIn)) > 0; // booking check out date is more than check in date entered by customer
//		
//
//		/*If booking check-in date or booking check-out date is within date range input by user
//		and status is booked, then room is unavailable.*/
//		bool isRoomBooked = root->item.getStatus() == "Booked"
//			&& root->item.getRoom().getType() == roomType
//			&& (
//				(difftime(mktime(&bookingCheckIn), mktime(&tempCheckIn)) >= 0 // booking check in date is more than check in date entered by customer
//					&& difftime(mktime(&bookingCheckIn), mktime(&tempCheckOut)) < 0) // booking check in date is less than check out date entered by customer
//				|| (difftime(mktime(&bookingCheckOut), mktime(&tempCheckIn)) > 0 // booking check out date is more than check in date entered by customer
//					&& difftime(mktime(&bookingCheckOut), mktime(&tempCheckOut)) <= 0)); // booking check out date is less than check out date entered by customer
//
//		if (isRoomOccupied || isRoomBooked)
//		{
//			/* 1 more room of this room type is unavailable based on the date range given: we will count it */
//			return 1 + countLeftOccupiedRooms + countRightOccupiedRooms;
//		}
//		else
//		{
//			return countLeftOccupiedRooms + countRightOccupiedRooms;
//		}
//	}
//}