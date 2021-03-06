#ifndef Counter_h_INCLUDED
#define Counter_h_INCLUDED

#include <pthread.h>
#include "Thread.h"

class Incr : public Thread
{
public:
	struct Counter 
	{
		int value;
		pthread_mutex_t mutex;
		bool mutexUse;
		double nLoops;
	};
public:
	Incr(Counter* pCounter, int schedPolicy);
protected:
	void run();
private:
	Counter* m_pCounter;	

};


#endif
