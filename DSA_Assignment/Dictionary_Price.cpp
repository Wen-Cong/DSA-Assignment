#pragma once
#include "Dictionary_Price.h";

// constructor
Dictionary_Price::Dictionary_Price()
{
	size = 0;
	for (int i = 0; i < PRICE_MAX_SIZE; i++)
	{
		items[i] = NULL;
	}
}

// destructor
Dictionary_Price::~Dictionary_Price()
{
	for (int i = 0; i < PRICE_MAX_SIZE; i++) {
		if (items[i] != NULL) {
			Node* tempNode = items[i];
			while (tempNode->next != NULL) {
				items[i] = tempNode->next;
				tempNode->next = NULL;
				delete tempNode;
				tempNode = items[i];
			}
		}
	}
}


int charvalue(char c)
{
	int charval;
	if (isalpha(c))
	{
		if (isupper(c))
			charval =(int)c - (int)'A';
		else
			charval = (int)c - (int)'a' + 26;
	}
	else
		charval = -1;

	return charval;
}

//why not a if else selection structure? Since there is only 5
long long Dictionary_Price::hash(PriceKeyType key)
{
	int total = 0;
	total += charvalue(key[0]);
	total %= PRICE_MAX_SIZE;
	for (int i = 1; i < key.size(); i++) {
		total = total * 52 + charvalue(key[i]);
		total %= PRICE_MAX_SIZE;
	}
	return total;
}


bool Dictionary_Price::add(PriceKeyType newKey, PriceType newItem)
{
	if (size < PRICE_MAX_SIZE)
	{
		int index = (this->hash(newKey));;
		Node* newNode = new Node;
		newNode->key = newKey;
		newNode->item = newItem;
		newNode->next = NULL;
		 
		if (items[index] != NULL)
		{
			Node* tempNode = items[index];
			while (tempNode->next != NULL)
			{ 
				if (tempNode->key == newKey)
				{
					tempNode->item.count++;
					return false;
				}
				tempNode = tempNode->next;
			}

			if (tempNode->key == newKey)
			{
				tempNode->item.count++;
				return false;
			}
			tempNode->next = newNode;
		}
		else
		{
			items[index] = newNode;
		}

		size++;
		return true;
	}
	else
	{
		return false;
	}
}


void Dictionary_Price::remove(PriceKeyType key)
{
	if (!isEmpty())
	{
		int index = (this->hash(key)); //
		if (items[index] != NULL)
		{
			Node* tempNode = items[index];
			if (tempNode->key == key)
			{
				items[index] = tempNode->next;
				tempNode->next = NULL;
				delete tempNode;

				size--;
			}
			else
			{
				while (tempNode != NULL)
				{
					if (tempNode->next->key == key)
					{
						Node* deleteNode = tempNode->next;
						tempNode->next = deleteNode->next;
						deleteNode->next = NULL;
						delete deleteNode;

						size--;
					}

					tempNode = tempNode->next;
				}
			}
		}
	}
}


PriceType Dictionary_Price::get(PriceKeyType key)
{
	PriceRoomType pr = PriceRoomType();
	if (!isEmpty())
	{
		int index = (this->hash(key));
		if (items[index] != NULL)
		{
			Node* tempNode = items[index];
			while (tempNode != NULL)
			{
				if (tempNode->key == key)
				{
					return tempNode->item;
				}
				tempNode = tempNode->next;
			}

			return pr;
		}
		else
		{
			return pr;
		}
	}
	else
	{
		return pr;
	}
}


bool Dictionary_Price::isEmpty()
{
	return size == 0;
}


int Dictionary_Price::getLength()
{
	return size;
}


void Dictionary_Price::print()
{
	int count = 0;
	for (int i = 0; i < PRICE_MAX_SIZE; i++)
	{
		if (items[i] != NULL)
		{
			Node* tempNode = items[i];
			while (tempNode != NULL)
			{
				count++;
				cout << "[" << count << "] " << tempNode->key << " ($" << tempNode->item.price << ")" << endl;
				tempNode = tempNode->next;
			}
		}
	}
	cout << endl;
}