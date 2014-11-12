#include <iostream>
#include "FirstComeFirstServe.h"

void FirstComeFirstServe::makeGantt()
{
	// Go down the line and assign the waiting queue to gantt line
	for (int j=0; j<waitingQueue.size(); j++)
	{
		gantt.push_back(waitingQueue.at(j));
	}
}

void FirstComeFirstServe::makeColumnTurnAround()
{
	//Time
	int t = 0;
	int waitTime = 0;

	for (int i=0; i<gantt.size(); i++)
	{
		t = gantt[i]->getBurstTime();
		gantt[i]->setTurnAroundTime(t);
		waitTime += waitTime;
		gantt[i]->setWaitTime(waitTime);
	}

	for (int j=0; j<gantt.size(); j++)
	{
		chartTurnAround.push_back(gantt[j]);
	}
}

void FirstComeFirstServe::makeColumnWait()
{
	//Time
	int t=0;

	// First process always has a wait time of 0.
	gantt[0]->setWaitTime(t);
	
	for (int i=0; i<gantt.size()-1; i++)
	{	
		// Get burst time of process and add it to wait time
		t += gantt[i]->getBurstTime();
		// Set the next process
		gantt[i+1]->setWaitTime(t);
	}

	for (int j=0; j<gantt.size(); j++)
	{
		chartWait.push_back(gantt[j]);
	}
}