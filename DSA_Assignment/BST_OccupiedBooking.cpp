//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
// BST_OccupiedBooking.cpp - Implementation of Binary Search Tree
// Bookings that have room number assigned will be allowed to be stored in this BST and are sorted by room number

#include "BST_OccupiedBooking.h"
#include <time.h>
#define max(x,y) ((x > y)? x : y)

// constructor
BST_OccupiedBooking::BST_OccupiedBooking()
{
	root = NULL;
}

// search an item in the binary search tree
BinaryNode* BST_OccupiedBooking::search(OccupiedBooking target)
{
	return search(root, target);
}

BinaryNode* BST_OccupiedBooking::search(BinaryNode* t, OccupiedBooking target)
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

// insert an item to the binary search tree
void BST_OccupiedBooking::insert(OccupiedBooking item)
{
	insert(root, item);
}

void BST_OccupiedBooking::insert(BinaryNode*& t, OccupiedBooking item)
{
	// Do not proceed to store bookings without room number assigned
	// This BST is only for bookings that have occupied a room before.
	if (item.getRoom().getRoomNum() < 0) {
		return;
	}

	// Base case
	if (t == NULL)
	{
		BinaryNode* newroot = new BinaryNode;
		newroot->item = item;
		newroot->left = NULL;
		newroot->right = NULL;
		t = newroot;
	}
	else {
		// Compare and sort BST by room number when inserting
		if (item.getRoom().getRoomNum() < t->item.getRoom().getRoomNum())
			insert(t->left, item);  // insert in left subtree
		else
			insert(t->right, item); // insert in right subtree	

	}

	t = balance(t);	// balance the tree (AVL Tree function)
}


// traverse the binary search tree in inorder
void BST_OccupiedBooking::inorder()
{
	cout << "\n=================== Occupied Bookings ===================\n";
	if (isEmpty())
		cout << "No item found" << endl;
	else
		inorder(root);
}

void BST_OccupiedBooking::inorder(BinaryNode* t)
{
	if (t != NULL)
	{
		inorder(t->left);
		t->item.print();
		inorder(t->right);
	}
}

// traverse the binary search tree in preorder
void BST_OccupiedBooking::preorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		preorder(root);
}

void BST_OccupiedBooking::preorder(BinaryNode* t)
{
	if (t != NULL)
	{
		t->item.print();
		preorder(t->left);
		preorder(t->right);
	}
}

// traverse the binary search tree in postorder
void BST_OccupiedBooking::postorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		postorder(root);
}

void BST_OccupiedBooking::postorder(BinaryNode* t)
{
	if (t != NULL)
	{
		postorder(t->left);
		postorder(t->right);
		t->item.print();
	}
}

// check if the binary search tree is empty
bool BST_OccupiedBooking::isEmpty()
{
	return (root == NULL);
}

// count the number of roots in the binary search tree
int BST_OccupiedBooking::countNodes()
{
	return countNodes(root);
}

int BST_OccupiedBooking::countNodes(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + countNodes(t->left) + countNodes(t->right);
}

// compute the height of the binary search tree
int BST_OccupiedBooking::getHeight()
{
	return getHeight(root);
}

int BST_OccupiedBooking::getHeight(BinaryNode* t)
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
bool BST_OccupiedBooking::isBalanced()
{
	return isBalanced(root);
}

bool BST_OccupiedBooking::isBalanced(BinaryNode* t)
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
void BST_OccupiedBooking::remove(OccupiedBooking target)
{
	remove(root, target);
	balanceTree(root);			// AVL Tree function
}



void BST_OccupiedBooking::remove(BinaryNode*& t, OccupiedBooking item)
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

				OccupiedBooking item = successor->item;
				remove(t->left, item);				// delete the successor (either case 1 or case 2)
				t->item = item;						// replace the root’s item with that of the successor
			}
		}
	}
}