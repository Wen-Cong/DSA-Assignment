#pragma once
#include "Dictionary.h";

// constructor
Dictionary::Dictionary()
{
	size = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		items[i] = NULL;
	}
}

// destructor
Dictionary::~Dictionary()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		items[i] = NULL;
	}
}

int charvalue(char c)
{
	if (isalpha(c))
	{
		if (isupper(c))
			return (int)c - (int)'A';
		else
			return (int)c - (int)'a' + 26;
	}
	else
		return -1;
}


int64_t Dictionary::hash(KeyType key)
{
	int64_t hashValue = 0;
	for (int i = 0; i < key.length(); i++)
	{
		char c = key.at(i);
		int charValue = charvalue(c);
		hashValue = (hashValue * 52) + charValue;
	}

	return hashValue;
}


bool Dictionary::add(KeyType newKey, ItemType newItem)
{
	if (size < MAX_SIZE)
	{
		int index = (this->hash(newKey)) % MAX_SIZE;

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


void Dictionary::remove(KeyType key)
{
	if (!isEmpty())
	{
		int index = (this->hash(key)) % MAX_SIZE;
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


ItemType Dictionary::get(KeyType key)
{
	if (!isEmpty())
	{
		int index = (this->hash(key)) % MAX_SIZE;
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

			return NULL;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}


bool Dictionary::isEmpty()
{
	return size == 0;
}


int Dictionary::getLength()
{
	return size;
}


void Dictionary::print()
{
	for (int i = 0; i < MAX_SIZE; i++)
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