#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <iostream>

using namespace std;

typedef struct CountParam CountParam;
struct CountParam
{ 
	double* pCounter;
	unsigned int nLoops;
	pthread_mutex_t mutex;
	bool mutexUse;
};

void startClock(timespec* pStart)
{
	if( clock_gettime( CLOCK_REALTIME, pStart) == -1 ) 
	{
		perror( "clock gettime" );
	}
}
  
  
void stopClock(timespec* pStop)
{
	if( clock_gettime( CLOCK_REALTIME, pStop) == -1 ) 
	{
		perror( "clock gettime" );
    }
}

void incr(unsigned int nLoops, double* pCounter, bool mutexUse, pthread_mutex_t* mutex ) //si  on passe NULL il appelle pas le mutex
{
	if(mutexUse)
	{
		
		for(int i=0; i < nLoops; i++)
		{
			
			pthread_mutex_lock(mutex);
			*pCounter += 1;
			pthread_mutex_unlock(mutex);
		}
	}
	else
	{
		for(int i=0; i < nLoops; i++)
		{
			*pCounter += 1;	
		}		
	}
}

void* call_incr(void* param)
{
	CountParam* p_struct = (CountParam*)param ;

	incr((*p_struct).nLoops, (*p_struct).pCounter, (*p_struct).mutexUse, &((*p_struct).mutex));
	
	
	
}


int main(int argc, char* argv[])
{

	timespec start, stop;
    double accum=0.;
    const double BILLION = 1000000000.;
	int nLoops = 0;
	int nTask=0;
	if(argc > 2)
	{
		sscanf(argv[1], "%d", &nLoops);
		sscanf(argv[2], "%d", &nTask);
		pthread_t threads[nTask];
		pthread_attr_t attr;
		pthread_attr_init(&attr); // FOR REAL TIME
		pthread_attr_setschedpolicy(&attr, SCHED_RR); // FOR REAL TIME
		pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED); // FOR REAL TIME
		sched_param schedParams;
		schedParams.sched_priority = 42;
		pthread_attr_setschedparam(&attr, &schedParams);
		double counter = 0.0;	
		startClock(&start);
		CountParam param;
		param.nLoops = nLoops;
		param.pCounter = &counter;
		if(argc>3)
		{
			param.mutexUse = true;
		}
		else
		{
			param.mutexUse = false;
		}
		pthread_mutex_init(&param.mutex, NULL);
		for(int i=0; i < nTask; i++)
		{
			cout << "main(): creating thread, " << i << endl;
			pthread_create(&threads[i], &attr, call_incr, &param);
		}
		for(int j=0; j < nTask; j++)
		{
			pthread_join(threads[j], NULL);
		}
		stopClock(&stop);

		accum = ( stop.tv_sec - start.tv_sec ) + (( stop.tv_nsec - start.tv_nsec ) / BILLION);
		printf("%lf\n", accum);
		printf("%Lf\n", counter);
		pthread_mutex_destroy(&param.mutex);
		return 0;
	}
	printf("Function expected 2 arguments.");
	return -1;
}


  
  
  
  
  
