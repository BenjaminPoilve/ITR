#ifndef Mutex_h_INCLUDED
#define Mutex_h_INCLUDED

#include <pthread.h>
#include <errno.h> 

class Mutex
{
public:
	Mutex(bool isInversionSafe);
	~Mutex();
	void lock();
	bool lock(double timeout_ms);
	bool trylock();
	void unlock();
protected:
	pthread_mutex_t mid;
};

#endif
