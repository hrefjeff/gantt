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