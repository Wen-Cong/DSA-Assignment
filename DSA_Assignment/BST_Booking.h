//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
// BST_Booking Interval tree
// Bookings stored in this Interval tree are sorted by check in date

#pragma once
#include<iostream>
using namespace std;
#include "BinaryNode.h"
#include "AVL_Tree.h" // AVL Tree functions
#include "List.h"
#include "BST_OccupiedBooking.h"
#include "Dictionary_Price.h"

typedef Booking ItemType;
class BST_Booking
{
private:
	BinaryNode* root;		// root of the BST

public:

	// constructor
	BST_Booking();

	

	// Search for overlapping check in and check out dates for bookings
	// pre : none
	// post: none
	void overlapSearch(Booking b, BST_Booking& bookingList);
	void overlapSearch(BinaryNode* root, Booking b, BST_Booking& bookingList);

	// Overlapping search with check in and check out dates for bookings To include only "Booked" or exclude "Booked" or all status
	// pre : none
	// post: none
	void overlapSearch(tm checkIn, tm checkOut, BST_Booking& bookingList, string isBooked);
	void overlapSearch(BinaryNode* root, tm checkIn, tm checkOut, BST_Booking& bookingList, string isBooked);

	// Overlapping search with check in and check out dates for bookings with status of Checked In or Checked Out
	// pre : none
	// post: none
	void overlapSearch(tm checkIn, tm checkOut, BST_OccupiedBooking& bookingList);
	void overlapSearch(BinaryNode* root, tm checkIn, tm checkOut, BST_OccupiedBooking& bookingList);

	// insert an item to the Interval tree
	// pre : none
	// post: item is added into the Interval tree
	void insert(ItemType item);
	void insert(BinaryNode*& root, ItemType item);

	// delete an item from the Interval tree
	// pre: none
	// post: item is removed from the interval tree
	void remove(ItemType target);
	void remove(BinaryNode*& root, ItemType target);

	// traverse the Interval tree in inorder
	// pre : none
	// post: none
	void inorder();
	void inorder(BinaryNode* t);

	// traverse the Interval tree in preorder
	// pre : none
	// post: none
	void preorder();
	void preorder(BinaryNode* t);

	// traverse the Interval tree in postorder
	// pre : none
	// post: none
	void postorder();
	void postorder(BinaryNode* t);

	// check if the Interval tree is empty
	// pre : none
	// post: none
	// return true if the tree is empty else false.
	bool isEmpty();

	// count the number of nodes in the interval tree
	// pre : none
	// post: none
	// return the number of node in the interval tree
	int countNodes();
	int countNodes(BinaryNode* t);

	// compute the height of the interval tree
	// pre: none
	// post: none
	int getHeight();
	int getHeight(BinaryNode* t);

	// check if the binary search tree is balanced
	// pre: none
	// post: none
	// return true if the tree is balance else false.
	bool isBalanced();
	bool isBalanced(BinaryNode* t);
	
	//Find the first available room number
	// pre : none
	// post: none
	// return the first available room number
	int availRoomList(List& aRoomList, string type);
	void availRoomList(BinaryNode* t, List& aRoomList, string type);

	// Print the option number and relevant booking details
	// pre : none
	// post: none
	void printOption(int& index);
	void printOption(BinaryNode* t, int& index);

	// Get the booking with the selected index
	// pre : none
	// post: none
	void getBooking(Booking& b, int index);
	void getBooking(BinaryNode* t, Booking& b, int index, int& count);

	// Update the booking in the list with the updated details
	// pre : none
	// post: none
	void updateBooking(Booking b);
	void updateBooking(BinaryNode* t, tm checkIn, tm checkOut, Booking b);

	// Count the number room for each room type
	// pre : none
	// post: none
	void searchHighestRoomTypeCount(string& roomType, int& count);
	void searchHighestRoomTypeCount(BinaryNode* t, Dictionary_Price& roomTypes);

	// Print relevant booking information
	// pre : none
	// post: none
	void printDetails();
	void printDetails(BinaryNode* t);

	//Code Used in debugging to convert tm struct into string
	/*string fromDateTime(tm date);*/
	
	//Codes that were not used
	//// search an item in the binary search tree
	//// pre : none
	//// post: none
	//// return item else return null.
	//BinaryNode* search(ItemType target);
	//BinaryNode* search(BinaryNode* root, ItemType target);

	//// search for range of items in the binary search tree and return count
	//int searchRange(tm checkin, tm checkout, string roomType);
	//int searchRange(BinaryNode* root, tm checkin, tm checkout, string roomType);
};

