#include <iostream>
#include "node.h"
using namespace std;
#pragma once

class processQueue
{
	friend class ioQueue;
	public:
		processQueue() {front=0; back=0;};
		//~processQueue();
		void generateProcesses();
		void Enqueue(node & Org);
		void Dequeue();
		void Print();
		node & dispatchProcess(int);
		bool Is_Empty() {return front==0;}
		void setQuantum(int);
		//processQueue & processQueue::operator=(ioQueue & Org);
	private:
		node *front;
		node *back;
		int priorityQuantum;
};