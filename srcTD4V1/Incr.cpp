#include "Incr.h"

Incr::Incr(Counter* pCounter, int schedPolicy): Thread(schedPolicy), m_pCounter(pCounter) // Thread à construire en premier
{
}

void Incr::run()
{
	if(m_pCounter->getMutexUse() == true)
	{
		for(int i=0; i <  m_pCounter->get_nLoops(); i++)
		{
			m_pCounter->incrementSafe();		
		}
	}
	else
	{
		for(int i=0; i < m_pCounter->get_nLoops(); i++)
		{
			m_pCounter->incrementUnsafe();
		}		
	}
}

Incr::Counter::Counter(double nLoops, bool mutexUse): 
mutex(false), value(0), nLoops(nLoops), mutexUse(mutexUse) 
// obligatoirement dans la liste d'initialisation pcq le mutex créé et initialisé directement. Faut le faire pour tout ce qui est hérité, embedded, const, réf. 
{ 

}


double Incr::Counter::incrementSafe()
{
	try
	{
		Lock lock(&mutex);
		value += 1;
	}
	catch(std::exception& e)
	{
		std::cerr << "Error:" << e.what() << std::endl;
	} 
	return value;
}
double Incr::Counter::incrementUnsafe()
{
	value += 1;
	return value;
}
double Incr::Counter::getValue()
{ 
	return value;
}

bool Incr::Counter::getMutexUse()
{ 
	return mutexUse;
}

double Incr::Counter::get_nLoops()
{ 
	return nLoops;
}
