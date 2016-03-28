#include "Consume.h"
#include <iostream>

Consume::Consume(Counter* pCounter, int schedPolicy, Fifo<int>* fifo): Thread(schedPolicy), m_pCounter(pCounter), m_pFifo(fifo),canFinish(false) // Thread à construire en premier
{
}

void Consume::run()
{
	while(!(canFinish && m_pFifo->isEmpty()))
	{
		int res;	
		try
		{
		 	res = m_pFifo->pop(20);
			if(m_pCounter->getMutexUse() == true)
			{
				m_pCounter->incrementSafe();		
			}
			else
			{
				m_pCounter->incrementUnsafe();
			}
		}
		catch (const std::exception& ex)
		{ 
			std::cout << "Exception" << std::endl;
		}
		std::cout << "je suis tjs dans la boucle" << std::endl;
	}
	std::cout << "je suis sorti de la boucle" << std::endl;
}

void Consume::allowFinish()
{
	canFinish=true;
}

bool Consume::getFinish()
{
	return canFinish;
}


Consume::Counter::Counter(bool mutexUse): 
mutex(true), value(0), mutexUse(mutexUse)
// obligatoirement dans la liste d'initialisation pcq le mutex créé et initialisé directement. Faut le faire pour tout ce qui est hérité, embedded, const, réf. 
{ 

}


double Consume::Counter::incrementSafe()
{
	try
	{
		Lock lock(&mutex);
		value += 1;
		std::cout << value << std::endl;
	}
	catch(std::exception& e)
	{
		std::cerr << "Error:" << e.what() << std::endl;
	} 
	return value;
}
double Consume::Counter::incrementUnsafe()
{
	value += 1;
	return value;
}
double Consume::Counter::getValue()
{ 
	return value;
}

bool Consume::Counter::getMutexUse()
{ 
	return mutexUse;
}

