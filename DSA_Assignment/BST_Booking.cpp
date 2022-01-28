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
			if (//Check if target year is smaller than root's target year
				(t->item.getCheckIn().tm_year > target.getCheckIn().tm_year) ||
				//In case both are in the same year, check month
				((t->item.getCheckIn().tm_year == target.getCheckIn().tm_year)
					&& (t->item.getCheckIn().tm_mon > target.getCheckIn().tm_mon)) ||
				//In case both are in the same year and month, check day
				((t->item.getCheckIn().tm_year == target.getCheckIn().tm_year)
					&& (t->item.getCheckIn().tm_mon == target.getCheckIn().tm_mon)
					&& (t->item.getCheckIn().tm_mday > target.getCheckIn().tm_mday))
				)	// search in left subtree
				return search(t->left, target);
			else					// search in right subtree
				return search(t->right, target);
	}
}

// search for range of items in the binary search tree and return count
int BST_Booking::searchRange(tm checkin, tm checkout, string roomType)
{
	return searchRange(root, checkin, checkout, roomType);
}

int BST_Booking::searchRange(BinaryNode* root, tm checkin, tm checkout, string roomType)
{
	if (root == NULL)
	{
		//base case: the tree is empty, we can return 0
		return 0;
	}
	else
	{
		// our tree is not empty.
		int countLeftOccupiedRooms = searchRange(root->left, checkin, checkout, roomType);
		int countRightOccupiedRooms = searchRange(root->right, checkin, checkout, roomType);

		// Get and format all time data for comparison
		tm bookingCheckIn = root->item.getCheckIn();
		tm bookingCheckOut = root->item.getCheckOut();
		tm tempCheckIn = checkin;
		tm tempCheckOut = checkout;
		//Comparing time the year have to be the no. of years different from 1900
		bookingCheckIn.tm_year -= 1900;
		bookingCheckOut.tm_year -= 1900;
		tempCheckIn.tm_year -= 1900;
		tempCheckOut.tm_year -= 1900;

		// Set condition to determine if room is occupied or booked
		/*Checkout date for bookings that are currently in checked in status
		  is more than check in date entered by customer. Hence, room is unavailable*/
		bool isRoomOccupied = root->item.getStatus() == "Checked In" 
						   && root->item.getRoom().getType() == roomType
						   && difftime(mktime(&bookingCheckOut), mktime(&tempCheckIn)) > 0; // booking check out date is more than check in date entered by customer
		

		/*If booking check-in date or booking check-out date is within date range input by user
		and status is booked, then room is unavailable.*/
		bool isRoomBooked = root->item.getStatus() == "Booked"
			&& root->item.getRoom().getType() == roomType
			&& (
				(difftime(mktime(&bookingCheckIn), mktime(&tempCheckIn)) >= 0 // booking check in date is more than check in date entered by customer
					&& difftime(mktime(&bookingCheckIn), mktime(&tempCheckOut)) < 0) // booking check in date is less than check out date entered by customer
				|| (difftime(mktime(&bookingCheckOut), mktime(&tempCheckIn)) > 0 // booking check out date is more than check in date entered by customer
					&& difftime(mktime(&bookingCheckOut), mktime(&tempCheckOut)) <= 0)); // booking check out date is less than check out date entered by customer

		if (isRoomOccupied || isRoomBooked)
		{
			/* 1 more room of this room type is unavailable based on the date range given: we will count it */
			return 1 + countLeftOccupiedRooms + countRightOccupiedRooms;
		}
		else
		{
			return countLeftOccupiedRooms + countRightOccupiedRooms;
		}
	}
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
		t = newroot;
	}
	else {

		//Comparing time the year have to be the no. of years different from 1900
		tm compare = t->item.getCheckIn();
		compare.tm_year -= 1900;
		tm temp = item.getCheckIn();
		temp.tm_year -= 1900;
		//if difftime > 0, temp is earlier
		if (difftime(mktime(&compare), mktime(&temp)) > 0)
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

void BST_Booking::inorder(BinaryNode* t)
{
	if (t != NULL)
	{
		inorder(t->left);
		cout << t->item.getId() << endl;
		inorder(t->right);
	}
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
		cout << t->item.getId() << endl;
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
		cout << t->item.getId() << endl;
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
		compare.tm_year -= 1900;
		tm temp = item.getCheckIn();
		temp.tm_year -= 1900;
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
				t->item = item;						// replace the root�s item with that of the successor
			}
		}
	}
}