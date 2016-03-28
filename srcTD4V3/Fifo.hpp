#ifndef Fifo_hpp_INCLUDED
#define Fifo_hpp_INCLUDED

#include <exception>
#include <queue>
#include "Lock.h"
#include "Condition.h"


template<typename T> class Fifo
{
public:
	class EmptyException : public std::exception
	{
	public:
		const char* what() throw();
	};

public:
	void push(T msg)
	{
		elements.push(msg);
		condition.notify();
	}

	bool isEmpty()
	{
		return elements.empty();
	}
	T pop()
    	{
		Lock lock(&condition);
		while(elements.empty())
		{
	   	 condition.wait();
		}
		T popped = elements.front();
		elements.pop();
		return popped;
   	}
	T pop(double timeout_ms)
	{
		Lock lock(&condition);
		while(elements.empty())
			if(!condition.wait(timeout_ms))
			{
				throw EmptyException();
			}
		T popped = elements.front();
		elements.pop();
		return popped;
	}


private:
	std::queue<T> elements;
	Condition condition;
};


#endif
