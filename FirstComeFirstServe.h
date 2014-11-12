#ifndef FIRSTCOMEFIRSTSERVE_H
#define FIRSTCOMEFIRSTSERVE_H

#include "AbstractSchedStrat.h"

class FirstComeFirstServe: public AbstractSchedStrat {
	
	public:

		void makeGantt();
		void makeColumnTurnAround();
		void makeColumnWait();
};

#endif