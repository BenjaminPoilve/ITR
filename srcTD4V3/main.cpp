#include <stdio.h>
#include <vector>
#include <iostream>

#include "Produce.h"
#include "Consume.h"
#include "Thread.h"
#include "Mutex.h"
#include "Lock.h"

using namespace std;

int main(int argc, char* argv[])
{
	int nProduce=0;
	int nConsume=0;
	Fifo<int> fifo;

	if(argc > 2)
	{
		sscanf(argv[1], "%d", &nProduce);
		sscanf(argv[2], "%d", &nConsume);
		int nPush = 10;
		Consume::Counter counter(true);
		
		int schedPolicy;
		schedPolicy = SCHED_RR;
		vector<Consume*> myVectCons;
		vector<Produce*> myVectProd;
		for(int i=0; i<nProduce; i++)
		{	
			Produce* ptrProduce = new Produce(nPush, schedPolicy, &fifo); 
			myVectProd.push_back(ptrProduce);
		}
		for(int i=0; i<nConsume; i++)
		{	
			Consume* ptrConsume = new Consume(&counter, schedPolicy, &fifo); 
			myVectCons.push_back(ptrConsume);
		}
		
		for(int i=0; i < nProduce; i++)
		{
			cout << "main(): creating thread, " << i << endl;
			myVectProd[i]->start(42);
		}
		for(int i=0; i < nConsume; i++)
		{
			cout << "main(): creating thread, " << i << endl;
			myVectCons[i]->start(42);
		}
		for(int i=0; i < nProduce; i++)
		{
			myVectProd[i]->join(20);
		}
		for(int i=0; i < nConsume; i++)
		{
			myVectCons[i]->allowFinish();
			cout << "allowed " << myVectCons[i]->getFinish() << endl;
	
		}
		for(int i=0; i < nConsume; i++)
		{
			myVectCons[i]->join(20);
		}
		for(int i=0; i < nProduce; i++)
		{
			delete myVectProd[i];
		}
		for(int i=0; i < nConsume; i++)
		{
			delete myVectCons[i];
		}

		myVectProd.clear();
		myVectCons.clear();

		cout << "Le compteur vaut: " << counter.getValue() << endl;
		return 0;
	}
	return -1;
}
