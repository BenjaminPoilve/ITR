#include "Lock.h"

Lock::Lock(Mutex* mutex): m(mutex)
{
	m->lock();
}

Lock::Lock(Mutex* mutex, double timeout_ms): m(mutex)
{
	if(m->lock(timeout_ms) == false)	
		throw std::runtime_error("There was a runtime error");
}

Lock::~Lock()
{
	m->unlock();
}
