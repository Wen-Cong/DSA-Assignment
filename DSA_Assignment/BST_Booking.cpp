//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
// BST_Booking.cpp - Implementation of Binary Search Tree
// Bookings status that are only booked are stored in this BST
// When bookings status change from booked to checkin the record will
// be removed from this tree and inserted into the BST_Checkin tree
#include "BST_Booking.h"
#include <time.h>
#define max(x,y) ((x > y)? x : y)

// constructor
BST_Booking::BST_Booking()
{
	root = NULL;
}

// search an item in the binary search tree
BinaryNode* BST_Booking::search(ItemType target)
{
	return search(root, target);
}

BinaryNode* BST_Booking::search(BinaryNode* t, ItemType target)
{
	if (t == NULL)	// item not found
		return NULL;
	else
	{
		if ((t->item.getCheckIn().tm_year == target.getCheckIn().tm_year)
			&& (t->item.getCheckIn().tm_mon == target.getCheckIn().tm_mon)
			&& (t->item.getCheckIn().tm_mday == target.getCheckIn().tm_mday))		// item found
			return t;
		else
		{
			//Comparing time the year have to be the no. of years different from 1900
			tm compare = t->item.getCheckIn();
			tm temp = target.getCheckIn();
			//if difftime > 1 temp is earlier
			if (difftime(mktime(&compare), mktime(&temp)) > 0)
				return search(t->left, target);
			else					// search in right subtree
				return search(t->right, target);
		}
	}
}

// //search for range of items in the binary search tree and return count
//int BST_Booking::searchRange(tm checkin, tm checkout, string roomType)
//{
//	return searchRange(root, checkin, checkout, roomType);
//}

//int BST_Booking::searchRange(BinaryNode* root, tm checkin, tm checkout, string roomType)
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

void BST_Booking::overlapSearch(Booking b, BST_Booking& bookingList)
{
	return overlapSearch(root, b, bookingList);
}

void BST_Booking::overlapSearch(BinaryNode* root, Booking b, BST_Booking& bookingList)
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
// Check if given two booking have overlapping check-in and check-out date range
bool isOverlapped(ItemType b1, tm b2In, tm b2Out)
{
	tm b1In = b1.getCheckIn();
	tm b1Out = b1.getCheckOut();

	if ((difftime(mktime(&b1In), mktime(&b2Out)) < 0) &&
		(difftime(mktime(&b2In), mktime(&b1Out)) < 0))
		return true;
	return false;
}

void BST_Booking::overlapSearch(tm checkIn,tm checkOut, BST_Booking& bookingList, bool isBooked)
{
	return overlapSearch( root, checkIn,  checkOut, bookingList, isBooked);
}

void BST_Booking::overlapSearch(BinaryNode* root, tm checkIn, tm checkOut, BST_Booking& bookingList,bool isBooked)
{
	// Base Case
	if (root == NULL)
		return;

	bool matchedQuery = isOverlapped(root->item, checkIn,checkOut);

	if (matchedQuery) {
		//if booked == true search for only status that are booked
		if (isBooked) {
			if (root->item.getStatus() == "Booked") {
				bookingList.insert(root->item);
			}
		}
		else {
			//Add to the list those bookings status != "Booked"
			if (root->item.getStatus() != "Booked") {
				bookingList.insert(root->item);
			}
			
		}		
	}

	// If left child of root is present and max of left child is
	// greater than check in time of check in, 
	// then there are some rooms occupied during the given check in and check out time
	if (root->left != NULL && difftime(mktime(&root->left->max), mktime(&checkIn)) > 0)
		overlapSearch(root->left, checkIn, checkOut, bookingList, isBooked);

	// If right child of root is present and min of right child is
	// lesser than check out time of check out, 
	// then there are some rooms occupied during the given check in and check out time
	if (root->right != NULL && difftime(mktime(&root->right->min), mktime(&checkOut)) < 0)
		overlapSearch(root->right, checkIn, checkOut, bookingList, isBooked);

	return;
}

// insert an item to the binary search tree
void BST_Booking::insert(ItemType item)
{
	insert(root, item);
}

