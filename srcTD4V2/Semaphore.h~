#ifndef Semaphore_h_INCLUDED
#define Semaphore_h_INCLUDED
#include "Condition.h"
#include <limits.h>

class Semaphore
{
public:
	Semaphore(unsigned int initCount = 0, unsigned int maxCount = UINT_MAX, unsigned int bkdTasks =0);
	void give();
	void flush();
	void take();
	bool take(double timeout_ms);
private:
	volatile unsigned int counter;
	unsigned int maxCount;
	Condition condition;
	unsigned int bkdTasks; // compteur correspondant au nombre de tâches en attente de mutex (utile pour flush())
};

#endif
