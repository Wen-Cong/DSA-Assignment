//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
#pragma once
#include "Booking.h";

typedef Booking ItemType;

struct BinaryNode
{
	ItemType   item;	// data item
	BinaryNode* left;	// pointer pointing to left subtree
	BinaryNode* right;	// pointer pointing to right subtree
	tm min;				// Minimum low value of children
	tm max;				// Maximum high value of children
};