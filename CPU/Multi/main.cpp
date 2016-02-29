#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "node.h"
#include "priorityQueue.h"
#include "fcfsQueue.h"
#include "ioQueue.h"
using namespace std;
#pragma once

int main()
{
	//Declare and initialize all necessary values for cpu algorithm functionality
	ofstream outFile;//reference to output file
	outFile.open("mlfq.txt");
	priorityQueue pQueue1,pQueue2;//Create process queues
	fcfsQueue fQueue;
	pQueue1.generateProcesses();//Generate 9 processes 
	pQueue1.setQuantum(6);//Set time quantum of p queue 1
	pQueue2.setQuantum(12);//Set time quantum of p queue 2
	ioQueue inOutQueue;//create io queue
	node executingProcess;//create cpu execution process
	executingProcess.name="";
	vector<node> finishedProcesses;//keeps track of processes that have finished all cpu/io bursts
	int currentExecutionTime=0;//tracks current process execution time
	int currentTime=0;//tracks total program time
	bool start=true;//first run 
	bool processOnCpu=true;
	node holderProcess;//Holds process for determining which queue to put the process leaving io in
	bool allProcessesDone=false;
	int CpuTimeNotUtilized=0;//Tracks total time where cpu had no process
	int IoProcessesDone=0;//tracks finished io processes at current time
	while(!inOutQueue.Is_Empty()||!pQueue1.Is_Empty()||allProcessesDone==false)
	{
		IoProcessesDone=inOutQueue.checkIoStatus(currentTime);//Check Io status and put finished processes in processQueue.
		if(IoProcessesDone!=0)
		{
			while(IoProcessesDone!=0)//If there are processes ready, check their priority and put them in the proper queue.
			{
				holderProcess=inOutQueue.outOfIo(currentTime);
				if(holderProcess.priority==1)
				{
					pQueue1.Enqueue(holderProcess);
				}
				else if(holderProcess.priority==2)
				{
					pQueue2.Enqueue(holderProcess);
				}
				else
				{
					fQueue.Enqueue(holderProcess);
				}
				
				inOutQueue.Dequeue();
				IoProcessesDone--;
			}
		}
		//====================================================
		if(executingProcess.curCpuBurstTime==currentExecutionTime&&processOnCpu)//If currently executing process is done, move it to io if need be.
		{
			
			executingProcess.remainingCpuBurstTime-=currentExecutionTime;
			if(executingProcess.remainingCpuBurstTime==0)//Save info of process if it has completed all execution/io time
			{
				executingProcess.newBurst=true;
				if(executingProcess.cpuBurstList.size()==executingProcess.cpuBurstNumber)
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
				if(!pQueue1.Is_Empty())//check if process queue 1 is empty, if not place a new process on the cpu and display new set of info
				{
					cout<<"Current Time: "<<currentTime<<endl;
					outFile<<"Current Time: "<<currentTime<<endl;
					processOnCpu=true;
					executingProcess=pQueue1.dispatchProcess(currentTime);
					pQueue1.Dequeue();
					cout<<"Now Running: "<<executingProcess.name<<endl;
					cout<<"-------------------------------------------"<<endl<<endl;
					cout<<"Priority Queue 1:"<<endl;
					outFile<<"Now Running: "<<executingProcess.name<<endl;
					outFile<<"-------------------------------------------"<<endl<<endl;
					outFile<<"Priority Queue 1:"<<endl;
					pQueue1.Print(&outFile);
					cout<<"Priority Queue 2:"<<endl;
					outFile<<"Priority Queue 2:"<<endl;
					pQueue2.Print(&outFile);
					cout<<"Priority Queue 3:"<<endl;
					outFile<<"Priority Queue 3:"<<endl;
					fQueue.Print(&outFile);
					inOutQueue.Print(currentTime,&outFile);
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
					outFile<<endl<<endl;
				}
				else if(!pQueue2.Is_Empty())//check if process queue 2 is empty, if not place a new process on the cpu and display new set of info
				{
					cout<<"Current Time: "<<currentTime<<endl;
					outFile<<"Current Time: "<<currentTime<<endl;
					processOnCpu=true;
					executingProcess=pQueue2.dispatchProcess(currentTime);
					pQueue2.Dequeue();
					cout<<"Now Running: "<<executingProcess.name<<endl;
					cout<<"-------------------------------------------"<<endl<<endl;
					cout<<"Priority Queue 1:"<<endl;
					outFile<<"Now Running: "<<executingProcess.name<<endl;
					outFile<<"-------------------------------------------"<<endl<<endl;
					outFile<<"Priority Queue 1:"<<endl;
					pQueue1.Print(&outFile);
					cout<<"Priority Queue 2:"<<endl;
					outFile<<"Priority Queue 2:"<<endl;
					pQueue2.Print(&outFile);
					cout<<"Priority Queue 3:"<<endl;
					outFile<<"Priority Queue 3:"<<endl;
					fQueue.Print(&outFile);
					inOutQueue.Print(currentTime,&outFile);
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
					outFile<<endl<<endl;
				}
				else if(!fQueue.Is_Empty()) //check if process fqueue is empty, if not place a new process on the cpu and display new set of info
				{
					cout<<"Current Time: "<<currentTime<<endl;
					outFile<<"Current Time: "<<currentTime<<endl;
					processOnCpu=true;
					executingProcess=fQueue.dispatchProcess(currentTime);
					fQueue.Dequeue();
					cout<<"Now Running: "<<executingProcess.name<<endl;
					cout<<"-------------------------------------------"<<endl<<endl;
					outFile<<"Now Running: "<<executingProcess.name<<endl;
					outFile<<"-------------------------------------------"<<endl<<endl;
					cout<<"Priority Queue 1:"<<endl;
					outFile<<"Priority Queue 1:"<<endl;
					pQueue1.Print(&outFile);
					cout<<"Priority Queue 2:"<<endl;
					outFile<<"Priority Queue 2:"<<endl;
					pQueue2.Print(&outFile);
					cout<<"Priority Queue 3:"<<endl;
					outFile<<"Priority Queue 3:"<<endl;
					fQueue.Print(&outFile);
					inOutQueue.Print(currentTime,&outFile);
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
					outFile<<endl<<endl;
				}
				else//No process in ready queues
				{
					executingProcess.name="";
					executingProcess.curCpuBurstTime=0;
					CpuTimeNotUtilized+=1;
					processOnCpu=false;
				}
			}
			else//The current process still has cpu time remaining but the Round Robin quantum has finished -> switch new process on to cpu
			{
				executingProcess.newBurst=false;
				executingProcess.priority+=1;
				if(executingProcess.priority==2)//enqueue process to correct queue
				{
					pQueue2.Enqueue(executingProcess);
				}
				else
				{
					fQueue.Enqueue(executingProcess);
				}
				if(!pQueue1.Is_Empty())//check if process queue 1 is empty, if not place a new process on the cpu and display new set of info
					{
						cout<<"Current Time: "<<currentTime<<endl;
						outFile<<"Current Time: "<<currentTime<<endl;
						processOnCpu=true;
						executingProcess=pQueue1.dispatchProcess(currentTime);
						pQueue1.Dequeue();
						cout<<"Now Running: "<<executingProcess.name<<endl;
						cout<<"-------------------------------------------"<<endl<<endl;
						outFile<<"Now Running: "<<executingProcess.name<<endl;
						outFile<<"-------------------------------------------"<<endl<<endl;
						cout<<"Priority Queue 1:"<<endl;
						outFile<<"Priority Queue 1:"<<endl;
						pQueue1.Print(&outFile);
						cout<<"Priority Queue 2:"<<endl;
						outFile<<"Priority Queue 2:"<<endl;
						pQueue2.Print(&outFile);
						cout<<"Priority Queue 3:"<<endl;
						outFile<<"Priority Queue 3:"<<endl;
						fQueue.Print(&outFile);
						inOutQueue.Print(currentTime,&outFile);
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
						outFile<<endl<<endl;
					}
					else if(!pQueue2.Is_Empty())//check if process queue 2 is empty, if not place a new process on the cpu and display new set of info
					{
						cout<<"Current Time: "<<currentTime<<endl;
						outFile<<"Current Time: "<<currentTime<<endl;
						processOnCpu=true;
						executingProcess=pQueue2.dispatchProcess(currentTime);
						pQueue2.Dequeue();
						cout<<"Now Running: "<<executingProcess.name<<endl;
						cout<<"-------------------------------------------"<<endl<<endl;
						outFile<<"Now Running: "<<executingProcess.name<<endl;
						outFile<<"-------------------------------------------"<<endl<<endl;
						cout<<"Priority Queue 1:"<<endl;
						outFile<<"Priority Queue 1:"<<endl;
						pQueue1.Print(&outFile);
						cout<<"Priority Queue 2:"<<endl;
						outFile<<"Priority Queue 2:"<<endl;
						pQueue2.Print(&outFile);
						cout<<"Priority Queue 3:"<<endl;
						outFile<<"Priority Queue 3:"<<endl;
						fQueue.Print(&outFile);
						inOutQueue.Print(currentTime,&outFile);
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
						outFile<<endl<<endl;
					}
					else if(!fQueue.Is_Empty())//check if process fqueue  is empty, if not place a new process on the cpu and display new set of info
					{
						cout<<"Current Time: "<<currentTime<<endl;
						outFile<<"Current Time: "<<currentTime<<endl;
						processOnCpu=true;
						executingProcess=fQueue.dispatchProcess(currentTime);
						fQueue.Dequeue();
						cout<<"Now Running: "<<executingProcess.name<<endl;
						cout<<"-------------------------------------------"<<endl<<endl;
						outFile<<"Now Running: "<<executingProcess.name<<endl;
						outFile<<"-------------------------------------------"<<endl<<endl;
						cout<<"Priority Queue 1:"<<endl;
						outFile<<"Priority Queue 1:"<<endl;
						pQueue1.Print(&outFile);
						cout<<"Priority Queue 2:"<<endl;
						outFile<<"Priority Queue 2:"<<endl;
						pQueue2.Print(&outFile);
						cout<<"Priority Queue 3:"<<endl;
						outFile<<"Priority Queue 3:"<<endl;
						fQueue.Print(&outFile);
						inOutQueue.Print(currentTime,&outFile);
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
						outFile<<endl<<endl;
					}
					else
					{
						executingProcess.name="";
						executingProcess.curCpuBurstTime=0;
						CpuTimeNotUtilized+=1;
						processOnCpu=false;
					}
				
			}
			
			currentExecutionTime=0;
		}
		///////////////////////////////////////////////////////////////////////////////
		else if(processOnCpu==false)// If no process on cpu, look if a  new process is available in the queues
		{
			if(!pQueue1.Is_Empty())//check if process queue 1 is empty, if not place a new process on the cpu and display new set of info
			{
				cout<<"Current Time: "<<currentTime<<endl;
				outFile<<"Current Time: "<<currentTime<<endl;
				processOnCpu=true;
				executingProcess=pQueue1.dispatchProcess(currentTime);
				pQueue1.Dequeue();
				cout<<"Now Running: "<<executingProcess.name<<endl;
				cout<<"-------------------------------------------"<<endl<<endl;
				outFile<<"Now Running: "<<executingProcess.name<<endl;
				outFile<<"-------------------------------------------"<<endl<<endl;
				cout<<"Priority Queue 1:"<<endl;
				outFile<<"Priority Queue 1:"<<endl;
				pQueue1.Print(&outFile);
				cout<<"Priority Queue 2:"<<endl;
				outFile<<"Priority Queue 2:"<<endl;
				pQueue2.Print(&outFile);
				cout<<"Priority Queue 3:"<<endl;
				outFile<<"Priority Queue 3:"<<endl;
				fQueue.Print(&outFile);
				inOutQueue.Print(currentTime,&outFile);
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
				outFile<<endl<<endl;
			}
			else if(!pQueue2.Is_Empty())//check if process queue 2 is empty, if not place a new process on the cpu and display new set of info
			{
				cout<<"Current Time: "<<currentTime<<endl;
				outFile<<"Current Time: "<<currentTime<<endl;
				processOnCpu=true;
				executingProcess=pQueue2.dispatchProcess(currentTime);
				pQueue2.Dequeue();
				cout<<"Now Running: "<<executingProcess.name<<endl;
				cout<<"-------------------------------------------"<<endl<<endl;
				outFile<<"Now Running: "<<executingProcess.name<<endl;
				outFile<<"-------------------------------------------"<<endl<<endl;
				cout<<"Priority Queue 1:"<<endl;
				outFile<<"Priority Queue 1:"<<endl;
				pQueue1.Print(&outFile);
				cout<<"Priority Queue 2:"<<endl;
				outFile<<"Priority Queue 2:"<<endl;
				pQueue2.Print(&outFile);
				cout<<"Priority Queue 3:"<<endl;
				outFile<<"Priority Queue 3:"<<endl;
				fQueue.Print(&outFile);
				inOutQueue.Print(currentTime,&outFile);
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
				outFile<<endl<<endl;
			}
			else if(!fQueue.Is_Empty())//check if process fqueue is empty, if not place a new process on the cpu and display new set of info
			{
				cout<<"Current Time: "<<currentTime<<endl;
				outFile<<"Current Time: "<<currentTime<<endl;
				processOnCpu=true;
				executingProcess=fQueue.dispatchProcess(currentTime);
				fQueue.Dequeue();
				cout<<"Now Running: "<<executingProcess.name<<endl;
				cout<<"-------------------------------------------"<<endl<<endl;
				outFile<<"Now Running: "<<executingProcess.name<<endl;
				outFile<<"-------------------------------------------"<<endl<<endl;
				outFile<<"Priority Queue 1:"<<endl;
				cout<<"Priority Queue 1:"<<endl;
				pQueue1.Print(&outFile);
				cout<<"Priority Queue 2:"<<endl;
				outFile<<"Priority Queue 2:"<<endl;
				pQueue2.Print(&outFile);
				cout<<"Priority Queue 3:"<<endl;
				outFile<<"Priority Queue 3:"<<endl;
				fQueue.Print(&outFile);
				inOutQueue.Print(currentTime,&outFile);
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
				outFile<<endl<<endl;
			}
			else//No processes available for execution
			{
				executingProcess.name="";
				executingProcess.curCpuBurstTime=0;
				CpuTimeNotUtilized+=1;
				processOnCpu=false;
			}
			currentExecutionTime=0;
		}
		else//Case for making sure a fcfs (priority 3) process doesn't keep executing if a higher priority process is available
		{
			
			executingProcess.newBurst=false;
			if(!pQueue1.Is_Empty()&&executingProcess.priority>1)//check if process queue 1 is empty, if not place a new process on the cpu and display new set of info
			{
				cout<<"Current Time: "<<currentTime<<endl;
				outFile<<"Current Time: "<<currentTime<<endl;
				processOnCpu=true;
				executingProcess.remainingCpuBurstTime-=currentExecutionTime;
				if(executingProcess.priority==2)
				{
					pQueue2.Enqueue(executingProcess);
				}
				else
				{
					fQueue.Enqueue(executingProcess);
				}
				executingProcess=pQueue1.dispatchProcess(currentTime);
				pQueue1.Dequeue();
				cout<<"Now Running: "<<executingProcess.name<<endl;
				cout<<"-------------------------------------------"<<endl<<endl;
				outFile<<"Now Running: "<<executingProcess.name<<endl;
				outFile<<"-------------------------------------------"<<endl<<endl;
				cout<<"Priority Queue 1:"<<endl;
				outFile<<"Priority Queue 1:"<<endl;
				pQueue1.Print(&outFile);
				cout<<"Priority Queue 2:"<<endl;
				outFile<<"Priority Queue 2:"<<endl;
				pQueue2.Print(&outFile);
				cout<<"Priority Queue 3:"<<endl;
				outFile<<"Priority Queue 3:"<<endl;
				fQueue.Print(&outFile);
				inOutQueue.Print(currentTime,&outFile);
				int i=0;
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
				outFile<<endl<<endl;
				currentExecutionTime=0;
			}
			else if(!pQueue2.Is_Empty()&&executingProcess.priority>2) //check if process queue 2 is empty, if not place a new process on the cpu and display new set of info
			{
				cout<<"Current Time: "<<currentTime<<endl;
				processOnCpu=true;
				executingProcess.remainingCpuBurstTime-=currentExecutionTime;
				fQueue.Enqueue(executingProcess);
				executingProcess=pQueue2.dispatchProcess(currentTime);
				pQueue2.Dequeue();
				cout<<"Now Running: "<<executingProcess.name<<endl;
				cout<<"-------------------------------------------"<<endl<<endl;
				outFile<<"Now Running: "<<executingProcess.name<<endl;
				outFile<<"-------------------------------------------"<<endl<<endl;
				cout<<"Priority Queue 1:"<<endl;
				outFile<<"Priority Queue 1:"<<endl;
				pQueue1.Print(&outFile);
				cout<<"Priority Queue 2:"<<endl;
				outFile<<"Priority Queue 2:"<<endl;
				pQueue2.Print(&outFile);
				cout<<"Priority Queue 3:"<<endl;
				outFile<<"Priority Queue 3:"<<endl;
				fQueue.Print(&outFile);
				inOutQueue.Print(currentTime,&outFile);
				int i=0;
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
				outFile<<endl<<endl;
				currentExecutionTime=0;
			}
		}
		currentExecutionTime++;
		currentTime++;
		if(inOutQueue.Is_Empty()&&pQueue1.Is_Empty()&&processOnCpu==false)
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

