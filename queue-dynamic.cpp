#include <iostream>
#include <stdexcept>

struct Element {
	double value;
	Element * next;
};

class Queue {
private:
	Element * first;
	Element * last;
public:
	Queue(): first(0), last(0) {		
	}

	Queue(const Queue & q): first(0), last(0) {
		Element * cur = q.first;

		while (cur != 0) {
			add(cur->value);
			cur = cur->next;
		}
	}

	~Queue() {
		/*while (first != 0) {
			Element * next = first->next;
			delete first;
			first = next;s
		}*/

		while (!empty())
			get();
	}

	void add(double v) {
		if ( first == 0 ) {
			first = new Element();
			first->value = v;
			first->next = 0;

			last = first;
		} else {
			last->next = new Element();
			last->next->value = v;
			last->next->next = 0;

			last = last->next;
		}
	}

	double get() {
		if ( first == 0 )
			throw std::logic_error("Queue is empty");

		double value = first->value;
		Element * next = first->next;

		delete first;

		first = next;

		return value;
	}

	bool empty() const {
		return first == 0;
	}

};


int main() {
	Queue q;

	q.add(1);
	q.add(2);
	q.add(3);

	Queue q2 = q;

	while (!q.empty())
		std::cout << q.get() << std::endl;

	while (!q2.empty())
		std::cout << q2.get() << std::endl;
}
