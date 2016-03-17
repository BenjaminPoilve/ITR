#ifndef Mutex_h_INCLUDED
#define Mutex_h_INCLUDED

#include <pthread.h>
#include <errno.h> 

class Mutex
{
public:
	Mutex(bool isInversionSafe);
	void lock();
	bool lock(double timeout_ms);
	bool trylock();
	void unlock();
private:
	pthread_mutex_t mid;
};

#endif
