#include "Counter.h"

Incr::Incr(Counter* pCounter, int schedPolicy): Thread(schedPolicy), m_pCounter(pCounter) // Thread à construire en premier
{
}

void Incr::run()
{
	if( m_pCounter->mutexUse == true)
	{
		for(int i=0; i <  m_pCounter->nLoops; i++)
		{
			pthread_mutex_lock(&(m_pCounter->mutex));
			m_pCounter->value += 1;
			pthread_mutex_unlock(&(m_pCounter->mutex));
		}
	}
	else
	{
		for(int i=0; i < m_pCounter->nLoops; i++)
		{
			m_pCounter->value += 1;	
		}		
	}
}
