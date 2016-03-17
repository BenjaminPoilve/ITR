#include <iostream>
#include <string>
#include <memory>

class AbstractHello
{
public:
	AbstractHello(const std::string& name_);
	virtual ~AbstractHello();
	virtual void print() const = 0;

public:
	const std::string& name() const { return _name; }

private:
	const std::string _name;
};

AbstractHello::AbstractHello(const std::string& name_) : _name(name_)
{
	std::cout << "Construct " << _name << std::endl;
}

AbstractHello::~AbstractHello()
{
	std::cout << "Destroy " << _name << std::endl;
}

class Hello : public AbstractHello
{
public:
	Hello(const std::string& name_ = "World") : AbstractHello(name_) {}
	void print() const;
};

void Hello::print() const
{
	std::cout << "Hello " << name() << '!' << std::endl;
}

int main()
{
	std::cout << "Begin" << std::endl;
	std::auto_ptr<AbstractHello> hello(new Hello());
	hello->print();
	std::cout << "End" << std::endl;

	return 0;
}
