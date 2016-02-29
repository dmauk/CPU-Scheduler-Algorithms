#include "processQueue.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void processQueue::Enqueue(node & newProcess)//Places process in queue based on remaing execution time.
{
	node * p = new node;
	*p=newProcess;
	if(Is_Empty())
	{
		front=p;
		back=p;
		p->next=0;
		p->prev=0;
	}
	else
	{
		node * bf;
		node * bb;
		bf=front;
		bb=front;
		while(bb!=0)
		{
			if(p->cpuBurstList[p->cpuBurstNumber]<bb->cpuBurstList[bb->cpuBurstNumber]&&bb==front)
			{
				bb->next=
				p->prev=bb;
				p->next=0;
				front=p;
				return;
			}
			else if(p->cpuBurstList[p->cpuBurstNumber]<bb->cpuBurstList[bb->cpuBurstNumber])
			{
				bb->next=p;
				bf->prev=p;
				p->prev=bb;
				p->next=bf;
				return;
			}
			else
			{
				bf=bb;
				bb=bb->prev;
			}
		}
		back=p;
		p->prev=0;
		p->next=bf;
		bf->prev=p;
	}
}

void processQueue::Dequeue() //Removes front process from the queue.
{
	if(!Is_Empty()&&front==back)
	{
		delete front;
		front = 0;
		back = 0;
	}
	else if(!Is_Empty())
	{
		node * p = front;
		front = p->prev;
		front->next = 0;
		delete p;
	}
}
void processQueue::Print(ofstream * outFile) //Displays all processes in the Process Queue by position (displays name and remaining burst time)
{
	cout<<"Ready Queue:  Process   Burst"<<endl;
	*outFile<<"Ready Queue:  Process   Burst"<<endl;
	if(!Is_Empty())
	{
		node * p = front;
		while(p!=0)
		{
			cout<<"              "<<p->name<<"        "<<p->cpuBurstList[p->cpuBurstNumber]<<endl;
			*outFile<<"              "<<p->name<<"        "<<p->cpuBurstList[p->cpuBurstNumber]<<endl;
			p=p->prev;
		}
	}
	else
	{
		cout<<"              [Empty]"<<endl;
		*outFile<<"              [Empty]"<<endl;
	}
}

