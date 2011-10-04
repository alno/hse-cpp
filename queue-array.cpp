#include <iostream>
#include <stdexcept>
#include <memory.h>

class Queue {
	int start;
	int end;
	int size;

	double * data;

public:
	Queue(int size) : size(size), start(0), end(0), data(new double[size+1]) {}
	Queue(const Queue & q) : size(q.size), start(q.start), end(q.end), data(new double[size+1]) {
		memcpy(data, q.data, (size + 1) * sizeof(double));
	}
	~Queue() { delete[] data; }

	void add(double v) {
		if ((end + 1) % (size + 1) == start)
			throw std::logic_error("Queue is full");

		data[end] = v;

		end = (end + 1) % (size + 1);
	}

	double get() {
		if (start == end)
			throw std::logic_error("Queue is empty");

		double v = data[start];

		start = (start + 1) % (size + 1);

		return v;
	}

	bool empty() {
		return start == end;
	}
};


int main() {
	Queue q(3);

	q.add(1);
	q.add(2);
	q.add(3);

	Queue q2 = q;

	while (!q.empty())
		std::cout << q.get() << std::endl;

	while (!q2.empty())
		std::cout << q2.get() << std::endl;

	q.add(4);
	q.add(5);
	q.add(6);

	while (!q.empty())
		std::cout << q.get() << std::endl;
}
