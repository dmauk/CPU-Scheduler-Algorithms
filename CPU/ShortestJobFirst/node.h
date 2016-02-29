#include <iostream>
#include <vector>
using namespace std;

#pragma once
//This class is used as the general object for a process. The class is designed to function
//in both the ioQueue class and the processQueue class. 
class node
{
	public:
		node();
		node & operator=(node &); //overloaded to pass all of the information of a node from one place to another.
		string name;//Name of the proces
		int curIoTime; //Expected time for process to get out of io
		int curCpuBurstTime;//Expected time for process to finish cpu burst
		int arrivalTime;//Time the process reaches the ready queue
		int waitTime;//time process spends waiting in ready queue
		int TurnAroundTime;//Time from ready queue to final execution
		int responseTime;//Time for process to get on cpu (first time)
		int cpuBurstNumber;//current cpu burst the process is on
		int ioBurstNumber;//current io burst process is on
		bool dispatchedOnce; //checks if process has been previously dispatched (for responseTime calculation)
		vector<int> ioBurstList;//Holds all io burst times for process
		vector<int> cpuBurstList;//Holds all cpu burst times
		node *prev, *next;//points to next, prev process in queue
};