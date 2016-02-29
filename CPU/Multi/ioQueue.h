#include <iostream>
#include "node.h"
#include "fcfsQueue.h"
#include "priorityQueue.h"
using namespace std;
#pragma once
class ioQueue
{
	friend class priorityQueue;
	friend class fcfsQueue;
	public:
		ioQueue() {front=0; back=0;};//creates empty ioQueue
		void Enqueue(node & Org);//Places process in queue based off remaing io time
		node & outOfIo(int);//Sends information of process leaving queue.
		int checkIoStatus(int);//Checks processes leaving io at this point in time.
		void Dequeue();//Removes process from front
		void Print(int,ofstream*);//Prints all io processes and their info
		bool Is_Empty() {return front==0;};//Checks if queue is empty.
	private:
		node *front,*back;//front, back processes in queue
};