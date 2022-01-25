//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
// BST_Checkin.cpp - Implementation of Binary Search Tree
// Bookings that guests have Checkin are stored in this BST
#include "BST_Checkin.h"
#include <time.h>
#define max(x,y) ((x > y)? x : y)

// constructor
BST_Checkin::BST_Checkin()
{
	root = NULL;
}

// search an item in the binary search tree
BinaryNode* BST_Checkin::search(ItemType target)
{
	return search(root, target);
}

BinaryNode* BST_Checkin::search(BinaryNode* t, ItemType target)
{
	if (t == NULL)	// item not found
		return NULL;
	else
	{
		//Comparing time the year have to be the no. of years different from 1900
		tm compare = t->item.getCheckIn();
		compare.tm_year -= 1900;
		tm temp = target.getCheckIn();
		temp.tm_year -= 1900;
		// if there is no time difference means its exact
		if (difftime(mktime(&compare), mktime(&temp))==0)		// item found
			return t;
		else
			// if diff time is positive, means target time is earlier than the root time.
			if (difftime(mktime(&compare), mktime(&temp)) > 0
				)	// search in left subtree
				return search(t->left, target);
			else					// search in right subtree
				return search(t->right, target);
	}
}

// insert an item to the binary search tree
void BST_Checkin::insert(ItemType item)
{
	insert(root, item);
}

void BST_Checkin::insert(BinaryNode* &t, ItemType item)
{
	if (t == NULL)
	{
		BinaryNode *newNode = new BinaryNode;
		newNode->item = item;
		newNode->left = NULL;
		newNode->right = NULL;
		t = newNode;
	}
	else {
		//Comparing time the year have to be the no. of years different from 1900
		tm compare = t->item.getCheckIn();
		compare.tm_year -= 1900;
		tm temp = item.getCheckIn();
		temp.tm_year -= 1900;
		//if difftime > 1 temp is earlier
		if (difftime(mktime(&compare), mktime(&temp)) > 0)
			insert(t->left, item);  // insert in left subtree
		else
			insert(t->right, item); // insert in right subtree	
	}

	t = balance(t);				// balance the tree (AVL Tree function)
}


// traverse the binary search tree in inorder
void BST_Checkin::inorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		inorder(root);
}

void BST_Checkin::inorder(BinaryNode* t)
{
	if (t != NULL)
	{
		inorder(t->left);
		cout << t->item.getId() << endl;
		inorder(t->right);
	}
}
// traverse the binary search tree in preorder
void BST_Checkin::preorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		preorder(root);
}

void BST_Checkin::preorder(BinaryNode* t)
{
	if (t != NULL)
	{
		cout << t->item.getId() << endl;
		preorder(t->left);
		preorder(t->right);
	}
}

// traverse the binary search tree in postorder
void BST_Checkin::postorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		postorder(root);
}

void BST_Checkin::postorder(BinaryNode* t)
{
	if (t != NULL)
	{
		postorder(t->left);
		postorder(t->right);
		cout << t->item.getId() << endl;
	}
}

// check if the binary search tree is empty
bool BST_Checkin::isEmpty()
{
	return (root == NULL);
}

// count the number of nodes in the binary search tree
int BST_Checkin::countNodes()
{
	return countNodes(root);
}

int BST_Checkin::countNodes(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + countNodes(t->left) + countNodes(t->right);
}

// compute the height of the binary search tree
int BST_Checkin::getHeight()
{
	return getHeight(root);
}

int BST_Checkin::getHeight(BinaryNode* t)
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
bool BST_Checkin::isBalanced()
{
	return isBalanced(root);
}

bool BST_Checkin::isBalanced(BinaryNode *t)
{
	if (t == NULL)
		return true;
	else
	{
		int leftHeight = getHeight(t->left);	// height of left sub-tree
		int rightHeight = getHeight(t->right);	// height of right sub-tree
		bool isBalancedNode = (abs(leftHeight - rightHeight) <= 1);
		bool isBalancedLeft = isBalanced(t->left);
		bool isBalancedRight = isBalanced(t->right);
		return (isBalancedNode && isBalancedLeft && isBalancedRight);
	}
}

// delete an item from the binary search tree
void BST_Checkin::remove(ItemType target)
{
	remove(root, target);
	balanceTree(root);			// AVL Tree function
}

void BST_Checkin::remove(BinaryNode* &t, ItemType item)
{
	if (t != NULL)
	{
		//Comparing time the year have to be the no. of years different from 1900
		tm compare = t->item.getCheckIn();
		compare.tm_year -= 1900;
		tm temp = item.getCheckIn();
		temp.tm_year -= 1900;
		//if difftime > 1 temp is earlier
		if (difftime(mktime(&compare), mktime(&temp)) > 0)			// search in left subtree
			remove(t->left, item);
		else if (difftime(mktime(&compare),mktime(&temp)) < 0)	// search in right subtree
			remove(t->right, item);
		else						// item == t->item (found) - base case
		{
			if (t->left == NULL && t->right == NULL) // case 1 : node has 0 child
			{
				BinaryNode* temp = t;	// to be deleted
				t = NULL;
				delete temp;			// delete the node
			}
			else if (t->left == NULL)	// case 2 : node has 1 child
			{
				BinaryNode* temp = t;	// node to be deleted

				if (t == root)			// current node is root
					root = t->right;
				else
					t = t->right;

				delete temp;			// delete the node
			}
			else if (t->right == NULL)	// case 2 : node has 1 child
			{
				BinaryNode* temp = t;	// node to be deleted

				if (t == root)			// current node is root
					root = t->left;
				else
					t = t->left;

				delete temp;			// delete the node
			}
			else // case 3 : node has 2 children
			{
				BinaryNode* successor = t->left;
				while (successor->right != NULL)	// search for right most node in left sub-tree
					successor = successor->right;

				ItemType item = successor->item;	
				remove(t->left, item);				// delete the successor (either case 1 or case 2)
				t->item = item;						// replace the node’s item with that of the successor
			}
		}
	}
}




