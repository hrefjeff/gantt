#include <iostream>
#include "RoundRobin.h"

void RoundRobin::makeGantt()
{

	for (int i = 0; i<waitingQueue.size(); i++)
	{
		waitingQueue[i]->setWaitTime(0);
		waitingQueue[i]->setStartTime(-1);
		waitingQueue[i]->setStopTime(-1);
	}

	int pBurstTime = 0;
	int waitTime = 0;

	// Keep going if we didn't get to the end of the waiting queue
	while (!waitingQueue.empty())
	{
		pBurstTime = waitingQueue.front()->getBurstTime();

		if (pBurstTime == 0)
		{
			waitingQueue.pop_front();
		}

		// If the item in the waiting queue has more burst time after processing
		else if (pBurstTime > timeSlice)
		{
			// assuming all processes end
			if (waitingQueue.front()->getStartTime() < 0)
			{
				waitingQueue.front()->setStartTime(waitTime);
				waitingQueue.front()->setStopTime(0);
			}
			
			Process * temp = new Process(waitingQueue.front());
			temp->setWaitTime(waitTime);
			temp->setBurstTime(timeSlice);
			gantt.push_back(temp);

			waitingQueue.front()->setBurstTime(pBurstTime - timeSlice);
			waitingQueue.push_back(waitingQueue.front());
			waitingQueue.pop_front();

			waitTime += timeSlice;
		}

		// If burstime is less than or equal to time slice
		else if (pBurstTime <= timeSlice)
		{
			if (waitingQueue.front()->getStartTime() < 0)
				waitingQueue.front()->setStartTime(waitTime);

			waitingQueue.front()->setWaitTime(waitTime);
			waitingQueue.front()->setStopTime(waitTime + pBurstTime);
			gantt.push_back(waitingQueue.front());
			
			waitTime += waitingQueue.front()->getBurstTime();

			waitingQueue.pop_front();
		}
	}
}

void RoundRobin::makeColumnTurnAround()
{
	chartTurnAround.clear();

	//Turnaround Time
	int tt = 0;

	for (int i=0; i<gantt.size(); i++)
	{
		if ((gantt[i]->getStopTime() > 0)) 
		{
			tt = gantt[i]->getStopTime() - gantt[i]->getStartTime();
			gantt[i]->setTurnAroundTime(tt);
			chartTurnAround.push_back(gantt[i]);
		}
	}
}

void RoundRobin::makeColumnWait()
{
	chartWait.clear();

	//Time
	int t=0;

	for (int i=0; i<gantt.size(); i++)
	{
		// If process was the last process entered,
		// Get burst time of process and add it to wait time
		if (gantt[i]->getStopTime() > 0)
		{
			chartWait.push_back(gantt[i]);
		}
	}
}


int RoundRobin::getTimeSlice()
{
	return timeSlice;
}

void RoundRobin::setTimeSlice(int quantum)
{
	timeSlice = quantum;
}