#pragma once

#include<string>
#include<iostream>
using namespace std;

const int PRICE_MAX_SIZE = 7;
typedef string PriceKeyType;
typedef double PriceType;


class Dictionary_Price
{
private:
	struct Node
	{
		PriceKeyType key;   // search key
		PriceType item;	// data item
		Node     *next;	// pointer pointing to next item with same search key
	};

	Node *items[PRICE_MAX_SIZE];
	int  size;			// number of items in the Dictionary_Price

public:

	// constructor
	Dictionary_Price();

	// destructor
	~Dictionary_Price();

	long long hash(PriceKeyType key);

	// add a new item with the specified key to the Dictionary_Price
	// pre : none
	// post: new item is added to the Dictionary_Price
	//       size of Dictionary_Price is increased by 1
	bool add(PriceKeyType newKey, PriceType newItem);

	// remove an item with the specified key in the Dictionary_Price
	// pre : key must exist in the Dictionary_Price
	// post: item is removed from the Dictionary_Price
	//       size of Dictionary_Price is decreased by 1
	void remove(PriceKeyType key);


	// get an item with the specified key in the Dictionary_Price (retrieve)
	// pre : key must exist in the Dictionary_Price
	// post: none
	// return the item with the specified key from the Dictionary_Price
	PriceType get(PriceKeyType key);

	// check if the Dictionary_Price is empty
	// pre : none
	// post: none
	// return true if the Dictionary_Price is empty; otherwise returns false
	bool isEmpty();

	// check the size of the Dictionary_Price
	// pre : none
	// post: none
	// return the number of items in the Dictionary_Price
	int getLength();

	//------------------- Other useful functions -----------------

	// display the items in the Dictionary_Price
	void print();

	// void replace(PriceKeyType key, PriceType item);
	// bool contains(PriceKeyType key);
};
