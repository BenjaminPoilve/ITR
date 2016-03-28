#include "Semaphore.h"
#include "Lock.h"

Semaphore::Semaphore(unsigned int initCount, unsigned int maxCount, unsigned int bkdTasks):
counter(initCount), maxCount(maxCount), bkdTasks(bkdTasks)
{}

void Semaphore::take()
{	
	Lock lock(&condition);
	if(counter > 0)
	{
		counter -= 1;
		condition.notifyAll();
	}
	else
	{	
		bkdTasks += 1;
		while (counter == 0)
		{ 
			condition.wait(); //wait libère le mutex en étant bloqué :)
		}
		bkdTasks -= 1; 
		counter -= 1;
		condition.notifyAll();
	}	
}

bool Semaphore::take(double timeout_ms)
{
	Lock lock(&condition);
	if(counter > 0)
	{
		counter -= 1;
		condition.notifyAll();
	}
	else
	{
		bkdTasks += 1;
		while (counter == 0)
		{
			if(!condition.wait(timeout_ms)); //wait libère le mutex en étant bloqué :)
			{	
				bkdTasks -= 1;
				break; // on unlock grace a notre utilisation brillante de l'objet Lock (dépilé)
			}
		}
		bkdTasks -= 1;
		counter -= 1;
		condition.notifyAll();
	}	
}


void Semaphore::give()
{
	Lock lock(&condition);
	if(counter < maxCount)
	{
		counter += 1;
		condition.notifyAll();
	}
	else
	{
		while (counter >= maxCount)
		{
			condition.wait(); //wait libère le mutex en étant bloqué :)
		}
		counter += 1;
		condition.notifyAll();
	}	
}




void Semaphore::flush() // idée on incremente un compteur à chaque appel bloquant, la on broadcast un signal après avoir ajouté le nb de tache au counter.
{
	Lock lock(&condition);
	counter += bkdTasks;
	condition.notifyAll();
}

