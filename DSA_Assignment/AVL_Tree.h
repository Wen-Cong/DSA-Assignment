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
BinaryNode* balance(BinaryNode* t);
BinaryNode* rotateLeft(BinaryNode* node);
BinaryNode* rotateRight(BinaryNode* node);
BinaryNode* rotateLeftRight(BinaryNode* node);
BinaryNode* rotateRightLeft(BinaryNode* node);
int diff(BinaryNode* t);
int getHeight(BinaryNode* t);