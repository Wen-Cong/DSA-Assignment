// Queue.h - Specification of Queue ADT (Pointer-based)
#pragma once
#include<string>
#include<iostream>
#include"Booking.h"
using namespace std;

typedef Booking QueueType;

class Queue
{
private:
    struct Node
    {
        QueueType item;	// item
        Node* next;	// pointer pointing to next item
    };

    Node* frontNode;	// point to the first item
    Node* backNode;	// point to the first item


public:
    // constructor
    Queue();
    ~Queue();

    // enqueue (add) item at the back of queue
    bool enqueue(QueueType item);

    // dequeue (remove) item from front of queue
    bool dequeue();

    // dequeue (remove) and retrieve item from front of queue
    bool dequeue(QueueType& item);

    // retrieve (get) item from front of queue
    void getFront(QueueType& item);

    // check if the queue is empty
    bool isEmpty();

    // display items in queue from front to back
    void displayItems();
};
