#ifndef Produce_h_INCLUDED
#define Produce_h_INCLUDED
#include "Lock.h"
#include <iostream>
#include "Thread.h"
#include "Mutex.h"
#include "Fifo.hpp"

class Produce : public Thread
{
public:
	Produce(int nPush, int schedPolicy, Fifo<int>* fifo);
protected:
	void run();
private:
	Fifo<int>* m_pFifo;
	int nPush;

};


#endif
