#include "Mutex.h"

Mutex::Mutex(bool isInversionSafe) 
{
	pthread_mutex_t mid;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	//TODO iniatiliser et destroy attr
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	if(isInversionSafe == true)
	{
		pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);	
	}
	pthread_mutex_init(&mid, &attr);
	pthread_mutexattr_destroy(&attr);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&mid);
}

void Mutex::lock()
{
	pthread_mutex_lock(&mid);
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&mid);
}


bool Mutex::lock(double timeout_ms)
{
	struct timespec abstime;
	clock_gettime(CLOCK_REALTIME, &abstime);
	long secs = timeout_ms / 1000;
	abstime.tv_sec += secs;
	abstime.tv_nsec += (timeout_ms - secs *1000) * 1000000;
	if(abstime.tv_nsec >= 1000000000)
	{	
		abstime.tv_sec += 1; 
		abstime.tv_nsec %= 1000000000; //TODO utiliser classe Clock
	}
	if (pthread_mutex_timedlock(&mid, &abstime) == ETIMEDOUT)
	{
		return false;
	}
	return true;
}


bool Mutex::trylock()
{
	return pthread_mutex_trylock(&mid);
}
