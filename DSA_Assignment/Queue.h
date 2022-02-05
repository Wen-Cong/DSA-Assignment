//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
// Queue.h - Specification of Queue ADT (Pointer-based)
#pragma once
#include<string>
#include<iostream>
#include"Booking.h"
using namespace std;

typedef string QueueType;

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
