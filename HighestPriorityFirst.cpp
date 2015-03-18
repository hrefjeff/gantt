#include <iostream>
#include "HighestPriorityFirst.h"

void HighestPriority::makeGantt()
{
	bool swapOccured = true;
	Process * max;

	// Keep going while we're pushing to gantt
	while (swapOccured)
	{
		// pretend that we didn't push anything
		swapOccured = false;

		// Set the max to 0 index
		max = waitingQueue.at(0);

		// compare each value to the max position
		for (int j = 0; j<waitingQueue.size(); j++)
		{

			// change the max if necessary
			if ((waitingQueue.at(j)->getPriority() < max->getPriority()) && waitingQueue.at(j)->getInListFlag())
			{
				max = waitingQueue.at(j);
				swapOccured = true;
			}
		}

		// push to gantt chart
		gantt.push_back(max);
		max->setInListFlag(false);
	}

	// Get rest of list and push it on.
	for (int i=0; i<waitingQueue.size(); i++)
	{
		if (waitingQueue.at(i)->getInListFlag())
		{
			gantt.push_back(waitingQueue.at(i));
			waitingQueue.at(i)->setInListFlag(false);
		}
	}

	// Cleanup the mess we just made
	for (int k=0; k<waitingQueue.size(); k++)
		waitingQueue.at(k)->setInListFlag(true);
}