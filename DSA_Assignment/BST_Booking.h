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
#pragma once
#include<iostream>
using namespace std;
#include "BinaryNode.h"
#include "AVL_Tree.h"		// AVL Tree functions

class BST_Booking
{
private:
	BinaryNode* root;		// root of the BST

public:

	// constructor
	BST_Booking();

	// search an item in the binary search tree
	BinaryNode* search(ItemType target);
	BinaryNode* search(BinaryNode* root, ItemType target);

	// insert an item to the binary search tree
	void insert(ItemType item);
	void insert(BinaryNode*& root, ItemType item);

	// delete an item from the binary search tree
	void remove(ItemType target);
	void remove(BinaryNode*& root, ItemType target);

	// traverse the binary search tree in inorder
	void inorder();
	void inorder(BinaryNode* t);

	// traverse the binary search tree in preorder
	void preorder();
	void preorder(BinaryNode* t);

	// traverse the binary search tree in postorder
	void postorder();
	void postorder(BinaryNode* t);

	// check if the binary search tree is empty
	bool isEmpty();

	// count the number of nodes in the binary search tree
	int countNodes();
	int countNodes(BinaryNode* t);

	// compute the height of the binary search tree
	int getHeight();
	int getHeight(BinaryNode* t);

	// check if the binary search tree is balanced
	bool isBalanced();
	bool isBalanced(BinaryNode* t);
};

