#include "ioQueue.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


//In order to make the switching of processes from io queue to process queue easy, the passed processes are organized by remaining io time.
//This gurantees that the processes in the front of the io queue will be getting out of Io sooner than those in the back. This makes dequeueing
//processes extremely simple (i.e. remove from front).
void ioQueue::Enqueue(node & newProcess)//Organizes new process in the io queue based off remaining io time. Shorter io time is in the front.
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
			if(p->curIoTime<bb->curIoTime&&bb==front)
			{
				bb->next=p;
				p->prev=bb;
				p->next=0;
				front=p;
				return;
			}
			else if(p->curIoTime<bb->curIoTime)
			{
				bb->next=p;
				bf->prev=p;
				p->prev=bb;
				p->next=bf;
				return;
			}
			else if(p->curIoTime==bb->curIoTime)//Organize based on remaining time if remaining io time is the same
			{
				while(bb!=0)
				{
					if(p->name<bb->name)
					{
						if(bb==front)
						{
							p->next=0;
							front->next=p;
							p->prev=front;
							front=p;
							return;
						}
						else
						{
							p->next=bf;
							p->prev=bb;
							bb->next=p;
							bf->prev=p;
							return;
						}
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

void ioQueue::Dequeue()//Removes process from front of queue
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

node & ioQueue::outOfIo(int currentTime)//Sends process information of process leaving io queue.
{
	front->arrivalTime=currentTime;
	return *front;
}


int ioQueue::checkIoStatus(int currentTime)//checks number of processes that will be finishing at this point in time
{
	int processesDone=0;
	node *p;
	if(Is_Empty())
	{
		return 0;
	}
	else
	{
		p=front;
		while(p!=0)
		{
			if(p->curIoTime==currentTime)
			{
				processesDone++;
			}
			p=p->prev;
		}
	}
	return processesDone;
}

void ioQueue::Print(int currentTime,ofstream*outFile)//Prints all processes in io and their info
{
	cout<<"IO Queue:     Process   Burst"<<endl;
	*outFile<<"IO Queue:     Process   Burst"<<endl;
	if(!Is_Empty())
	{
		node * p = front;
		while(p!=0)
		{
			cout<<"              "<<p->name<<"        "<<p->curIoTime-currentTime<<endl;
			*outFile<<"              "<<p->name<<"        "<<p->curIoTime-currentTime<<endl;
			p=p->prev;
		}
	}
	else
	{
				cout<<"              [Empty]"<<endl;
				*outFile<<"              [Empty]"<<endl;
	}
}