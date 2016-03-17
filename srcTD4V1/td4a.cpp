// on appelle le pthread_create dans start.

class Thread
{
public:	
	Thread(int); // constructeur 
	~Thread();
	void start(int);
	void join();

protected:
	virtual void run() = 0;		
	
private: 
	static void* call_run(pthread_t*);
	pthread_t m_tid;
	pthread_attr_t m_attr; 
	int m_schedPolicy;
	
};


Thread::Thread(int schedPolicy, int tid, p_thread_attr_t attr) : 
	m_tid(0), m_attr(attr), m_schedPolicy(schedPolicy)
{
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, schedPolicy);
	pthread_attr_setinheritedsched(&attr, PTHREAD_EXPLICIT_SCHED);
}
 
 
static void* Thread::call_run(void* thread)
{
	Thread* ptr_thread= (Thread*)thread;
	ptr_thread->run();
}


void Thread::start(int priority) 
{
	sched_param schedParam;
	schedParams.sched_priority = priority;
	pthread_attr_setschedparams(&m_attr, &schedParams);
	pthread_create(&m_tid, &m_attr, call_run, this); 
}


void Thread::join()
{ 
	pthread_join(m_tid, NULL);
}
