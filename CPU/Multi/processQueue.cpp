#include "processQueue.h"
#include <iostream>
#include <string>

void processQueue::Enqueue(node & newProcess)
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
				p->prev=bb;//add equal process time case to all cases middle front back
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

void processQueue::Dequeue()
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
void processQueue::Print()
{
				cout<<"Ready Queue:  Process   Burst"<<endl;


	if(!Is_Empty())
	{
		node * p = front;
		while(p!=0)
		{
				cout<<"              "<<p->name<<"        "<<p->cpuBurstList[p->cpuBurstNumber]<<endl;
			p=p->prev;
		}
	}
	else
	{
				cout<<"              [Empty]"<<endl;
	}
}

void processQueue::generateProcesses()
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
	process.remainingCpuBurstTime=17;
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
	process.remainingCpuBurstTime=10;
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
	process.remainingCpuBurstTime=18;
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
	process.remainingCpuBurstTime=17;
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
	process.remainingCpuBurstTime=5;
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
	process.remainingCpuBurstTime=10;
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
	process.remainingCpuBurstTime=6;
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
	process.remainingCpuBurstTime=9;
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
	process.remainingCpuBurstTime=6;
	Enqueue(process);
}

void processQueue::setQuantum(int time)
{
	priorityQuantum=time;
}

node & processQueue::dispatchProcess(int currentTime)
{
	if(front->dispatchedOnce==false)
	{
		front->responseTime=currentTime;
		front->dispatchedOnce=true;
	}
	front->waitTime+=(currentTime-front->arrivalTime);
	if(front->newBurst)
	{
		front->remainingCpuBurstTime=front->cpuBurstList[front->cpuBurstNumber];
		front->cpuBurstNumber+=1;
	}
	if(front->remainingCpuBurstTime<priorityQuantum)
	{
		front->curCpuBurstTime=front->remainingCpuBurstTime;
	}
	else
	{
		front->curCpuBurstTime=priorityQuantum;
	}
	return *front;
}
