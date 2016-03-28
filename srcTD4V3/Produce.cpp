#include "Produce.h"


Produce::Produce(int nPush, int schedPolicy, Fifo<int>* fifo): nPush(nPush), Thread(schedPolicy), m_pFifo(fifo) // Thread à construire en premier
{
}

void Produce::run()
{
	for(int i=0; i< nPush; i++)
	{
		m_pFifo->push(42);
	}
}




