#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "node.h"
#include "processQueue.h"
#include "ioQueue.h"
using namespace std;
int main()
{
	//Declare and initialize all necessary values for cpu algorithm functionality
	ofstream outFile;//reference to output file
	outFile.open("fcfs.txt");
	processQueue pQueue;//Create process queue
	pQueue.generateProcesses();//Generate 9 processes
	ioQueue inOutQueue;//create io queue
	node executingProcess;//create cpu execution process
	executingProcess.name="";
	vector<node> finishedProcesses;//keeps track of processes that have finished all cpu/io bursts
	int currentExecutionTime=0;//tracks current process execution time
	int currentTime=0;//tracks total program time
	bool start=true;//first run 
	bool processOnCpu=true;
	bool allProcessesDone=false;
	int CpuTimeNotUtilized=0;//Tracks total time where cpu had no process
	int IoProcessesDone=0;//tracks finished io processes at current time
	while(!inOutQueue.Is_Empty()||!pQueue.Is_Empty()||allProcessesDone==false)
	{
		IoProcessesDone=inOutQueue.checkIoStatus(currentTime);//Check Io status and put finished processes in processQueue.
		if(IoProcessesDone!=0)
		{
			while(IoProcessesDone!=0)
			{
				pQueue.Enqueue(inOutQueue.outOfIo(currentTime));
				inOutQueue.Dequeue();
				IoProcessesDone--;
			}
		}
		if(executingProcess.curCpuBurstTime==currentExecutionTime&&processOnCpu)//If currently executing process is done, move it to io if need be.
		{
			if(executingProcess.cpuBurstList.size()==executingProcess.cpuBurstNumber)//Save info of process if it has completed all execution/io time
			{
				if(start)
				{
					start=false;
				}
				else
				{
					executingProcess.TurnAroundTime=currentTime;
					finishedProcesses.push_back(executingProcess);
				}
			}
			else//Enqueue process to io if it has another io burst
			{
				executingProcess.curIoTime=(currentTime+executingProcess.ioBurstList[executingProcess.ioBurstNumber]);
				executingProcess.ioBurstNumber+=1;
				inOutQueue.Enqueue(executingProcess);
			}
			if(!pQueue.Is_Empty())//check if process queue is empty, if not place a new process on the cpu and display new set of info
			{
				cout<<"Current Time: "<<currentTime<<endl;
				outFile<<"Current Time: "<<currentTime<<endl;
				processOnCpu=true;
				executingProcess=pQueue.dispatchProcess(currentTime);
				pQueue.Dequeue();
				cout<<"Now Running: "<<executingProcess.name<<endl;
				outFile<<"Now Running: "<<executingProcess.name<<endl;
				cout<<"-------------------------------------------"<<endl<<endl;
				outFile<<"-------------------------------------------"<<endl<<endl;
				pQueue.Print(&outFile);
				inOutQueue.Print(currentTime,&outFile);
				cout<<"-------------------------------------------"<<endl;
				outFile<<"-------------------------------------------"<<endl;
				int i=0;
				cout<<"Completed Processes"<<endl;
				outFile<<"Completed Processes"<<endl;
				while(i<finishedProcesses.size())
				{
					cout<<finishedProcesses[i].name<<"  ";
					outFile<<finishedProcesses[i].name<<"  ";
					i++;
				}
				cout<<endl;
				outFile<<endl;
				cout<<"-------------------------------------------"<<endl;
				cout<<"-------------------------------------------"<<endl;
				outFile<<"-------------------------------------------"<<endl;
				outFile<<"-------------------------------------------"<<endl;
				cout<<endl<<endl;
			}
			else//No process in process queue
			{
				executingProcess.name="";
				executingProcess.curCpuBurstTime=0;
				CpuTimeNotUtilized+=1;
				processOnCpu=false;
			}
			currentExecutionTime=0;
		}
		else if(processOnCpu==false)//Check if the process queue has available processes and put it on cpu/display new set of info.
		{
			if(!pQueue.Is_Empty())
			{
				cout<<"Current Time: "<<currentTime<<endl;
				outFile<<"Current Time: "<<currentTime<<endl;
				processOnCpu=true;
				executingProcess=pQueue.dispatchProcess(currentTime);
				pQueue.Dequeue();
				cout<<"Now Running: "<<executingProcess.name<<endl;
				cout<<"-------------------------------------------"<<endl<<endl;
				outFile<<"Now Running: "<<executingProcess.name<<endl;
				outFile<<"-------------------------------------------"<<endl<<endl;
				pQueue.Print(&outFile);
				inOutQueue.Print(currentTime,&outFile);
				cout<<"-------------------------------------------"<<endl;
				outFile<<"-------------------------------------------"<<endl;
				int i=0;
				cout<<"Completed Processes"<<endl;
				outFile<<"Completed Processes"<<endl;
				while(i<finishedProcesses.size())
				{
					cout<<finishedProcesses[i].name<<"  ";
					outFile<<finishedProcesses[i].name<<"  ";
					i++;
				}
				cout<<endl;
				outFile<<endl;
				cout<<"-------------------------------------------"<<endl;
				cout<<"-------------------------------------------"<<endl;
				outFile<<"-------------------------------------------"<<endl;
				outFile<<"-------------------------------------------"<<endl;
				cout<<endl<<endl;
			}
			else//no processes in processQueue
			{
				executingProcess.name="";
				executingProcess.curCpuBurstTime=0;
				CpuTimeNotUtilized+=1;
				processOnCpu=false;
			}
			currentExecutionTime=0;
		}
		currentExecutionTime++;
		currentTime++;
		if(inOutQueue.Is_Empty()&&pQueue.Is_Empty()&&processOnCpu==false)
		{
			allProcessesDone=true;
		}
	}
	//Display all calculated data in final, well-organized table display.
	cout<<"Finished"<<endl<<endl;
	outFile<<"Finished"<<endl<<endl;
	double CpuUtilization;
	currentTime-=1;
	CpuTimeNotUtilized-=1;
	CpuUtilization=currentTime-CpuTimeNotUtilized;
	CpuUtilization=(CpuUtilization/currentTime)*100;
	cout<<"Total Time: "<<currentTime<<endl;
	cout<<"CPU Utilization: "<<CpuUtilization<<"%"<<endl<<endl;
	cout<<"Waiting Times       ";
	outFile<<"Total Time: "<<currentTime<<endl;
	outFile<<"CPU Utilization: "<<CpuUtilization<<"%"<<endl<<endl;
	outFile<<"Waiting Times       ";
	int i=0;
	while(i<finishedProcesses.size())
	{
		cout<<finishedProcesses[i].name<<"   ";
		outFile<<finishedProcesses[i].name<<"   ";
		i++;
	}
	cout<<endl;
	cout<<"                    ";
	outFile<<endl;
	outFile<<"                    ";
	i=0;
	double avgWait=0;
	while(i<finishedProcesses.size())
	{
		cout<<finishedProcesses[i].waitTime<<"  ";
		outFile<<finishedProcesses[i].waitTime<<"  ";
		avgWait+=finishedProcesses[i].waitTime;
		i++;
	}
	cout<<endl<<"Average Wait:       "<<avgWait/finishedProcesses.size();
	cout<<endl<<endl;
	cout<<"Turnaround Times    ";
	outFile<<endl<<"Average Wait:       "<<avgWait/finishedProcesses.size();
	outFile<<endl<<endl;
	outFile<<"Turnaround Times    ";
	i=0;
	while(i<finishedProcesses.size())
	{
		cout<<finishedProcesses[i].name<<"   ";
		outFile<<finishedProcesses[i].name<<"   ";
		i++;
	}
	cout<<endl;
	cout<<"                    ";
	outFile<<endl;
	outFile<<"                    ";
	i=0;
	double avgTT=0;
	while(i<finishedProcesses.size())
	{
		cout<<finishedProcesses[i].TurnAroundTime<<"  ";
		outFile<<finishedProcesses[i].TurnAroundTime<<"  ";
		avgTT+=finishedProcesses[i].TurnAroundTime;
		i++;
	}
	cout<<endl<<"Average Turnaround: "<<avgTT/finishedProcesses.size();
	cout<<endl<<endl;
	cout<<"Response Times      ";
	outFile<<endl<<"Average Turnaround: "<<avgTT/finishedProcesses.size();
	outFile<<endl<<endl;
	outFile<<"Response Times      ";
	i=0;
	while(i<finishedProcesses.size())
	{
		cout<<finishedProcesses[i].name<<"   ";
		outFile<<finishedProcesses[i].name<<"   ";
		i++;
	}
	cout<<endl;
	cout<<"                    ";
	outFile<<endl;
	outFile<<"                    ";
	i=0;
	double avgRT=0;
	while(i<finishedProcesses.size())
	{
		cout<<finishedProcesses[i].responseTime<<"   ";
		outFile<<finishedProcesses[i].responseTime<<"   ";
		avgRT+=finishedProcesses[i].responseTime;
		if(finishedProcesses[i].responseTime<10)
		{
			cout<<" ";
		}
		i++;
	}
	cout<<endl<<"Average Response:   "<<avgRT/finishedProcesses.size();
	cout<<endl<<endl;
	outFile<<endl<<"Average Response:   "<<avgRT/finishedProcesses.size();
	outFile<<endl<<endl;

	system("Pause");
	return 0;
}

