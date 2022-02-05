//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
// BST_OccupiedBooking.cpp - Implementation of Binary Search Tree
// Bookings stored in this BST are sorted by room number

#pragma once
#include<iostream>
using namespace std;
#include "BinaryNode.h"
#include "AVL_Tree.h" // AVL Tree functions
#include "List.h"
#include "Dictionary_Room.h"
typedef Booking OccupiedBooking;

class BST_OccupiedBooking
{
private:
	BinaryNode* root;		// root of the BST

public:

	// constructor
	BST_OccupiedBooking();

	// search an item in the binary search tree
	BinaryNode* search(OccupiedBooking target);
	BinaryNode* search(BinaryNode* root, OccupiedBooking target);

	// insert an item to the binary search tree
	// pre : none
	// post: item is added into the binary search tree
	void insert(OccupiedBooking item);
	void insert(BinaryNode*& root, OccupiedBooking item);

	// delete an item from the binary search tree
	// pre : none
	// post: removed specified item from the binary search tree
	void remove(OccupiedBooking target);
	void remove(BinaryNode*& root, OccupiedBooking target);

	// traverse the binary search tree in inorder
	// pre : none
	// post: none
	void inorder();
	void inorder(BinaryNode* t, Dictionary_Room& roomsAlreadySeen);

	// traverse the binary search tree in preorder
	// pre : none
	// post: none
	void preorder();
	void preorder(BinaryNode* t);

	// traverse the binary search tree in postorder
	// pre : none
	// post: none
	void postorder();
	void postorder(BinaryNode* t);

	// check if the binary search tree is empty
	// pre : none
	// post: none
	bool isEmpty();

	// count the number of nodes in the binary search tree
	// pre : none
	// post: none
	// return the number of nodes in the tree
	int countNodes();
	int countNodes(BinaryNode* t);

	// compute the height of the binary search tree
	// pre : none
	// post: none
	// return the height of the tree
	int getHeight();
	int getHeight(BinaryNode* t);

	// check if the binary search tree is balanced
	// pre : none
	// post: none
	// return if the tree is balanced returns true else false
	bool isBalanced();
	bool isBalanced(BinaryNode* t);
};

