#ifndef Consume_h_INCLUDED
#define Consume_h_INCLUDED
#include "Lock.h"
#include <iostream>
#include "Thread.h"
#include "Mutex.h"
#include "Fifo.hpp"

class Consume : public Thread
{
public:
	class Counter 
	{	
	public:
		Counter(bool);
		double getValue();
		double incrementSafe();
		double incrementUnsafe();
		bool getMutexUse();
		
	private:
		int value;
		Mutex mutex;
		bool mutexUse;
	};
public:
	Consume(Counter* pCounter, int schedPolicy, Fifo<int>* fifo);
	void allowFinish();
	bool getFinish();
protected:
	void run();
private:
	Counter* m_pCounter;	
	Fifo<int>* m_pFifo;
	bool canFinish;


};


#endif
