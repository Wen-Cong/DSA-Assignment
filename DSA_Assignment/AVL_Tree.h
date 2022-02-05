//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
// AVL_Tree.h - AVL functions(Specification)
#pragma once
#include<iostream>
using namespace std;

#include "BinaryNode.h"

void balanceTree(BinaryNode*& t);

// AVL Tree functions
// balance a node
BinaryNode* balance(BinaryNode* t);
// left rotation of node
BinaryNode* rotateLeft(BinaryNode* node);
// right rotation of node
BinaryNode* rotateRight(BinaryNode* node);
// left right rotation of node
BinaryNode* rotateLeftRight(BinaryNode* node);
// right left rotation of node
BinaryNode* rotateRightLeft(BinaryNode* node);
// check the difference in number of nodes in left and right subtrees
// left heavy  : diff > +1
// right heavy : diff < -1
int diff(BinaryNode* t);
int getHeight(BinaryNode* t);