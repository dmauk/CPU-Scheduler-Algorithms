#include <iostream>
#include "node.h"
using namespace std;
#pragma once

class fcfsQueue
{
	friend class ioQueue;
	public:
		fcfsQueue() {front=0; back=0;};//creates empty queue
		void generateProcesses();//Generates  9 processes
		void Enqueue(node & Org);//Enqueues process at back
		void Dequeue();//Dequeues process from front
		void Print(ofstream*);//Prints out all processes and information in queue
		node & dispatchProcess(int); //Sends value of process that will go on CPU
		bool Is_Empty() {return front==0;};//Checks if queue is empty
	private:
		node *front;//front process in queue
		node *back;//back process in queue
};