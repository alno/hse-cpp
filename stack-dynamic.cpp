#include <stdexcept>
#include <iostream>

class Element {
public:
	double value;
	Element * next;

	Element(double value, Element * next) :
	value(value), next(next) {}
};

class Stack {
	Element * top;

public:
	Stack(): top(0) {}
	~Stack() {
		while ( top != 0 ) {
			Element * e = top;
			top = top->next;
			delete e;
		}
	}

	void push(double v) {
		top = new Element(v, top);
	}

	double pop() {
		if ( top == 0)
			throw std::logic_error("Stack is empty");

		double value = top->value;
		Element * next = top->next;

		delete top;

		top = next;		
		return value;
	}

	double get_top() {
		if ( top == 0)
			throw std::logic_error("Stack is empty");

		return top->value;
	}

	bool empty() {
		return top == 0;
	}

};

int main() {
	Stack s;
	s.push(23);
	s.push(11);
	s.push(5);

	while (!s.empty())
		std::cout << s.pop() << std::endl;
}
