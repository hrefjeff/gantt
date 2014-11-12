#include <iostream>
#include "AbstractSchedStrat.h"

AbstractSchedStrat::AbstractSchedStrat()
{

	while (!waitingQueue.empty())
	{
		waitingQueue.pop_front();
	}

	gantt.resize(0);
	gantt.empty();

	chartTurnAround.resize(0);
	chartWait.resize(0);
	chartWaitAvg = 0.0;

}

AbstractSchedStrat::~AbstractSchedStrat()
{
	// clear method removes & destroys all
	// elements in a container
	while (!waitingQueue.empty())
	{
		waitingQueue.pop_front();
	}
	chartTurnAround.clear();
	chartWait.clear();
	chartWaitAvg = 0.0;
}

void AbstractSchedStrat::addProcess(Process * newProcess)
{
	waitingQueue.push_back(newProcess);
}

void AbstractSchedStrat::removeProcess()
{
	waitingQueue.pop_front();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Writer(s): Jeffrey Allen
  Purpose  : Constructor for minBinaryHeap
  Incoming : N/A
  Outgoing : N/A
  Return   : N/A
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void AbstractSchedStrat::printWaitQueue()
{
	cout << endl;
	cout << "~~~~~~~~~~~~~~WAITING QUEUE~~~~~~~~~~~~~" << endl;
    for (int i = 0; i<waitingQueue.size(); i++)
    {
		cout << "_______________INDEX: " << i << "______________" << endl;
		cout << "Name      : " << waitingQueue[i]->getName() << endl;
		cout << "BurstTime : " << waitingQueue[i]->getBurstTime() << endl;
		cout << "Priority  : " << waitingQueue[i]->getPriority() << endl;
		cout << "Wait Time : " << waitingQueue[i]->getWaitTime() << endl;
    }
    cout << endl;
}

void AbstractSchedStrat::printWaitChart()
{
	cout << endl;
	cout << "~~~~~~~~~~~~~~WAITING COLUMN~~~~~~~~~~~~~" << endl;
    for (int i = 0; i<chartWait.size(); i++)
    {
		cout << "Wait Column " << i << ": " << waitingQueue[i] << endl;		
    }
    cout << endl;
}

void AbstractSchedStrat::printGantt()
{
	cout << endl;
	cout << "~~~~~~~~~~~~~~GANTT QUEUE~~~~~~~~~~~~~" << endl;
    for (int i = 0; i<gantt.size(); i++)
    {
		cout << "_______________INDEX: " << i << "______________" << endl;
		cout << "Name      : " << gantt[i]->getName() << endl;
		cout << "BurstTime : " << gantt[i]->getBurstTime() << endl;
		cout << "Priority  : " << gantt[i]->getPriority() << endl;
		cout << "Wait Time : " << gantt[i]->getWaitTime() << endl;
    }
    cout << endl;
}

vector<Process *> AbstractSchedStrat::getColumnTurnAround()
{
	return chartTurnAround;
}

vector<Process *> AbstractSchedStrat::getColumnWait()
{
	return chartWait;
}


double AbstractSchedStrat::calculateWaitAvg()
{
	double avg = 0.0;
	int total = 0.0;

	for (int i=0; i<chartWait.size(); i++)
	{
		total += chartWait[i]->getWaitTime();
	}

	avg = total / chartWait.size();

	return avg;
}