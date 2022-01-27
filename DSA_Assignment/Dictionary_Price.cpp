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
	for (int i = 0; i < PRICE_MAX_SIZE; i++)
	{
		items[i] = NULL;
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


long long Dictionary_Price::hash(PriceKeyType key)
{
	string firstWord = key.substr(0, key.find(" "));
	long long hashValue = 0;
	for (int i = 0; i < firstWord.length(); i++)
	{
		char c = firstWord.at(i);
		int charValue = charvalue(c);
		hashValue = (hashValue * 53) + charValue;
	}

	return hashValue;
}


bool Dictionary_Price::add(PriceKeyType newKey, PriceType newItem)
{
	if (size < PRICE_MAX_SIZE)
	{
		int index = (this->hash(newKey)) % PRICE_MAX_SIZE;
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
					return false;
				}
				tempNode = tempNode->next;
			}

			if (tempNode->key == newKey)
			{
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
		int index = (this->hash(key)) % PRICE_MAX_SIZE;
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
	if (!isEmpty())
	{
		int index = (this->hash(key)) % PRICE_MAX_SIZE;
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

			return 0;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
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
	for (int i = 0; i < PRICE_MAX_SIZE; i++)
	{
		if (items[i] != NULL)
		{
			Node* tempNode = items[i];
			while (tempNode != NULL)
			{
				cout << tempNode->key << ": " << tempNode->item << endl;
				tempNode = tempNode->next;
			}
		}
	}
	cout << endl;
}