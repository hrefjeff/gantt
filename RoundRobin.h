#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include "AbstractSchedStrat.h"

class RoundRobin: public AbstractSchedStrat {

	private:

		int timeSlice;
	
	public:

		void makeGantt();
		void makeColumnTurnAround();
		void makeColumnWait();

		int getTimeSlice();

		void setTimeSlice(int);

};

#endif