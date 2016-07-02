#include <iostream>
#include <string>

struct person
{
	person(std::string const &name) : name_(name)
	{
	}

	void setName(std::string const &name)
	{
		name_ = name;
	}

	friend std::ostream &operator<<(std::ostream &out, person const &p)
	{
		return out << p.name_;
	}

private:
	std::string name_;	
};

void foo(person const &value)
{
	//value = person("ola foo");
	//value.setName("ola foo");
}

void bar(person &value)
{
	//value = person("ola bar");
	value.setName("ola bar");
}

void var(person* const value)
{
	//value = new person("ola var");
	value->setName("ola var");
}

void tar(person const *value)
{
	value = new person("ola tar");
	//value->setName("ola tar");
}

void xar(const person* const value)
{
	//value = new person("ola tar");
	//value->setName("ola tar");
}

int main() {

	person p("ola");
	std::cout << p << '\n';

	foo(p);
	std::cout << p << '\n';

	bar(p);
	std::cout << p << '\n';

	var(&p);
	std::cout << p << '\n';

	tar(&p);
	std::cout << p << '\n';

	return 0;
}