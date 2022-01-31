#include"Queue.h"
Queue::Queue() {
	frontNode = NULL;
	backNode = NULL;
}
Queue::~Queue() {
	while(!isEmpty()) {
		Node* tempNode = frontNode;
		if (frontNode == backNode) {
			frontNode = NULL;
			backNode = NULL;
		}
		else {
			frontNode = tempNode->next;
		}
		tempNode->next = NULL;
		delete tempNode;
	}
}

// enqueue (add) item at the back of queue
bool Queue::enqueue(QueueType item){
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;
	if (isEmpty()) {
		frontNode = newNode;
		backNode = newNode;
	}
	else {
		backNode->next = newNode;
		backNode = newNode;
	}
	return true;
}

// dequeue (remove) item from front of queue
bool Queue::dequeue() {
	if (!isEmpty()) {
		Node* tempNode = frontNode;
		if (frontNode == backNode) {
			frontNode = NULL;
			backNode = NULL;
		}
		else {
			frontNode = tempNode->next;
		}
		tempNode->next = NULL;
		delete tempNode;
		return true;
	}
	return false;
}

// dequeue (remove) and retrieve item from front of queue
bool Queue::dequeue(QueueType& item) {
	if (!isEmpty()) {
		item = frontNode->item;
		dequeue();
		return true;
	}
	else {
		return false;
	}
}

// retrieve (get) item from front of queue
void Queue::getFront(QueueType& item) {
	if (!isEmpty()) {
		item = frontNode->item;
	}
}

// check if the queue is empty
bool Queue::isEmpty() {
	if (frontNode == NULL) {
		return true;
	}
	else
		return false;
}

// display items in queue from front to back
void Queue::displayItems() {
	QueueType item;
	Queue tempQueue;
	if (!isEmpty()) {
		while (!isEmpty()) {
			dequeue(item);
			cout << item << endl;
			tempQueue.enqueue(item);
		}
		while (!tempQueue.isEmpty()) {
			tempQueue.dequeue(item);
			enqueue(item);
		}
	}
	else
		cout << "The queue is empty.\n" << endl;
}