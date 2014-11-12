#include <vector>
#include <deque>

#include "process.h"
#include "FirstComeFirstServe.h"
#include "RoundRobin.h"

#ifndef ABSTRACTSCHEDSTRAT_H
#define ABSTRACTSCHEDSTRAT_H

using namespace std;

//-------------------------------------------------------------------
// ABSTRACT Scheduling strategy
//-------------------------------------------------------------------

class AbstractSchedStrat {

	protected:

		deque<Process *> waitingQueue;
		vector<Process *> gantt;
		vector<Process *> chartTurnAround;
		vector<Process *> chartWait;
		double chartWaitAvg;

	public:

		AbstractSchedStrat();
		~AbstractSchedStrat();

		void addProcess(Process *);
		void removeProcess();
		void printWaitQueue();
		void printGantt();
		void printWaitChart();

		vector<Process *> getColumnTurnAround();
		vector<Process *> getColumnWait();

		virtual void makeGantt() = 0;
		virtual void makeColumnTurnAround() {}
		virtual void makeColumnWait() {}
		double calculateWaitAvg();
};

#endif