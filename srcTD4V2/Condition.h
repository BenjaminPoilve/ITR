#include <time.h>
#include "Mutex.h"

class Condition : public Mutex
{
public:
	Condition();
	~Condition();
	void wait();
	bool wait(double);
	void notify();
	void notifyAll(); 
private:
	pthread_cond_t cid;
	

};
