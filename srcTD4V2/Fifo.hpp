#ifndef Fifo_hpp_INCLUDED
#define Fifo_hpp_INCLUDED
#include <exception>

template<typename T> // T type de message.
class Fifo
{
public:
	class EmptyException : public std::exception
	{
	public:
		const char* what() throw();
	};

public:
	void push(T msg);
	T pop();
	T pop(double timeout_ms);
private:
	std::queue<T> elements;
	Condition condition;
};

void push(T msg)
{
	elements.push(msg);
	condition.notify();
}

T pop()
{
	if(!elements.empty())
	{
		elements.pop();
	}
	else()
	{
		while (elements.empty())
		{
			condition.wait(); 
		}
	}
}

#endif
