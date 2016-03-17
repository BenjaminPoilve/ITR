#ifndef Lock_h_INCLUDED
#define Lock_h_INCLUDED

#include "Mutex.h"
#include <stdexcept>

class Lock
{
public:
	Lock(Mutex* m);
	Lock(Mutex* m, double timeout_ms);
	~Lock();
private:
	Mutex* m;
};

#endif
