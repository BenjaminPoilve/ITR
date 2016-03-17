#include <stdio.h>
#include <time.h>

#include <unistd.h>
#include <stdlib.h>



void incr(unsigned int nLoops, double* pCounter)
{
	for(int i=0; i < nLoops; i++)
	{
		*pCounter += 1;
	}
}


  void startClock(timespec* pStart){
	  if( clock_gettime( CLOCK_REALTIME, pStart) == -1 ) {
      perror( "clock gettime" );
    }
  }
  
  
   void stopClock(timespec* pStop){
	   if( clock_gettime( CLOCK_REALTIME, pStop) == -1 ) {
      perror( "clock gettime" );
    }
  }

int main(int argc, char* argv[])
{
	timespec start, stop;
    double accum=0.;
    const double BILLION = 1000000000.;
    
	if(argc > 1)
	{
		
		int nLoops = 0;
		sscanf(argv[1], "%d", &nLoops);
		double counter = 0.0;	
		startClock(&start);
		incr(nLoops, &counter);
		stopClock(&stop);
		printf("%Lf\n", counter);
		accum = ( stop.tv_sec - start.tv_sec ) + (( stop.tv_nsec - start.tv_nsec ) / BILLION);
		printf("%lf\n", accum);
		return 0;
	}
	printf("Function expected 1 argument, got 0 instead");
	return -1;
}


  
  
  
  
  