void processQueue::generateProcesses()//Generates 9 processes with io burst times, cpu burst times, and a unique name
{
	node process;
	//P1
	process.name="P1";
	process.ioBurstList.push_back(24);
	process.ioBurstList.push_back(73);
	process.ioBurstList.push_back(31);
	process.ioBurstList.push_back(27);
	process.ioBurstList.push_back(33);
	process.ioBurstList.push_back(43);
	process.ioBurstList.push_back(64);
	process.ioBurstList.push_back(19);
	process.cpuBurstList.push_back(17);
	process.cpuBurstList.push_back(18);
	process.cpuBurstList.push_back(17);
	process.cpuBurstList.push_back(16);
	process.cpuBurstList.push_back(14);
	process.cpuBurstList.push_back(16);
	process.cpuBurstList.push_back(14);
	process.cpuBurstList.push_back(15);
	process.cpuBurstList.push_back(15);
	Enqueue(process);
	//P2
	process.ioBurstList.clear();
	process.cpuBurstList.clear();
	process.name="P2";
	process.ioBurstList.push_back(31);
	process.ioBurstList.push_back(35);
	process.ioBurstList.push_back(42);
	process.ioBurstList.push_back(43);
	process.ioBurstList.push_back(47);
	process.ioBurstList.push_back(43);
	process.ioBurstList.push_back(51);
	process.cpuBurstList.push_back(10);
	process.cpuBurstList.push_back(9);
	process.cpuBurstList.push_back(8);
	process.cpuBurstList.push_back(7);
	process.cpuBurstList.push_back(9);
	process.cpuBurstList.push_back(12);
	process.cpuBurstList.push_back(15);
	process.cpuBurstList.push_back(19);
	Enqueue(process);
	//P3
	process.ioBurstList.clear();
	process.cpuBurstList.clear();
	process.name="P3";
	process.ioBurstList.push_back(51);
	process.ioBurstList.push_back(53);
	process.ioBurstList.push_back(61);
	process.ioBurstList.push_back(31);
	process.ioBurstList.push_back(43);
	process.ioBurstList.push_back(31);
	process.cpuBurstList.push_back(18);
	process.cpuBurstList.push_back(23);
	process.cpuBurstList.push_back(24);
	process.cpuBurstList.push_back(22);
	process.cpuBurstList.push_back(21);
	process.cpuBurstList.push_back(20);
	process.cpuBurstList.push_back(12);
	Enqueue(process);
	//P4
	process.ioBurstList.clear();
	process.cpuBurstList.clear();
	process.name="P4";
	process.ioBurstList.push_back(42);
	process.ioBurstList.push_back(55);
	process.ioBurstList.push_back(54);
	process.ioBurstList.push_back(52);
	process.ioBurstList.push_back(67);
	process.ioBurstList.push_back(72);
	process.ioBurstList.push_back(66);
	process.cpuBurstList.push_back(17);
	process.cpuBurstList.push_back(19);
	process.cpuBurstList.push_back(20);
	process.cpuBurstList.push_back(17);
	process.cpuBurstList.push_back(15);
	process.cpuBurstList.push_back(12);
	process.cpuBurstList.push_back(15);
	process.cpuBurstList.push_back(14);
	Enqueue(process);
	//P5
	process.ioBurstList.clear();
	process.cpuBurstList.clear();
	process.name="P5";
	process.ioBurstList.push_back(61);
	process.ioBurstList.push_back(82);
	process.ioBurstList.push_back(71);
	process.ioBurstList.push_back(61);
	process.ioBurstList.push_back(62);
	process.ioBurstList.push_back(51);
	process.ioBurstList.push_back(77);
	process.ioBurstList.push_back(61);
	process.ioBurstList.push_back(42);
	process.cpuBurstList.push_back(5);
	process.cpuBurstList.push_back(6);
	process.cpuBurstList.push_back(5);
	process.cpuBurstList.push_back(3);
	process.cpuBurstList.push_back(5);
	process.cpuBurstList.push_back(4);
	process.cpuBurstList.push_back(3);
	process.cpuBurstList.push_back(4);
	process.cpuBurstList.push_back(3);
	process.cpuBurstList.push_back(5);
	Enqueue(process);
	//P6
	process.ioBurstList.clear();
	process.cpuBurstList.clear();
	process.name="P6";
	process.ioBurstList.push_back(35);
	process.ioBurstList.push_back(41);
	process.ioBurstList.push_back(33);
	process.ioBurstList.push_back(32);
	process.ioBurstList.push_back(41);
	process.ioBurstList.push_back(29);
	process.cpuBurstList.push_back(10);
	process.cpuBurstList.push_back(12);
	process.cpuBurstList.push_back(14);
	process.cpuBurstList.push_back(11);
	process.cpuBurstList.push_back(15);
	process.cpuBurstList.push_back(13);
	process.cpuBurstList.push_back(11);
	Enqueue(process);
	//P7
	process.ioBurstList.clear();
	process.cpuBurstList.clear();
	process.name="P7";
	process.ioBurstList.push_back(18);
	process.ioBurstList.push_back(21);
	process.ioBurstList.push_back(19);
	process.ioBurstList.push_back(16);
	process.ioBurstList.push_back(29);
	process.ioBurstList.push_back(21);
	process.ioBurstList.push_back(22);
	process.ioBurstList.push_back(24);
	process.cpuBurstList.push_back(6);
	process.cpuBurstList.push_back(7);
	process.cpuBurstList.push_back(5);
	process.cpuBurstList.push_back(4);
	process.cpuBurstList.push_back(5);
	process.cpuBurstList.push_back(7);
	process.cpuBurstList.push_back(8);
	process.cpuBurstList.push_back(6);
	process.cpuBurstList.push_back(5);
	Enqueue(process);
	//P8
	process.ioBurstList.clear();
	process.cpuBurstList.clear();
	process.name="P8";
	process.ioBurstList.push_back(52);
	process.ioBurstList.push_back(42);
	process.ioBurstList.push_back(31);
	process.ioBurstList.push_back(21);
	process.ioBurstList.push_back(43);
	process.ioBurstList.push_back(31);
	process.ioBurstList.push_back(32);
	process.cpuBurstList.push_back(9);
	process.cpuBurstList.push_back(12);
	process.cpuBurstList.push_back(14);
	process.cpuBurstList.push_back(14);
	process.cpuBurstList.push_back(16);
	process.cpuBurstList.push_back(14);
	process.cpuBurstList.push_back(13);
	process.cpuBurstList.push_back(15);
	Enqueue(process);
	//P9
	process.ioBurstList.clear();
	process.cpuBurstList.clear();
	process.name="P9";
	process.ioBurstList.push_back(35);
	process.ioBurstList.push_back(41);
	process.ioBurstList.push_back(33);
	process.ioBurstList.push_back(32);
	process.ioBurstList.push_back(41);
	process.ioBurstList.push_back(29);
	process.ioBurstList.push_back(16);
	process.ioBurstList.push_back(22);
	process.cpuBurstList.push_back(6);
	process.cpuBurstList.push_back(4);
	process.cpuBurstList.push_back(6);
	process.cpuBurstList.push_back(6);
	process.cpuBurstList.push_back(7);
	process.cpuBurstList.push_back(4);
	process.cpuBurstList.push_back(5);
	process.cpuBurstList.push_back(5);
	process.cpuBurstList.push_back(4);
	Enqueue(process);
}

node & processQueue::dispatchProcess(int currentTime) //Returns the information of the node that will be placed on the CPU
{
	if(front->dispatchedOnce==false)
	{
		front->responseTime=currentTime;//calculates response time
		front->dispatchedOnce=true;
	}
	front->waitTime+=(currentTime-front->arrivalTime); //Calculates wait time
	front->curCpuBurstTime=front->cpuBurstList[front->cpuBurstNumber];//Sets CPU burst time based on which cpu burst is next in the vector
	front->cpuBurstNumber+=1; //Sets next cpu bursts to get from the vector
	return *front;//Passes from process from queue.
}

