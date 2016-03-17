#include "Thread.h"

Thread::Thread(int schedPolicy) : m_schedPolicy(schedPolicy)
{
	pthread_t m_tid;
	pthread_attr_t m_attr;
	pthread_attr_init(&m_attr);
	pthread_attr_setschedpolicy(&m_attr, schedPolicy);
	pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED);
}
 
 
void* Thread::call_run(void* thread)
{
	Thread* ptr_thread= (Thread*)thread;
	ptr_thread->run();
}


void Thread::start(int priority) 
{
	sched_param schedParam;
	schedParam.sched_priority = priority;
	pthread_attr_setschedparam(&m_attr, &schedParam);
	pthread_create(&m_tid, &m_attr, call_run, this); 
}


void Thread::join()
{ 
	pthread_join(m_tid, NULL);
}

void Thread::join(double timeout_ms)
{
	struct timespec abstime;
	clock_gettime(CLOCK_REALTIME, &abstime);
	long secs = timeout_ms / 1000;
	abstime.tv_sec += secs;
	abstime.tv_nsec += (timeout_ms - secs *1000) * 1000000;
	if(abstime.tv_nsec >= 1000000000)
	{	
		abstime.tv_sec += 1; 
		abstime.tv_nsec %= 1000000000; //TODO utiliser classe Clock
	}
	pthread_timedjoin_np(m_tid, NULL, &abstime);
}

void Thread::sleep(double delay_ms)
{
	const double mille = 1000;
	struct timespec tim;
	tim.tv_sec = delay_ms / mille;
	tim.tv_nsec = (delay_ms - (delay_ms / mille) * mille) * mille * mille;
	nanosleep(&tim, NULL);
}

void Thread::setStackSize(size_t stackSize)
{
	pthread_attr_setstacksize(&m_attr, stackSize);
	//printf("Thread stack size successfully set to %li bytes\n",stackSize);
}