void BST_Booking::insert(BinaryNode*& t, ItemType item)
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
void BST_Booking::inorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		inorder(root);
}
string BST_Booking::fromDateTime(tm date) {
	// Convert tm type to string in (dd/mm/yyyy) format
	string dateStr = "";
	// Append year, month and day in human readable format
	dateStr = to_string(date.tm_mday) + "/" + to_string(date.tm_mon + 1) + "/" + to_string(date.tm_year + 1900);
	// If hour and minute is found, append hour and minute
	if (date.tm_hour != NULL && date.tm_min != NULL) {
		dateStr += " " + to_string(date.tm_hour) + ":" + to_string(date.tm_min);
	}

	return dateStr;
}
void BST_Booking::inorder(BinaryNode* t)
{
	if (t != NULL)
	{
		cout << "L" << endl;
		inorder(t->left);
		cout << "M" << endl;
		cout << "Min " << fromDateTime(t->min) << " Max" << fromDateTime(t->max) << endl;
		t->item.print();
		cout << "R" << endl;
		inorder(t->right);
	}
}
// traverse the binary search tree in inorder
void BST_Booking::printOption(int& index)
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		return printOption(root,index);
}
// print option
void BST_Booking::printOption(BinaryNode* t, int& index) {
	if (t != NULL) {
		printOption(t->left, index);
		index++;
		tm date = t->item.getCheckOut();
		// Convert tm type to string in (dd/mm/yyyy) format
		string dateStr = "";
		// Append year, month and day in human readable format
		dateStr = to_string(date.tm_mday) + "/" + to_string(date.tm_mon + 1) + "/" + to_string(date.tm_year + 1900);
		// If hour and minute is found, append hour and minute
		if (date.tm_hour != NULL && date.tm_min != NULL) {
			dateStr += " " + to_string(date.tm_hour) + ":" + to_string(date.tm_min);
		}
		cout << "[" << index << "] "
			<< "Name: " << t->item.getGuestName()
			<< "  Room Type: " << t->item.getRoom().getType()
			<< "  Check Out Date: " << dateStr << endl;
		printOption(t->right, index);
		return;
	}
}
//get booking
void BST_Booking::getBooking(Booking& b ,int index) {
	if (isEmpty()) {
		cout << "No items found" << endl;
	}
	else
	{
		int count = 0;
		return getBooking(root, b, index , count);}
}
void BST_Booking::getBooking(BinaryNode* t, Booking& b, int index, int& count) {
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
//get booking
void BST_Booking::updateBooking(Booking b) {
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
void BST_Booking::updateBooking(BinaryNode* t, tm checkIn, tm checkOut, Booking b) {
	// Base Case
	if (t == NULL)
		return;

	bool matchedQuery = isOverlapped(t->item, checkIn, checkOut);

	if (matchedQuery) {
		//if booked == true search for only status that are booked
		if (t->item.getId() == b.getId()) {
			t->item = b;
		}
	}

	// If left child of root is present and max of left child is
	// greater than check in time of check in, 
	// then there are some rooms occupied during the given check in and check out time
	if (t->left != NULL && difftime(mktime(&t->left->max), mktime(&checkIn)) > 0)
		updateBooking(t->left, checkIn, checkOut,b);

	// If right child of root is present and min of right child is
	// lesser than check out time of check out, 
	// then there are some rooms occupied during the given check in and check out time
	if (t->right != NULL && difftime(mktime(&t->right->min), mktime(&checkOut)) < 0)
		updateBooking(t->right, checkIn, checkOut, b);
	return;
}

////Transfer to list for display
//void BST_Booking::transferList(List& displayList) {
//	return transferList( root, displayList);
//}
//void BST_Booking::transferList(BinaryNode* t,List& displayList) {
//	if (t != NULL) {
//		transferList(t->left, displayList);
//		displayList.add(t->item);
//		transferList(t->right,displayList);
//	}
//	return;
//}

//Transfer to list for display
int BST_Booking::availRoomList(List& aRoomList, string type) {
	List temp = List();
	availRoomList(root, temp, type);
for (int i = 0; i < aRoomList.getLength(); i++) {
		if (!temp.exists(aRoomList.get(i))) {
			return aRoomList.get(i);
		}
	}
	
	return -1;
}
void BST_Booking::availRoomList(BinaryNode* t, List& aRoomList, string type) {
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

// traverse the binary search tree in preorder
void BST_Booking::preorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		preorder(root);
}

void BST_Booking::preorder(BinaryNode* t)
{
	if (t != NULL)
	{
		t->item.print();
		preorder(t->left);
		preorder(t->right);
	}
}

// traverse the binary search tree in postorder
void BST_Booking::postorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		postorder(root);
}

void BST_Booking::postorder(BinaryNode* t)
{
	if (t != NULL)
	{
		postorder(t->left);
		postorder(t->right);
		t->item.print();
	}
}

// check if the binary search tree is empty
bool BST_Booking::isEmpty()
{
	return (root == NULL);
}

// count the number of roots in the binary search tree
int BST_Booking::countNodes()
{
	return countNodes(root);
}

int BST_Booking::countNodes(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + countNodes(t->left) + countNodes(t->right);
}

// compute the height of the binary search tree
int BST_Booking::getHeight()
{
	return getHeight(root);
}

int BST_Booking::getHeight(BinaryNode* t)
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
bool BST_Booking::isBalanced()
{
	return isBalanced(root);
}

bool BST_Booking::isBalanced(BinaryNode* t)
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
void BST_Booking::remove(ItemType target)
{
	remove(root, target);
	balanceTree(root);			// AVL Tree function
}



void BST_Booking::remove(BinaryNode*& t, ItemType item)
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