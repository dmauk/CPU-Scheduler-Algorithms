#include "node.h"

node::node()//initializes process values to 0
{
	priority=1;
	curIoTime=0;
	curCpuBurstTime=0;
	remainingCpuBurstTime=0;
	arrivalTime=0;
	waitTime=0;
	TurnAroundTime=0;
	responseTime=0;
	cpuBurstNumber=0;
	ioBurstNumber=0;
	dispatchedOnce=false;
	newBurst=true;

}
node & node::operator=(node & Org)//Passes all data of process to another (for easy switching between queues)
{
	name=Org.name;
	curCpuBurstTime=Org.curCpuBurstTime;
	arrivalTime=Org.arrivalTime;
	waitTime=Org.waitTime;
	TurnAroundTime=Org.TurnAroundTime;
	responseTime=Org.responseTime;
	cpuBurstNumber=Org.cpuBurstNumber;
	ioBurstNumber=Org.ioBurstNumber;
	dispatchedOnce=Org.dispatchedOnce;
	newBurst=Org.newBurst;
	priority=Org.priority;
	remainingCpuBurstTime=Org.remainingCpuBurstTime;
	curIoTime=Org.curIoTime;
	ioBurstList=Org.ioBurstList;
	cpuBurstList=Org.cpuBurstList;
	next=0;
	prev=0;
	return *this;
}
